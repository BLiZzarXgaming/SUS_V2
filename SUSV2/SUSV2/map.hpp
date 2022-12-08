/*	##############################################################################
	Auteur		: Matias Beaulieu
	Date		: 2022/09/22
	Programme	: map.hpp
	But			: une matrice générique en 2D allouée dynamiquement en mémoire
	##############################################################################	*/

#pragma once
#include <iostream>
#include <iomanip>
#include <assert.h>

template <class TYPE>
class map
{
private:
	char* _name;										//pointeur sur le nom de la map
	TYPE** _map;										//La map dynamique en ligne et colonne
	int _nbLine,										//nombre de ligne pour la matrice
		_nbCol;											//nombre de colonne pour la matrice

	void allocName(const char* name) {					//allocateur de nom en mémoire
														
		if (strlen(name) > 0) {
			_name = new char[strlen(name) + 1];
			strcpy_s(_name, strlen(name) + 1, name);
		}
		else {
			_name = nullptr;
		}	
	}

	void allocMap(int nbLine, int nbCol) {				//allocateur de map en mémoire
		if (nbLine == 0 || nbCol == 0) {
			_nbLine = _nbLine = 0;
			_map = nullptr;
		}
		else {
			_nbLine = nbLine;
			_nbCol = nbCol;

			_map = new TYPE * [nbLine];

			for (int i = 0; i < nbLine; i++) {
				*(_map + i) = new TYPE[nbCol];
			}
		}
	}
public:
	map();
	map(const char* name, int line, int col);
	map(const map& m);
	~map();

	void clear();										//clear la map et le nom
	void clearMap();									//clear la map et remet les dimensions à 0
	void clearName();									//clear le nom

														//getteurs / setteurs
	int nbLine()const;									//retourne le nb de ligne
	int nbCol()const;									//retourne le nb de colonne
	void resize(int nbLine, int nbCol);					//resize la matrice avec les nouv. dims

	TYPE& at(int posI, int posJ)const;					//retourne une référence à l’élément
	TYPE*& operator[](int pos)const;					//à la position i,j pour accéder ou modifier

	const char* getName()const;							//retourne le nom de la map
	void setName(const char* name);						//modifie le nom de la map

	const map& operator=(const map&);					//surcharge de l'operateur = pour affecter une map

	void print(std::ostream& sortie)const;				//print la matrice (sans le nom)
	void read(std::istream& entree);					//lit la matrice de la map ds le flux
};

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const map<TYPE>& m);		//surcharge de l'opérateur<<
template <class TYPE>													
std::istream& operator>>(std::istream& entree, map<TYPE>& m);			//surcharge de l'opérateur>>
																		
//Constructeur du map vide (par défaut)
template<class TYPE>
map<TYPE>::map()
{
	_name = nullptr;
	_map = nullptr;
	_nbCol = _nbLine = 0;
}

//Constructeur du map avec paramètres nom, nombre de lignes et de colones
template<class TYPE>
map<TYPE>::map(const char* name, int nbLine, int nbCol)
{
	assert(nbLine >= 0 && nbCol >= 0);

	allocName(name);
	allocMap(nbLine, nbCol);
}

//Constructeur de copie, qui construit une copie d'un map avec celui-ci en paramètre
template<class TYPE>
map<TYPE>::map(const map<TYPE>& m)
{
	allocName(m._name);

	allocMap(m._nbLine, m._nbCol);

	for (int i = 0; i < _nbLine; i++) {				//copy elements
		for (int j = 0; j < _nbCol; j++) {
			*(*(_map + i) + j) = *(*(m._map + i) + j);
		}
	}
}

//Destructeur du map
template<class TYPE>
map<TYPE>::~map()
{
	clear();
}

//Méthode clear du map et du nom pour effacer les valeurs dans le map et l'enlever de la mémoire
template<class TYPE>
void map<TYPE>::clear()
{
	clearMap();
	clearName();
}

//Méthode clear du map
template<class TYPE>
void map<TYPE>::clearMap()
{
	for (int i = 0; i < _nbLine; i++) {
		delete[] * (_map + i);
	}

	delete[] _map;
	_map = nullptr;
	_nbCol = _nbLine = 0;
}

