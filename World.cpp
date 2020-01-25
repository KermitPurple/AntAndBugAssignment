#include <GL/glut.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // default not auto
    Auto = false;
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
void World::display() const {
	//print Grid
	printGrid();

	//print Icons
    int numAnts = 0;
    int numBugs = 0;
    int numSuperAnts = 0;
    for (int j = 0; j < WORLDSIZE; j++) {
        for (int i = 0; i < WORLDSIZE; i++) {
            if (grid[i][j] != NULL) {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
                }
		grid[i][j]->printIcon(i,j);
            }
        }
    }

	//print text
	printOrgNums(numBugs, numAnts, numSuperAnts);
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
        }
    }
}

////////////////////
// Private functions
////////////////////


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
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
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
void World::printOrgNums(int numBugs, int numAnts, int numSuperAnts) const{
	// convert from int to string
	stringstream str;
	str << numBugs << ' ' << numAnts << ' ' << numSuperAnts;
	string strBugs, strAnts, strSuperAnts;
	str >> strBugs >> strAnts >> strSuperAnts;

	//store in array
	string text[9] = {
		"Bugs: " + strBugs,
		"Ants: " + strAnts,
		"Super Ants: " + strSuperAnts,
        "New Bug: b",
        "New Ant: a",
        "New SuperAnt: s",
        "Step: Spacebar",
        "Quit: q",
        " ",
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

void World::toggleAuto() const{
        Auto = !Auto;
}

bool World::getAuto() const{
        return Auto;
}
