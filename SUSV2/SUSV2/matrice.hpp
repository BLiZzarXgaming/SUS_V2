/*	##############################################################################
	Auteur		: Matias Beaulieu
	Date		: 2022/09/22
	Programme	: matrice.hpp
	But			: une matrice générique en 2D allouée dynamiquement en mémoire
	##############################################################################	*/

#pragma once
#include <iostream>
#include <iomanip>
#include <assert.h>

template <class TYPE>
class matrice
{
private:
	char* _name;										//pointeur sur le nom de la matrice
	TYPE** _matrice;										//La matrice dynamique en ligne et colonne
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

	void allocmatrice(int nbLine, int nbCol) {				//allocateur de matrice en mémoire
		if (nbLine == 0 || nbCol == 0) {
			_nbLine = _nbLine = 0;
			_matrice = nullptr;
		}
		else {
			_nbLine = nbLine;
			_nbCol = nbCol;

			_matrice = new TYPE * [nbLine];

			for (int i = 0; i < nbLine; i++) {
				*(_matrice + i) = new TYPE[nbCol];
			}
		}
	}
public:
	matrice();
	matrice(const char* name, int line, int col);
	matrice(const matrice& m);
	~matrice();

	void clear();										//clear la matrice et le nom
	void clearmatrice();									//clear la matrice et remet les dimensions à 0
	void clearName();									//clear le nom

														//getteurs / setteurs
	int nbLine()const;									//retourne le nb de ligne
	int nbCol()const;									//retourne le nb de colonne
	void resize(int nbLine, int nbCol);					//resize la matrice avec les nouv. dims

	TYPE& at(int posI, int posJ)const;					//retourne une référence à l’élément
	TYPE*& operator[](int pos)const;					//à la position i,j pour accéder ou modifier

	const char* getName()const;							//retourne le nom de la matrice
	void setName(const char* name);						//modifie le nom de la matrice

	const matrice& operator=(const matrice&);					//surcharge de l'operateur = pour affecter une matrice

	void print(std::ostream& sortie)const;				//print la matrice (sans le nom)
	void read(std::istream& entree);					//lit la matrice de la matrice ds le flux
};

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const matrice<TYPE>& m);		//surcharge de l'opérateur<<
template <class TYPE>													
std::istream& operator>>(std::istream& entree, matrice<TYPE>& m);			//surcharge de l'opérateur>>
																		
//Constructeur du matrice vide (par défaut)
template<class TYPE>
matrice<TYPE>::matrice()
{
	_name = nullptr;
	_matrice = nullptr;
	_nbCol = _nbLine = 0;
}

//Constructeur du matrice avec paramètres nom, nombre de lignes et de colones
template<class TYPE>
matrice<TYPE>::matrice(const char* name, int nbLine, int nbCol)
{
	assert(nbLine >= 0 && nbCol >= 0);

	allocName(name);
	allocmatrice(nbLine, nbCol);
}

//Constructeur de copie, qui construit une copie d'un matrice avec celui-ci en paramètre
template<class TYPE>
matrice<TYPE>::matrice(const matrice<TYPE>& m)
{
	allocName(m._name);

	allocmatrice(m._nbLine, m._nbCol);

	for (int i = 0; i < _nbLine; i++) {				//copy elements
		for (int j = 0; j < _nbCol; j++) {
			*(*(_matrice + i) + j) = *(*(m._matrice + i) + j);
		}
	}
}

//Destructeur du matrice
template<class TYPE>
matrice<TYPE>::~matrice()
{
	clear();
}

//Méthode clear du matrice et du nom pour effacer les valeurs dans le matrice et l'enlever de la mémoire
template<class TYPE>
void matrice<TYPE>::clear()
{
	clearmatrice();
	clearName();
}