//Méthode clear du nom
template<class TYPE>
void map<TYPE>::clearName()
{
	delete[] _name;
	_name = nullptr;
}

//Getteur du nombre de ligne
template<class TYPE>
int map<TYPE>::nbLine() const
{
	return _nbLine;
}

//Getteur du nombre de colones
template<class TYPE>
int map<TYPE>::nbCol() const
{
	return _nbCol;
}

//Resize du map, permet d'augmenter ou diminuer la dimension du map
template<class TYPE>
void map<TYPE>::resize(int nbLine, int nbCol)
{
	assert(nbLine >= 0 && nbCol >= 0);

	if (nbLine == _nbLine && nbCol == _nbCol) {
		return;
	}
	
	TYPE** temp = nullptr;

	if (nbLine > 0 && nbCol > 0) {

		temp = new TYPE * [nbLine];

		for (int i = 0; i < nbLine; i++) {
			*(temp + i) = new TYPE[nbCol];
		}

		for (int i = 0; i < nbLine && i < _nbLine; i++) {
			for (int j = 0; j < nbCol && j < _nbCol; j++) {
				*(*(temp + i) + j) = *(*(_map + i) + j);
			}
		}
	}
	else 
		nbLine = nbCol = 0;

	clearMap();

	_map = temp;
	_nbLine = nbLine;
	_nbCol = nbCol;
}

//Méthode at, permet d'affecter une valeur à un endroit dans la map ou bien de retourner une valeur
template<class TYPE>
TYPE& map<TYPE>::at(int posI, int posJ) const
{
	assert(posI >= 0 && posI < _nbLine);
	assert(posJ >= 0 && posJ < _nbCol);

	return *(*(_map + posI) + posJ);
}

//Surcharge de l'opérateur crochet, permet d'affecter une valeur à un endroit dans une dimension du map ou de
//retourner une valeur à un endroit
template<class TYPE>
TYPE*& map<TYPE>::operator[](int pos) const
{
	assert(pos >= 0 && pos < _nbLine);

	return *(_map + pos);
}

//Surcharge de l'opérateur égal, pour affecter une map à une autre, écrase le paramètre implicite par l'explicite
//et le retourne
template<class TYPE>
const map<TYPE>& map<TYPE>::operator=(const map& m)
{
	if (this == &m) return *this;

	clear();
	allocName(m._name);

	for (int i = 0; i < _nbLine; i++) {				//copy elements
		for (int j = 0; j < _nbCol; j++) {
			*(*(_map + i) + j) = *(*(m._map + i) + j);
		}
	}


	return *this;
}

//Getteur du nom
template<class TYPE>
const char* map<TYPE>::getName() const
{
	if (_name == nullptr)
		return "\0";

	return _name;
}

//Setteur du nom avec clear et alloc
template<class TYPE>
void map<TYPE>::setName(const char* name)
{
	clearName();
	allocName(name);
}

//Méthode print pour l'affichage en deux dimensions des valeurs contenues dans un map
template<class TYPE>
void map<TYPE>::print(std::ostream& sortie) const
{
	for (int i = 0; i < _nbLine; i++) {
		for (int j = 0; j < _nbCol; j++) {
			sortie << std::left << std::setw(4) << *(*(_map + i) + j);
		}

		sortie << std::endl;
	}
}

//Méthode read pour la lecture d'un fichier ou d'un entrée quelconque
template<class TYPE>
void map<TYPE>::read(std::istream& entree)
{
	for (int i = 0; i < _nbLine; i++) {
		for (int j = 0; j < _nbCol; j++) {
			entree >> *(*(_map + i) + j);
		}
	}
}

//Surcharge de l'opérateur <<, pour appeler naturelement l'affichage
template<class TYPE>
std::ostream& operator<<(std::ostream& sortie, const map<TYPE>& m)
{
	m.print(sortie);

	return sortie;
}

//Surcharge de l'opérateur >>, pour appeler naturelement la lecture (readFile)
template<class TYPE>
std::istream& operator>>(std::istream& entree, map<TYPE>& m)
{
	m.read(entree);

	return entree;
}