#include <GL/glut.h>
#include <iostream>
#include <ctime>    // for time
#include <conio.h>
#include <MMSystem.h>
#include "World.h"
using namespace std;

int main(int argc, char *argv[]){
    // play the sound
	PlaySound(TEXT("sound.wav"), NULL, SND_ASYNC);

	World myWorld(0, argc, argv);
	myWorld.run();
	return 0;
}
