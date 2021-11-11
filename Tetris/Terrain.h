#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Matrice.h"

using namespace std;

class Terrain: public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray plateau;
    sf::Texture textureMap;
public:

    Matrice tableau = Matrice(22, 10);
    string lien;

    inline Matrice getTerrain() { return tableau; }

    bool creerMap(const string lien, sf::Vector2u tailleTuille, unsigned int largeur, unsigned int hauteur, int decalage )
    {
        this->lien = lien;
        int i, j;
        sf::Vertex* carre;
        int nbCase, posX, posY;

        // on charge la texture de la palette
        if (!textureMap.loadFromFile(this->lien))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        plateau.setPrimitiveType(sf::Quads);
        plateau.resize(largeur * hauteur * 4);

        // on remplit le tableau de vertex, avec un carr� par tuile
        for (i = 0; i < largeur; i++) {
            for (j = 0; j < hauteur; j++) {
                // on r�cup�re le num�ro de tuile courant
                nbCase = tableau.get(i, j);

                // on en d�duit sa position dans la texture du tileset
                posX = nbCase % (textureMap.getSize().x / tailleTuille.x +1000);
                posY = nbCase / (textureMap.getSize().x / tailleTuille.x+1000);

                // on r�cup�re un pointeur vers le carr� � d�finir dans le tableau de vertex
                carre = &plateau[(i + j * largeur) * 4];

                // on d�finit ses quatre coins
                carre[0].position = sf::Vector2f(i * tailleTuille.x, j * tailleTuille.y);
                carre[1].position = sf::Vector2f((i + 1) * tailleTuille.x, j * tailleTuille.y);
                carre[2].position = sf::Vector2f((i + 1) * tailleTuille.x, (j + 1) * tailleTuille.y);
                carre[3].position = sf::Vector2f(i * tailleTuille.x, (j + 1) * tailleTuille.y);

                // on d�finit ses quatre coordonn�es de texture
                carre[0].texCoords = sf::Vector2f(posX * tailleTuille.x, posY * tailleTuille.y);
                carre[1].texCoords = sf::Vector2f((posX + 1) * tailleTuille.x, posY * tailleTuille.y);
                carre[2].texCoords = sf::Vector2f((posX + 1) * tailleTuille.x, (posY + 1) * tailleTuille.y);
                carre[3].texCoords = sf::Vector2f(posX * tailleTuille.x, (posY + 1) * tailleTuille.y);
            }
        }
        return true;
    }

    bool actualiseMap(sf::Vector2u tailleTuille, unsigned int largeur, unsigned int hauteur)
    {
        int i, j;
        sf::Vertex* carre;
        int nbCase, posX, posY;

        // on remplit le tableau de vertex, avec un carr� par tuile
        for (i = 0; i < largeur; i++) {
            for (j = 0; j < hauteur; j++) {
                // on r�cup�re le num�ro de tuile courant
                nbCase = tableau.get(i, j);

                // on en d�duit sa position dans la texture du tileset
                posX = nbCase % (textureMap.getSize().x / tailleTuille.x);
                posY = nbCase / (textureMap.getSize().x / tailleTuille.x);

                // on r�cup�re un pointeur vers le carr� � d�finir dans le tableau de vertex
                carre = &plateau[(i + j * largeur) * 4];

                // on d�finit ses quatre coins
                carre[0].position = sf::Vector2f(i * tailleTuille.x, j * tailleTuille.y);
                carre[1].position = sf::Vector2f((i + 1) * tailleTuille.x, j * tailleTuille.y);
                carre[2].position = sf::Vector2f((i + 1) * tailleTuille.x, (j + 1) * tailleTuille.y);
                carre[3].position = sf::Vector2f(i * tailleTuille.x, (j + 1) * tailleTuille.y);

                // on d�finit ses quatre coordonn�es de texture
                carre[0].texCoords = sf::Vector2f(posX * tailleTuille.x, posY * tailleTuille.y);
                carre[1].texCoords = sf::Vector2f((posX + 1) * tailleTuille.x, posY * tailleTuille.y);
                carre[2].texCoords = sf::Vector2f((posX + 1) * tailleTuille.x, (posY + 1) * tailleTuille.y);
                carre[3].texCoords = sf::Vector2f(posX * tailleTuille.x, (posY + 1) * tailleTuille.y);
            }
        }
        return true;
    }

    void restart() {
        tableau = Matrice(22, 10);
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform = getTransform();

        // on applique la texture du tileset
        states.texture = &textureMap;

        // et on dessine enfin le tableau de vertex
        target.draw(plateau, states);
    }
};