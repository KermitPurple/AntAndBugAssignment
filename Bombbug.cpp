#include "Bombbug.h"
#include "GL/glut.h"
#include "WorldGL.h"
#include "World.h"
#include "organism.h"

Bombbug::Bombbug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord){    
	death_tik = 9;
}

void Bombbug::move(){
	death_tik--;
	if(death_tik <= -1){
		explode();
	}
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

void Bombbug::printIcon(double xx, double yy) const{
	//Set color
	glColor3f(0.000f, 0.000f, 1.000f);

	//print
	printSquare(xx, yy, size());
	//Set color
	glColor3f(1.000f, 1.000f, 1.000f);
	printLetter(xx,yy);
}

void Bombbug::generateOffspring(int whereX, int whereY){
}

void Bombbug::printLetter(int whereX, int whereY)const{
	glRasterPos2d((whereX + 0.4)*SCALE, (WORLDHEIGHT - whereY - 0.6)*SCALE);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, char(48+death_tik));
}
void Bombbug::explode(){
	delete world->getAt(x, x);
	world->setAt(x, x, NULL);
}
bool Bombbug::isDead() const{
	if(death_tik <=-1)
		return true;
	return false;
}
