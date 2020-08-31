CC = g++
CFLAGS = -c -Wall
INCLUDE = -Iinclude
LIBS = -lfreeGLUT -lopenGL32 -lwinmm

all: Ant Bug World Organism main World Bombbug
	$(CC) bin/*.o -o bin/test.exe $(INCLUDE) $(LIBS)
	@echo

%: src/%.cpp
	$(CC) $< $(CFLAGS) -o bin/$@.o $(INCLUDE) $(LIBS)

clean:
	rm bin/*

new:
	mkdir bin

test: all
	bin/test.exe
