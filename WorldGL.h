#ifndef WORLDGL_H
#define WORLDGL_H
#include"World.h"
#include"time.h"

class WorldGL {
private:
	World myWorld(time(0));

	//print the board
	void display() const;
	
	//accept keyboard input
	void kbin() const;
public:
	WorldGL(int argc, char *argv[]);

	// simulate world;
	void run() const;
	
};

#endif //WORLDGL_H
