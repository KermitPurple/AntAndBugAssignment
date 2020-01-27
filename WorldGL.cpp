#include<GL/glut.h>
#include "time.h"
#include"WorldGL.h"
#include"World.h"

static void WorldGL::display(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//Clears the Screen
	// if auto, move forward 1 step
	if(myWorld.getAuto()){
		myWorld.simulateOneStep();
		Sleep(250);
	}
	myWorld.display();
	glutSwapBuffers();//This keeps it from breaking. I don't know exactly what it does but its good
}

static void WorldGL::kbin(unsigned char key, int x, int y) {
	if(key == 'q'){
		exit(1);
	}
	else if(key == char(32)){//space
		myWorld.simulateOneStep();
	}
	else if (key == 'a'){
		myWorld.createOrganisms(ANT, 1);
	}
	else if (key == 'b'){
		myWorld.createOrganisms(BUG, 1);
	}
	else if (key == 's'){
		//create SuperAnt
		//myWorld.createOrganisms(SUPERANT, 1);
	}
	else if (key == 'z'){
		myWorld.toggleAuto();
	}
}

WorldGL::WorldGL(int argc, char *argv[]){
	myWorld = World(time(0));
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize (500, 600) ;
	glutCreateWindow( "Organism Simulation" );
	glOrtho(0, WORLDSIZE * SCALE, 0, WORLDHEIGHT * SCALE, 0, 1);
}

void WorldGL::run() const{
	//output
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(kbin);
	
	//Loop
	glutMainLoop();
}
