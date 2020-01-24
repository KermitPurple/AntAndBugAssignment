#include <GL/glut.h>
#include <iostream>
#include <ctime>    // for time
#include <conio.h>
#include "World.h"
using namespace std;

World myWorld(time(0));

void display(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//Clears the Screen
	myWorld.display();
	glutSwapBuffers();//This keeps it from breaking. I don't know exactly what it does but its good
}

//int main()
//{
//    World myWorld(time(0));
//
//    myWorld.display();
//
//    char ch;
//
//    while (cin.get(ch) && ch != 'q') {   // q for quit
//        myWorld.simulateOneStep();
//        myWorld.display();
//    }
//
//    return 0;
//}

void kbin(unsigned char key, int x, int y){
	cout << key << endl;
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
}

int main(int argc, char *argv[]){
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition ( 0, 0 ) ;
	glutInitWindowSize (500, 600) ;
	glutCreateWindow( "Ant and Bug Simulation" );
	glOrtho(0, WORLDSIZE * SCALE, 0, WORLDHEIGHT * SCALE, 0, 1);

	//output
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(kbin);
	
	//Loop
	glutMainLoop();

	return 0;
}
