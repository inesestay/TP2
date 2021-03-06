#ifndef __LABYRINTH__
#define __LABYRINTH__

#include "header.h"
#include "case.h"
#include "noeud.h"

class Labyrinth
{
private:
	Case** m_port;
	int m_hauteur, m_largeur;
	Noeud m_in, m_out;
public:
	Labyrinth();
	Labyrinth(int hauteur, int largeur);
	Labyrinth(int hauteur, int largeur, int entreeI, int entreeJ, int sortieI, int sortieJ);
	~Labyrinth();

	void readFile();
	void affichage();
	void allocation();

	//debut code
	void nettoyageMarque();

	void cheminLargeur();
	void cheminProfondeur();
	bool recurcivite2(Case *c);
	void affichageconnexe();
    void recurcivite(Case *c);
};

#endif // __LABYRINTH__
