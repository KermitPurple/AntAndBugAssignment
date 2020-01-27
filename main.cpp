#include <GL/glut.h>
#include <iostream>
#include <ctime>    // for time
#include <conio.h>
#include "World.h"
#include "WorldGL.h"
using namespace std;

int main(int argc, char *argv[]){
	WorldGL myWorldGL(argc, argv);
	myWorldGL.run();
	return 0;
}
