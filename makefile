all: Ant.o Bug.o World.o Organism.o main.o World.o
	g++ *.o -o test.exe -l freeGLUT -l openGL32

Ant.o: Ant.cpp Ant.h
	g++ Ant.cpp -c -o Ant.o

Bug.o: Bug.cpp Bug.h
	g++ Bug.cpp -c -o Bug.o

Organism.o: Organism.cpp Organism.h
	g++ Organism.cpp -c -o Organism.o

World.o: World.cpp World.h
	g++ World.cpp -c -o World.o -l freeGLUT -l openGL32

main.o: main.cpp
	g++ main.cpp -c -o main.o -l freeGLUT -l openGL32

clean:
	rm *.o test.exe

force: clean all

test: all
	test.exe
