all: Ant.o Bug.o World.o Organism.o main.o
	g++ *.o -o test.exe

Ant.o: Ant.cpp
	g++ Ant.cpp -c -o Ant.o

Bug.o: Bug.cpp
	g++ Bug.cpp -c -o Bug.o

Organism.o: Organism.cpp
	g++ Organism.cpp -c -o Organism.o

World.o: World.cpp
	g++ World.cpp -c -o World.o

main.o: main.cpp
	g++ main.cpp -c -o main.o

