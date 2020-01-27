all: Ant.o Bug.o World.o Organism.o main.o World.o WorldGl.o
	g++ *.o -o test.exe -l freeGLUT -l openGL32

Ant.o: Ant.cpp Ant.h
	g++ Ant.cpp -c -o Ant.o -l freeGLUT -l openGL32

Bug.o: Bug.cpp Bug.h
	g++ Bug.cpp -c -o Bug.o -l freeGLUT -l openGL32  

Organism.o: Organism.cpp Organism.h
	g++ Organism.cpp -c -o Organism.o -l freeGLUT -l openGL32

World.o: World.cpp World.h
	g++ World.cpp -c -o World.o -l freeGLUT -l openGL32

main.o: main.cpp
	g++ main.cpp -c -o main.o -l freeGLUT -l openGL32

WorldGL.o: WorldGL.cpp
	g++ WorldGL.cpp -c -o WorldGL.o -l freeGLUT -l openGL32

clean:
	rm *.o test.exe

test: all
	test.exe
