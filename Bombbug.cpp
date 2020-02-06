#include "Bombbug.h"
#include "GL/glut.h"

Bombbug::Bombbug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord){    
}

void Bombbug::move(){
}

void Bombbug::breed(){
}

OrganismType Bombbug::getType() const{
	return BOMBBUG;
}

char Bombbug::representation() const{
	return 'b';
}

int Bombbug::size() const{
	return 40;
}

bool Bombbug::in_range(int xx, int yy){
	return true;
}

void Bombbug::printIcon(double x, double y) const{
	//Set color
	glColor3f(0.000f, 0.000f, 1.000f);

	//print
	printSquare(x, y, size());
}

void Bombbug::generateOffspring(int whereX, int whereY){
}



