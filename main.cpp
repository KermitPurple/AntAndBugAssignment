#include <GL/glut.h>
#include <iostream>
#include <ctime>    // for time
#include <conio.h>
#include <MMSystem.h>
#include "World.h"
#include "WorldGL.h"
using namespace std;

int main(int argc, char *argv[]){
	PlaySound(TEXT("sound.wav"), NULL, SND_ASYNC);

	WorldGL myWorldGL(argc, argv);
	myWorldGL.run();
	return 0;
}