//Méthode clear du matrice
template<class TYPE>
void matrice<TYPE>::clearmatrice()
{
	for (int i = 0; i < _nbLine; i++) {
		delete[] * (_matrice + i);
	}

	delete[] _matrice;
	_matrice = nullptr;
	_nbCol = _nbLine = 0;
}

//Méthode clear du nom
template<class TYPE>
void matrice<TYPE>::clearName()
{
	delete[] _name;
	_name = nullptr;
}

//Getteur du nombre de ligne
template<class TYPE>
int matrice<TYPE>::nbLine() const
{
	return _nbLine;
}

//Getteur du nombre de colones
template<class TYPE>
int matrice<TYPE>::nbCol() const
{
	return _nbCol;
}

//Resize du matrice, permet d'augmenter ou diminuer la dimension du matrice
template<class TYPE>
void matrice<TYPE>::resize(int nbLine, int nbCol)
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
				*(*(temp + i) + j) = *(*(_matrice + i) + j);
			}
		}
	}
	else 
		nbLine = nbCol = 0;

	clearmatrice();

	_matrice = temp;
	_nbLine = nbLine;
	_nbCol = nbCol;
}

//Méthode at, permet d'affecter une valeur à un endroit dans la matrice ou bien de retourner une valeur
template<class TYPE>
TYPE& matrice<TYPE>::at(int posI, int posJ) const
{
	assert(posI >= 0 && posI < _nbLine);
	assert(posJ >= 0 && posJ < _nbCol);

	return *(*(_matrice + posI) + posJ);
}

//Surcharge de l'opérateur crochet, permet d'affecter une valeur à un endroit dans une dimension du matrice ou de
//retourner une valeur à un endroit
template<class TYPE>
TYPE*& matrice<TYPE>::operator[](int pos) const
{
	assert(pos >= 0 && pos < _nbLine);

	return *(_matrice + pos);
}

//Surcharge de l'opérateur égal, pour affecter une matrice à une autre, écrase le paramètre implicite par l'explicite
//et le retourne
template<class TYPE>
const matrice<TYPE>& matrice<TYPE>::operator=(const matrice& m)
{
	if (this == &m) return *this;

	clear();
	allocName(m._name);

	for (int i = 0; i < _nbLine; i++) {				//copy elements
		for (int j = 0; j < _nbCol; j++) {
			*(*(_matrice + i) + j) = *(*(m._matrice + i) + j);
		}
	}


	return *this;
}

//Getteur du nom
template<class TYPE>
const char* matrice<TYPE>::getName() const
{
	if (_name == nullptr)
		return "\0";

	return _name;
}

//Setteur du nom avec clear et alloc
template<class TYPE>
void matrice<TYPE>::setName(const char* name)
{
	clearName();
	allocName(name);
}

//Méthode print pour l'affichage en deux dimensions des valeurs contenues dans un matrice
template<class TYPE>
void matrice<TYPE>::print(std::ostream& sortie) const
{
	for (int i = 0; i < _nbLine; i++) {
		for (int j = 0; j < _nbCol; j++) {
			sortie << std::left << std::setw(5) << *(*(_matrice + i) + j);
		}

		sortie << std::endl;
	}
}

//Méthode read pour la lecture d'un fichier ou d'un entrée quelconque
template<class TYPE>
void matrice<TYPE>::read(std::istream& entree)
{
	for (int i = 0; i < _nbLine; i++) {
		for (int j = 0; j < _nbCol; j++) {
			entree >> *(*(_matrice + i) + j);
		}
	}
}

//Surcharge de l'opérateur <<, pour appeler naturelement l'affichage
template<class TYPE>
std::ostream& operator<<(std::ostream& sortie, const matrice<TYPE>& m)
{
	m.print(sortie);

	return sortie;
}

//Surcharge de l'opérateur >>, pour appeler naturelement la lecture (readFile)
template<class TYPE>
std::istream& operator>>(std::istream& entree, matrice<TYPE>& m)
{
	m.read(entree);

	return entree;
}