#include <GL/glut.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "Bombbug.h"
using namespace std;

///////////////////
// Public functions
///////////////////

World* World::currentInstance;

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed, int argc, char* argv[]) {
    currentInstance = this;
    // default auto
    Auto = true;
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the ants = 3
    createOrganisms(ANT, INITIAL_ANTS);
    // creates the bugs = 8
    createOrganisms(BUG, INITIAL_BUGS);
    // create a bomb bug
    createOrganisms(BOMBBUG, 1);

    // initialize window for graphics library
	glutInit(&argc, argv);// initialize 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// choose display mode
	glutInitWindowPosition(0, 0);//set Position
	glutInitWindowSize(500, 600);//set size
	glutCreateWindow("Organism Simulation");// set title
	glOrtho(0, WORLDSIZE * SCALE, 0, WORLDHEIGHT * SCALE, 0, 1);//set scale
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::print_screen() const {
     
	//print Grid
	printGrid();

	//print Icons
    int numAnts = 0;
    int numBugs = 0;
    int numBombBugs = 0;
    for (int j = 0; j < WORLDSIZE; j++) {
        for (int i = 0; i < WORLDSIZE; i++) {
            if (grid[i][j] != NULL) {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
                }
                else if (grid[i][j]->getType() == BOMBBUG) {
                    numBombBugs++;
                }
                grid[i][j]->printIcon(i,j);
            }
        }
    }

	//print text
	printOrgNums(numBugs, numAnts, numBombBugs);
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);

    //count down on bomb bug
    moveOrganism(BOMBBUG);

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
	    else if (orgType == BOMBBUG){
		    new Bombbug(this, p.x, p.y);
	    }
        }
        else if (fullGrid()){
            break;
        }
    }
}

void World::run() const{
	//output
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(kbin);
	
	//Loop
	glutMainLoop();
}

////////////////////
// Private functions
////////////////////

void World::kbin(unsigned char key, int x, int y){
	if(key == 'q'){
		exit(1);
	}
	else if(key == char(32)){//space
		currentInstance->simulateOneStep();
	}
	else if (key == 'a'){
		currentInstance->createOrganisms(ANT, 1);
	}
	else if (key == 'b'){
		currentInstance->createOrganisms(BUG, 1);
	}
	else if (key == 'x'){
		//create BombBug
		currentInstance->createOrganisms(BOMBBUG, 1);
	}
	else if (key == 'z'){
		currentInstance->toggleAuto();
	}
}

void World::display(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//Clears the Screen
	// if auto, move forward 1 step
	if(currentInstance->getAuto()){
		currentInstance->simulateOneStep();
		Sleep(250);
	}
	currentInstance->print_screen();
	glutSwapBuffers();//This keeps it from breaking. I don't know exactly what it does but its good
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
		if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
            // Kill off any organisms that haven't eaten recently
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}

//print grid
void World::printGrid() const{
	//Set color
	glColor3f(1.000f, 1.000f, 1.000f);
	//print horizontal lines
	for(int i = 1; i < WORLDHEIGHT; i++){
		glBegin(GL_LINES);
			glVertex2f(0, i * SCALE);
			glVertex2f(WORLDSIZE * SCALE, i * SCALE);
		glEnd();
	}
	//print verticle lines
	for(int i = 0; i < WORLDSIZE; i++){
		glBegin(GL_LINES);
			glVertex2f(i * SCALE, SCALE);
			glVertex2f(i * SCALE, WORLDHEIGHT * SCALE);
		glEnd();
	}
}

//print organism numbers
void World::printOrgNums(int numBugs, int numAnts, int numBombBugs) const{
	// convert from int to string
	stringstream str;
	str << numBugs << ' ' << numAnts << ' ' << numBombBugs;
	string strBugs, strAnts, strBombBugs;
	str >> strBugs >> strAnts >> strBombBugs;

	//store in array
	string text[9] = {
		"Bugs: " + strBugs,
		"Ants: " + strAnts,
		"Bomb Bugs:" + strBombBugs,
        "New Bug: b",
        "New Ant: a",
        "New BombBug: x",
        "Step: Spacebar",
        "Toggle Auto-Mode: z",
        "Quit: q",
	};

	//coordinates for the text
	Position WordPos[9] = {
		{0, int(0.7 * SCALE)},
		{0, int(0.4 * SCALE)},
		{0, int(0.1 * SCALE)},
		{WORLDSIZE * SCALE / 3, int(0.7 * SCALE)},
		{WORLDSIZE * SCALE / 3, int(0.4 * SCALE)},
		{WORLDSIZE * SCALE / 3, int(0.1 * SCALE)},
		{int(WORLDSIZE * SCALE / 1.5), int(0.7 * SCALE)},
		{int(WORLDSIZE * SCALE / 1.5), int(0.4 * SCALE)},
		{int(WORLDSIZE * SCALE / 1.5), int(0.1 * SCALE)},
	};

    //Colors for the text
    Color TextColor[9] = {
            {0,1,0},
            {1,0,0},
            {0,0,1},
            {0,1,0},
            {1,0,0},
            {0,0,1},
            {1,1,1},
            {1,1,1},
            {1,1,1},
    };

	//print lines of text
	for(int i = 0;i < 9 ;i++){
		int len = text[i].length();

        //apply Colors
        glColor3f(TextColor[i].val[0], TextColor[i].val[1], TextColor[i].val[2]);

        //apply coordinates
		glRasterPos2d(WordPos[i].x, WordPos[i].y);

		//cycle thru chars in word
		for(int j = 0; j < len; j++){
			//print
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i][j]);
		}
	}
}

// toggle auto on and off. stopping or starting the automatic playing of the game
void World::toggleAuto() const{
        Auto = !Auto;
}

// return variable auto.
bool World::getAuto() const{
        return Auto;
}

// return true if the grid is full
bool World::fullGrid() const{
        for(int j = 0; j < WORLDSIZE; j++){
            for(int i = 0; i < WORLDSIZE; i++){
                if(grid[i][j] == NULL){
                    return false;
                }
            }
        }
        return true;
}