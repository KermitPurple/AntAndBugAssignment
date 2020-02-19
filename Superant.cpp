#include <GL/glut.h>
#include "Superant.h"
using namespace std;

Superant::Superant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    death_tik = 0;
}

void Superant::move()
{
    breedTicks++;
    death_tik++;
    
    if(world->getAt(x, y + 1) != NULL)
    {
        if(world->getAt(x, y + 1)->getType() == BUG)
        {
            death_tik = 0;
            delete world->getAt(x, y + 1);
            movesTo(x, y + 1);
            return;
        }
    }
    
    if(world->getAt(x, y - 1) != NULL)
    {
        if(world->getAt(x, y - 1)->getType() == BUG)
        {
            death_tik = 0;
            delete world->getAt(x, y - 1);
            movesTo(x, y - 1);
            return;
        }
    }
    
    if(world->getAt(x - 1, y) != NULL)
    {
        if(world->getAt(x - 1, y)->getType() == BUG)
        {
            death_tik = 0;
            delete world->getAt(x - 1, y);
            movesTo(x - 1, y);
            return;
        }
    }
    if(world->getAt(x + 1, y) != NULL)
    {
        if(world->getAt(x + 1, y)->getType() == BUG)
        {
            death_tik = 0;
            delete world->getAt(x + 1, y);
            movesTo(x + 1, y);
            return;
        }
    }
    
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

void Superant::generateOffspring(int whereX, int whereY)
{
    new Superant(this->world, whereX, whereY);
    breedTicks = 0;
}

void Superant::breed()
{
    if(breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }
    
}

bool Superant::isDead() const
{
    if(death_tik >= STARVE_SUPERANTS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

OrganismType Superant::getType() const
{
    return SUPERANT;
}


char Superant::representation()const
{
    return 'S';
}

int Superant::size() const
{
    return 40;
}

bool Superant::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}

void Superant::printIcon(double x, double y) const{
	//Set color
	glColor3f(0, 0, 1);
	
	//print
	printSquare(x, y, size());
}
