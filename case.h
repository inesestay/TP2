#ifndef __CASE__
#define __CASE__

#include "header.h"
#include "noeud.h"

class Case
{
private:
	int m_taille;
	Noeud* m_tete;
	Noeud* m_queue;
	bool m_marque;

	int m_X;
	int m_Y;

	int m_X_prec;
	int m_Y_prec;

public:
	Case();
	Case(int taille, bool marque);
	~Case();

	//Setteurs
	void setMarque(bool marque);

	//Getteurs
	bool getMarqued();
	// Teste si la case est reliée à une case de coordonnées x, y
	bool isLinked(int x, int y);

	//Ajoute un Noeud à la liste
	void addKnot(int x, int y);


	void initaliserTaille();

	//ajout methode perso
	Noeud* getTete(){return m_tete;}
	Noeud* getQueue(){return m_queue;}


	void setXPrecedent(int val){m_X_prec = val;}
	void setYPrecedent(int val){m_Y_prec = val;}

	int getXPrecedent(){return m_X_prec;}
	int getYPrecedent(){return m_Y_prec;}

	void setX(int val){m_X = val;}
	void setY(int val){m_Y = val;}

	int getX(){return m_X;}
	int getY(){return m_Y;}
};

#endif // __CASE__
