#ifndef WORLDGL_H
#define WORLDGL_H
#include"World.h"
#include"time.h"

class WorldGL {
private:
	World myWorld;

	//print the board
	static void display();
	
	//accept keyboard input
	static void kbin();
public:
	WorldGL(int argc, char *argv[]);

	// simulate world;
	void run() const;
	
};

#endif //WORLDGL_H
