#pragma region include
#include <SFML/Audio.hpp>
#include "Terrain.h"
#include "Forme.h"
#include <string>
#include <fstream>
#include <sstream>
#pragma endregion include

string lectureScore();

#pragma region Variable
sf::Image icon;
vector<int> lignePleine;
int score = 0;
int highestscore = stoi(lectureScore());
const int SIZE_CUBE = 30;
const int SIZE_TABX = 10;
const int SIZE_TABY = 20;
Forme formeReserve;
Forme formeSuivante = Forme();
Forme ret;
int nbFormeReserve = 0;
int nbLigneActu = 0;
int menuOn = 1;
#pragma endregion Variable

#pragma region petiteFonction
int scoreAjouter(vector<int> ligne) {
    int len = ligne.size();
    switch (len) {
    case 1:
        return 40;
    case 2:
        return 100;
    case 3:
        return 300;
    case 4:
        return 1200;
    default:
        return 0;
    }
}

int levels(int nbLigne) {
    if (nbLigne < 10)
        return 1000;
    else if (nbLigne < 20)
        return 900;
    else if (nbLigne < 30)
        return 800;
    else if (nbLigne < 40)
        return 700;
    else if (nbLigne < 50)
        return 600;
    else return 500;
}

int nbLevels(int nbLigne) {
    if (nbLigne < 10)
        return 1;
    else if (nbLigne < 20)
        return 2;
    else if (nbLigne < 30)
        return 3;
    else if (nbLigne < 40)
        return 4;
    else if (nbLigne < 50)
        return 5;
    else return 6;
}
#pragma endregion petiteFonction

#pragma region lectureEcritureFichier
void ecritureScore(int nombre) {
    string nb = to_string(nombre);
    ofstream fichier("Score/score.txt");
    if (fichier)
        fichier << nb << endl;
    else
        EXIT_FAILURE;
}

string lectureScore() {
    ifstream fichier("Score/score.txt");
    if (fichier) {
        string ligne;
        getline(fichier, ligne);
        return ligne;
    }
    else
        EXIT_FAILURE;
}
#pragma endregion lectureEcritureFichier

int main()
{
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(700, 900), "Tetris");
    if (!icon.loadFromFile("Texture/icone.png"))
        EXIT_FAILURE;

    window.setIcon(32, 32, icon.getPixelsPtr());

    //Backgound
    sf::Texture fond;
    if (!fond.loadFromFile("Texture/fond.png", sf::IntRect(0, 0, 700, 900)))
        EXIT_FAILURE;
    sf::RectangleShape rec(sf::Vector2f(700.f, 900.f));
    rec.setTexture(&fond);
    rec.setTextureRect(sf::IntRect(0, 0, 700, 900));

    //MUSIQUE
    /*sf::SoundBuffer buffer;
    sf::Sound sound;
    if (!buffer.loadFromFile("Music/MainTheme.wav"))
        return -1;
    sound.setBuffer(buffer);
    sound.play();
    sound.setVolume(50.f);*/

    //Texte
#pragma region interfaceJeu
    sf::Font font;
    if (!font.loadFromFile("Texte/ArialCyr.ttf"))
        EXIT_FAILURE;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score : " + to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(100, 0);

    sf::Text hightscoreText;
    hightscoreText.setFont(font);
    hightscoreText.setString("highest score  : " + lectureScore());
    hightscoreText.setCharacterSize(24);
    hightscoreText.setFillColor(sf::Color::White);

    sf::Text nextForme;
    nextForme.setFont(font);
    nextForme.setString("Forme suivante :");
    nextForme.setCharacterSize(24);
    nextForme.setFillColor(sf::Color::White);
    nextForme.setPosition(400, 250);

    sf::Text reserve;
    reserve.setFont(font);
    reserve.setString("Reserve  :");
    reserve.setCharacterSize(24);
    reserve.setFillColor(sf::Color::White);
    reserve.setPosition(400, 50);

    sf::Text leveling;
    leveling.setFont(font);
    leveling.setString("Level  : " + to_string(nbLevels(0)));
    leveling.setCharacterSize(24);
    leveling.setFillColor(sf::Color::White);
    leveling.setPosition(400, 500);
