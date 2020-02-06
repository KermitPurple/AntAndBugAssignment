#ifndef BOMBUG_H
#define BOMBUG_H

#include "Organism.h"
#include "World.h"

class Bombbug : public Organism {
public:
	Bombbug(World* aworld, int xcoord, int ycoord);

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

private:
    void generateOffspring(int whereX, int whereY);
    int death_tik;
    void printLetter(int whereX, int whereY)const;
};

#endif //BOMBUG_H
