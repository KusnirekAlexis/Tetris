#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <exception>
#include "Matrice.h"
using namespace std;

class Forme : public sf::Drawable, public sf::Transformable {
private:
	int X;
	int Y;
	int SIZE_FORME = 4;
	int touteForme[7][4][4]{ {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}},
							{{0,0,0,0}, {2,2,2,2}, {0,0,0,0},{0,0,0,0}},
							{{0,0,0,0} ,{3,0,0,0}, {3,3,3,0},{0,0,0,0}},
							{{0,0,0,0} ,{4,4,4,0}, {4,0,0,0},{0,0,0,0}},
							{{0,0,0,0} ,{5,5,0,0}, {0,5,5,0},{0,0,0,0}},
							{{0,0,0,0} ,{0,6,6,0}, {6,6,0,0},{0,0,0,0}},
							{{0,0,0,0} ,{0,0,7,0}, {0,7,7,7},{0,0,0,0}} };
public:
	Matrice forme = Matrice(4, 4);

	Forme() {
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(0, 6);
		this->forme = Matrice(touteForme[distr(eng)]);
		Y = 0;
		X = 3;
		if (!textureForme.loadFromFile(this->lien))
			EXIT_FAILURE;
	}

	inline Matrice getForme() { return this->forme; }
	inline int getX() { return this->X; }
	inline int getY() { return this->Y; }
	inline void setX(int x) { this->X = x; }
	inline void setY(int x) { this->Y = x; }
	inline void dropeForme() { this->Y++; }
	inline void deplacementGauche() { this->X--; }
	inline void deplacementDroite() { this->X++; }

	void rotate(Matrice terrain) {
		this->forme.rotate();
		colisionGauche(terrain);
		if (verifRotate(terrain)) {
			colisionDroite(terrain);
			colisionBas(terrain);
		}
		else
			this->forme.unrotate();
	}

	bool verifRotate(Matrice terrain) {
		int i, j;
		for (i = X; i < X + 4 && i < terrain.getSizeX(); ++i)
			for (j = Y; j < Y + 4 && j < terrain.getSizeY(); ++j)
				if (forme.get(i - X, j - Y))
					if (terrain.get(i, j))
						return false;
		return true;
	}

	//Retourne le bloc actif le plus a droite 
	int limiteDroite() {
		int bloc = 0, i, j;
		for (i = 0; i < 4; ++i)
			for (j = 0; j < 4; ++j)
				if (forme.get(i, j) != 0 && i > bloc)
					bloc = i;
		return bloc+1;
	}

	//Retourne le bloc actif le plus a gauche 
	int limiteGauche() {
		int bloc = 5, i, j;
		for (i = 0; i < 4; ++i)
			for (j = 0; j < 4; ++j)
				if (forme.get(i, j) != 0 && i < bloc)
					bloc = i;
		return bloc;
	}

	//Retourne le bloc actif le plus en bas 
	int limiteBas() {
		int bloc = 0, i, j;
		for (i = 0; i < 4; ++i)
			for (j = 0; j < 4; ++j)
				if (forme.get(i, j) && j > bloc)
					bloc = j;
		return bloc;
	}

	bool colisionBas(Matrice terrain) {
		int ret = limiteBas();
		if (this->Y + ret > terrain.getSizeY() - 1) {
			this->Y = terrain.getSizeY() - ret - 1;
			return true;
		}
		return false;
	}

	void colisionInstantane(Matrice terrain) {
		int ret = limiteBas();
		while(!colisionFormeBas(terrain) && this->Y + ret < terrain.getSizeY() - 1){
			Y++;
		}
	}

	void colisionGauche(Matrice terrain) {
		if (this->X + limiteGauche() < 0)
			this->X++;
	}

	void colisionDroite(Matrice terrain) {
		if (this->X + limiteDroite() > terrain.getSizeX())
			this->X--;
	}

	bool colisionFormeBas(Matrice terrain) {
		int i, j;
		for (i = X; i < X + 4 && i < terrain.getSizeX(); ++i)
			for (j = Y; j < Y + 4 && j < terrain.getSizeY(); ++j)
				if (forme.get(i - X, j - Y)) {
					if (terrain.get(i, j)) {
						this->Y--;
						return true;
					}
				}
		return false;
	}

	bool colisionFormeGauche(Matrice terrain) {
		int i, j;
		for (i = X; i < X + 4 && i < terrain.getSizeX(); ++i)
			for (j = Y; j < Y + 4 && j < terrain.getSizeY(); ++j)
				if (forme.get(i - X, j - Y))
					if (terrain.get(i, j)) {
						this->X++;
						return true;
					}
		return false;
	}

	bool colisionFormeDroite(Matrice terrain) {
		int i, j;
		for (i = X; i < X + 4 && i < terrain.getSizeX(); ++i)
			for (j = Y; j < Y + 4 && j < terrain.getSizeY(); ++j)
				if (forme.get(i - X, j - Y))
					if (terrain.get(i, j)) {
						this->X--;
						return true;
					}
		return false;
	}

	inline bool gameOver() { return Y < 2; }

	bool actualiseForme(sf::Vector2u tailleTuille)
	{
		int i, j;
		sf::Vertex* carre;
		int nbCase, posX, posY;

		plateau.clear();
		plateau.setPrimitiveType(sf::Quads);
		plateau.resize(SIZE_FORME * SIZE_FORME * 4);

		// on remplit le tableau de vertex, avec un carré par tuile
		for (i = 0; i < SIZE_FORME; i++) {
			for (j = 0; j < SIZE_FORME; j++) {
				nbCase = forme.get(i, j);
				if (nbCase) {
					// on en déduit sa position dans la texture du tileset
					posX = nbCase % (textureForme.getSize().x / tailleTuille.x);
					posY = nbCase / (textureForme.getSize().x / tailleTuille.x);

					// on récupère un pointeur vers le carré à définir dans le tableau de vertex
					carre = &plateau[(i + j * SIZE_FORME) * 4];

					// on définit ses quatre coins
					carre[0].position = sf::Vector2f(i * tailleTuille.x + tailleTuille.x * getX(), j * tailleTuille.y + tailleTuille.y * getY());
					carre[1].position = sf::Vector2f((i + 1) * tailleTuille.x + tailleTuille.x * getX(), j * tailleTuille.y + tailleTuille.y * getY());
					carre[2].position = sf::Vector2f((i + 1) * tailleTuille.x + tailleTuille.x * getX(), (j + 1) * tailleTuille.y + tailleTuille.y * getY());
					carre[3].position = sf::Vector2f(i * tailleTuille.x + tailleTuille.x * getX(), (j + 1) * tailleTuille.y + tailleTuille.y * getY());

					// on définit ses quatre coordonnées de texture
					carre[0].texCoords = sf::Vector2f(posX * tailleTuille.x, posY * tailleTuille.y);
					carre[1].texCoords = sf::Vector2f((posX + 1) * tailleTuille.x, posY * tailleTuille.y);
					carre[2].texCoords = sf::Vector2f((posX + 1) * tailleTuille.x, (posY + 1) * tailleTuille.y);
					carre[3].texCoords = sf::Vector2f(posX * tailleTuille.x, (posY + 1) * tailleTuille.y);
				}
			}
		}
		return true;
	}

	string lien = "Texture/palette.png";

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// on applique la transformation
		states.transform = getTransform();

		// on applique la texture du tileset
		states.texture = &textureForme;

		// et on dessine enfin le tableau de vertex
		target.draw(plateau, states);
	}

	sf::VertexArray plateau;
	sf::Texture textureForme;
};