#pragma endregion interfaceJeu

#pragma region Menu
    sf::Texture titre;
    if (!titre.loadFromFile("Texture/titre.png"))
        EXIT_FAILURE;
    sf::RectangleShape tetris(sf::Vector2f(500, 150));
    tetris.setTexture(&titre);
    tetris.setPosition(100, 50);

    sf::Text start;
    start.setFont(font);
    start.setString("Press Spacebar to start");
    start.setCharacterSize(24);
    start.setFillColor(sf::Color::White);
    start.setPosition(200, 250);

    sf::Text controle1;
    controle1.setFont(font);
    controle1.setString("<- : Go to the right");
    controle1.setCharacterSize(24);
    controle1.setFillColor(sf::Color::White);
    controle1.setPosition(200, 400);

    sf::Text controle2;
    controle2.setFont(font);
    controle2.setString("-> : Go to the left");
    controle2.setCharacterSize(24);
    controle2.setFillColor(sf::Color::White);
    controle2.setPosition(200, 450);

    sf::Text controle3;
    controle3.setFont(font);
    controle3.setString("Up : Rotate");
    controle3.setCharacterSize(24);
    controle3.setFillColor(sf::Color::White);
    controle3.setPosition(200, 500);

    sf::Text controle4;
    controle4.setFont(font);
    controle4.setString("Down : Soft drop");
    controle4.setCharacterSize(24);
    controle4.setFillColor(sf::Color::White);
    controle4.setPosition(200, 550);

    sf::Text controle5;
    controle5.setFont(font);
    controle5.setString("Space : Hold");
    controle5.setCharacterSize(24);
    controle5.setFillColor(sf::Color::White);
    controle5.setPosition(200, 600);

    sf::Text controle6;
    controle6.setFont(font);
    controle6.setString("C : Hard drop");
    controle6.setCharacterSize(24);
    controle6.setFillColor(sf::Color::White);
    controle6.setPosition(200, 650);
