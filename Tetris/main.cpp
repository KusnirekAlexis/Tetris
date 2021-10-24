#pragma region include
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include "Terrain.h"
#include "Forme.cpp"
#pragma endregion include

#pragma region Variable
sf::Image icon;
#pragma endregion Variable

/*
score
montrer la forme qui va suivre
forme constituer de plusieur carré serai plus simple pour les collision 
systeme de matrice -> 0 si vide, 1 si plein (a voir si je mes des numéros different en fonction des couleur)
*/
int score = 0;
const int SIZE_CUBE = 30;
const int SIZE_TABX = 10;
const int SIZE_TABY = 20;

int main()
{
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(SIZE_TABX * SIZE_CUBE, SIZE_TABY * SIZE_CUBE), "Tetris");
    if (!icon.loadFromFile("Texture/icone.png"))
        EXIT_FAILURE;

    window.setIcon(32, 32, icon.getPixelsPtr());

    Terrain terrain;
    if(terrain.creerMap("Texture/palette.png", sf::Vector2u(30, 30), 10, 20))
        EXIT_FAILURE;

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            rectangle.move(0.0, 1.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rectangle.move(-1.0, 0.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rectangle.move(1.0, 0.0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rectangle.move(0.0, -1.0);
        }*/

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.draw(terrain);
        window.display();
        window.clear();
    }

    return 0;
}