//
//  Ant.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"
using namespace std;

Ant::Ant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    
}

void Ant::move()
{
    breedTicks++;
    Move mover = world->randomMove();
    switch (mover){
        case UP:
            if(world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
            {
                movesTo(x, y + 1);
            }
            break;
        case DOWN:
            if(world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
            {
                movesTo(x, y - 1);
            }
            break;
        case LEFT:
            if(world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
            {
                movesTo(x - 1, y);
            }
            break;
        case RIGHT:
            if(world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
            {
                movesTo(x + 1, y);
            }
            break;
        default:
            break;
    }
}

void Ant::breed()
{
    if(breedTicks >= BREED_ANTS)
    {
        breedAtAdjacentCell();
    }
}


// create another ant and reset breed tiks
void Ant::generateOffspring(int whereX, int whereY)
{
    new Ant(this->world, whereX, whereY);
    breedTicks = 0;
}


// return OrganismType
OrganismType Ant::getType() const
{
    return ANT;
}

// what ant looks like in terminal
char Ant::representation() const
{
    return 'o';
}

// return size of ant when printed to screen
int Ant::size() const
{
    return 10;
}

bool Ant::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}

// print ant to the screen
void Ant::printIcon(double x, double y) const{
	//Set color
	glColor3f(1.000f, 0.000f, 0.000f);

	//print
	printSquare(x, y,size());

}
