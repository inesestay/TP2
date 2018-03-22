#include "header.h"
#include "labyrinthe.h"

int main()
{
	//0 Variables
	Labyrinth tab1;

	//1 Lecture
	tab1.readFile();






	//2 Affichage
	tab1.affichage();

	tab1.cheminLargeur();

    tab1.cheminProfondeur();

	tab1.affichageconnexe();



	return 0;
}
