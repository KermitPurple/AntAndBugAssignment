#ifndef SUPERANT_H 
#define SUPERANT_H

#include "World.h"
#include "Organism.h"

class Superant : public Organism {
public:
       Superant(World* aworld, int xcoord, int ycoord);

       //makes superant move
       void move();

       // Makes this organism breed.
       void breed();

       // Returns the type of this organism.
       OrganismType getType() const;

       // The character representation of this organism.
       char representation() const;

       // The size of this organism.
       int size() const;

       bool in_range(int xx, int yy);

       //prints the icon of the corresponding organism
       virtual void printIcon(double x, double y) const;

       //is the superant dead
       bool isDead() const;

private:
    void generateOffspring(int whereX, int whereY);
    //count down to death
    int death_tik;
};

#endif //SUPERANT_H
