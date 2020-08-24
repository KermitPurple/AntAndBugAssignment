CC = g++
CFLAGS = -c -Wall
INCLUDE = -Iinclude
LIBS = -lfreeGLUT -lopenGL32

all: main Ant Bug Organism World Superant WorldGL
	$(CC) bin/*.o -o bin/test.exe $(INCLUDE) $(LIBS)

%: src/%.cpp
	$(CC) $< $(CFLAGS) -o bin/$@.o $(INCLUDE) $(LIBS)

clean:
	rm bin/*

new:
	mkdir bin

test: all
	bin/test.exe
	
