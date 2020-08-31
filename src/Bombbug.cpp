#include "Bombbug.h"
#include "GL/glut.h"
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
	for(int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			if(world->getAt(x + j,y + i) != NULL && (i !=0 || j != 0)){
				delete world->getAt(x + j,y + i);
				world->setAt(x + j,y + i,NULL);
			}
		}
	}
}
bool Bombbug::isDead() const{
	if(death_tik <=-1)
		return true;
	return false;
}
