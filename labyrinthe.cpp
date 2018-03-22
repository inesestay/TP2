#include "labyrinthe.h"

Labyrinth::Labyrinth(): m_port(NULL), m_hauteur(0), m_largeur(0), m_in(0, 0), m_out(10,10)
{}

Labyrinth::Labyrinth(int hauteur, int largeur): m_hauteur(hauteur), m_largeur(largeur), m_in(0,0), m_out(largeur,hauteur)
{
	m_port = new Case*[hauteur];
	for(int i(0); i < largeur; i++) m_port[i] = new Case[largeur];
}

Labyrinth::Labyrinth(int hauteur, int largeur, int entreeI, int entreeJ, int sortieI, int sortieJ):
			m_hauteur(hauteur), m_largeur(largeur), m_in(entreeI, entreeJ), m_out(sortieI, sortieJ)
{
	m_port = new Case*[hauteur];
	for(int i(0); i < largeur; i++) m_port[i] = new Case[largeur];
}

Labyrinth::~Labyrinth()
{
	if(m_port != NULL)
	{
		for(int i(0); i < m_hauteur; i++) delete[] m_port[i];

		delete[] m_port;
	}
}

void Labyrinth::readFile()
{
	//0 Variables
	std::ifstream fic;
	std::string fileName("lab.txt");
	std::string buffer("b");
	bool fin(false);
	int compteurLigne(0);

	//1.0 Ouverture du fichier
	fic.open(fileName.c_str());

	//2.0 Boucle de lecture
	if(fic)
	{
		while(!fin)
		{
			getline(fic, buffer);
			if(compteurLigne % 2 == 0)
			{
				if(m_largeur < buffer.size()) m_largeur = buffer.size()/2;

				if(fic.eof() || buffer[0] != '+')
				{
					m_hauteur = compteurLigne/2;
					fin = true;
				}
			}

			compteurLigne++;
		}
		std::cout << "Fin du fichier trouve" << std::endl;

		compteurLigne = 0;

		allocation();

		//Replacage de la tête de lecture en haut
		fic.seekg(0, std::ios::beg);
		if((int)fic.tellg() != 0)
		{
			fic.clear();
			fic.seekg(0, std::ios::beg);
		}

		for(int i(0); i< 2 * m_hauteur; i++)
		{
			getline(fic, buffer);

			if(i > 0 && i < (m_hauteur*2) )
			{
				for(int j(1); j < (2 * m_largeur); j++)
				{
					// Dans le cas où on est sur une ligne paire, ligne de murs horizontaux
					if(i % 2 == 0)
					{
						// On ne s'occupe que des j impairs, car les pairs sont des +
						if(j % 2 == 1)
						{
							if(buffer[j] == ' ')
							{
								m_port[(i/2)-1][j/2].addKnot((i/2), j/2);
								m_port[i/2][j/2].addKnot((i/2)-1, j/2);
							}
						}
					}
					// Dans le cas où on est sur une ligne impaire, ligne de murs verticaux et de cases (I pour entrée, O pour exit)
					else if(i % 2 == 1)
					{
						// Numéro de caractère impaire, 'case', detection de I ou de O
						if(j % 2 == 1)
						{
							if(buffer[j] == 'I') 
								m_in.setCoords(i/2, j/2);
							else if(buffer[j] == 'O')
								m_out.setCoords(i/2,j/2);
						}
						//Numero de caractère paire, detection de la presence ou de l'absence d'un mur
						if(j % 2 == 0)
						{
							if(buffer[j] == ' ')
							{
								// En cas d'absence de mur, la case gagne un noeud vers la case suivante
								m_port[i/2][j/2].addKnot(i/2, (j/2) - 1);
								m_port[i/2][(j/2) - 1].addKnot(i/2, j/2);
							}
						}
					}
				}
			}
		}
	}
}

void Labyrinth::affichage()
{
	//0 Variables

	//1 Boucle d'affichage
	for(int i(0); i <= m_hauteur*2; i++)
	{
		for(int j(0); j <= m_largeur*2; j++)
		{
			if(i % 2 == 0) // C'est à dire qu'on est sur une case de mur, de "+", ou de porte
			{
				// Si I est pair et J est pair, nous avons affaire à un "+"
				if(j % 2 == 0) std::cout << "+";
				// Si I est pair et J est impair, c'est une porte ou un mur horizontal
				else if(i != 0 && i != m_hauteur*2 && m_port[(i/2)-1][j/2].isLinked(i/2, j/2))
				{
					if(m_port[(i/2)-1][j/2].getMarqued() && m_port[i/2][j/2].getMarqued())
						std::cout << "X";
					else std::cout << " ";
				}
				else
				{
					std::cout << "-";
				}
			}
			else
			{
				if(j % 2 == 1) // I est impair et J est impair, on est sur une case
				{
					if(m_in.getX() == i/2 && m_in.getY() == j/2) std::cout << "I";
					else if(m_out.getX() == i/2 && m_out.getY() == j/2) std::cout << "O";
					else if(m_port[i/2][j/2].getMarqued()) std::cout << "X";
					else std::cout << " ";
				}
				else // I est impair et J est paur, on est sur un mur vertical ou une porte 
				{
					if(j != 0 && j != m_largeur*2 && m_port[i/2][(j/2)-1].isLinked(i/2, j/2))// C'est une porte
					{
						if(m_port[i/2][(j/2)-1].getMarqued() && m_port[i/2][j/2].getMarqued())
							std::cout << "X";
						else std::cout << " ";
					}
					else
					{
						std::cout << "|";
					}
				}
			}
		}
		std::cout << std::endl;
	}
}

void Labyrinth::allocation()
{
	m_port = new Case*[m_hauteur];
	for(int i(0); i < m_hauteur; i++) m_port[i] = new Case[m_largeur];
}