#pragma endregion Menu

    Terrain terrain;
    if(terrain.creerMap("Texture/palette.png", sf::Vector2u(30, 30), 10, 22, 100))
        EXIT_FAILURE;
    terrain.setPosition(100,100);

    Forme forme;
    forme.setPosition(100, 100);
    forme.actualiseForme(sf::Vector2u(30, 30));
    terrain.actualiseMap(sf::Vector2u(30, 30), 10, 22);

    sf::Clock travelTime;
    sf::Clock inputPlayer;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (!menuOn) {
            //Montre la forme a suivre
            formeSuivante.setPosition(400, 300);
            formeSuivante.actualiseForme(sf::Vector2u(30, 30));
            //DESCENTE
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && inputPlayer.getElapsedTime().asMilliseconds() > 50) || travelTime.getElapsedTime().asMilliseconds() > levels(nbLigneActu)) {
                forme.dropeForme();
                if (forme.colisionFormeBas(terrain.getTerrain()) || forme.colisionBas(terrain.getTerrain())) {
                    if (forme.gameOver()) {
                        terrain.restart();
                        menuOn = 1;
                        nbLigneActu = 0;
                        if (score > highestscore) {
                            ecritureScore(score);
                            highestscore = stoi(lectureScore());
                            hightscoreText.setString("highest score  : " + to_string(highestscore));
                        }
                        score = 0;
                    }
                    else {
                        terrain.tableau.insert(forme.getX(), forme.getY(), forme.forme);

                        //Verifie si des lignes on etais remplit
                        lignePleine = terrain.getTerrain().detecteLignePleine();
                        score += scoreAjouter(lignePleine);
                        scoreText.setString("Score : " + to_string(score));
                        nbLigneActu += lignePleine.size();
                        leveling.setString("Level  :" + to_string(nbLevels(nbLigneActu)));
                        terrain.getTerrain().retireLignePleine(lignePleine);
                        lignePleine.clear();
                    }

                    terrain.actualiseMap(sf::Vector2u(30, 30), 10, 22);
                    forme = formeSuivante;
                    formeSuivante = Forme();
                    forme.setPosition(100, 100);
                }
                forme.actualiseForme(sf::Vector2u(30, 30));
                inputPlayer.restart();
                travelTime.restart();
            }
            //DEPLACEMENT GAUCHE
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && inputPlayer.getElapsedTime().asMilliseconds() > 100) {
                forme.deplacementGauche();
                forme.colisionGauche(terrain.getTerrain());
                forme.colisionFormeGauche(terrain.getTerrain());
                forme.actualiseForme(sf::Vector2u(30, 30));
                inputPlayer.restart();
            }
            //DEPLACEMENT DROITE
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && inputPlayer.getElapsedTime().asMilliseconds() > 100) {
                forme.deplacementDroite();
                forme.colisionFormeDroite(terrain.getTerrain());
                forme.colisionDroite(terrain.getTerrain());
                forme.actualiseForme(sf::Vector2u(30, 30));
                inputPlayer.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && inputPlayer.getElapsedTime().asMilliseconds() > 100) {
                forme.rotate(terrain.getTerrain());
                forme.actualiseForme(sf::Vector2u(30, 30));
                inputPlayer.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && inputPlayer.getElapsedTime().asMilliseconds() > 150) {
                forme.colisionInstantane(terrain.getTerrain());
                if (forme.gameOver()) {
                    terrain.restart();
                    menuOn = 1;
                    nbLigneActu = 0;
                    if (score > highestscore) {
                        ecritureScore(score);
                        highestscore = stoi(lectureScore());
                        hightscoreText.setString("highest score  : " + to_string(highestscore));
                    }
                    score = 0;
                }
                else {
                    terrain.tableau.insert(forme.getX(), forme.getY(), forme.forme);

                    //Verifie si des lignes on etais remplit
                    lignePleine = terrain.getTerrain().detecteLignePleine();
                    score += scoreAjouter(lignePleine);
                    scoreText.setString("Score : " + to_string(score));
                    nbLigneActu += lignePleine.size();
                    leveling.setString("Level  :" + to_string(nbLevels(nbLigneActu)));
                    terrain.getTerrain().retireLignePleine(lignePleine);
                    lignePleine.clear();
                }
                terrain.actualiseMap(sf::Vector2u(30, 30), 10, 22);
                forme = formeSuivante;
                formeSuivante = Forme();
                forme.setPosition(100, 100);
                forme.actualiseForme(sf::Vector2u(30, 30));
                inputPlayer.restart();
                travelTime.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && inputPlayer.getElapsedTime().asMilliseconds() > 100) {
                forme.setX(3);
                forme.setY(0);
                if (nbFormeReserve) {
                    ret = forme;
                    forme = formeReserve;
                    formeReserve = ret;
                }
                else {
                    formeReserve = forme;
                    forme = formeSuivante;
                    formeSuivante = Forme();
                    nbFormeReserve = 1;
                }
                forme.setPosition(100, 100);
                formeReserve.setPosition(380, 100);
                formeReserve.actualiseForme(sf::Vector2u(30, 30));

                forme.actualiseForme(sf::Vector2u(30, 30));
                inputPlayer.restart();
            }
            hightscoreText.setPosition(100, 50);
            window.draw(rec);
            window.draw(terrain);
            window.draw(forme);
            window.draw(formeReserve);
            window.draw(formeSuivante);
            window.draw(scoreText);
            window.draw(hightscoreText);
            window.draw(nextForme);
            window.draw(reserve);
            window.draw(leveling);
            window.display();
            window.clear();
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                menuOn = 0;
            }
            hightscoreText.setPosition(200, 350);
            window.draw(rec);
            window.draw(tetris);
            window.draw(start);
            window.draw(hightscoreText);
            window.draw(controle1);
            window.draw(controle2);
            window.draw(controle3);
            window.draw(controle4);
            window.draw(controle5);
            window.draw(controle6);
            window.display();
            window.clear();
        }
    }

    return 0;
}