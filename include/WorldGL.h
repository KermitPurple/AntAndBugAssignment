#ifndef WORLDGL_H
#define WORLDGL_H
#include"World.h"
#include"time.h"

class WorldGL {
public:
	// constructor that takes information needed for freeGLUT
	WorldGL(int argc, char *argv[]);

	// simulate world;
	void run() const;
	
};

#endif //WORLDGL_H
