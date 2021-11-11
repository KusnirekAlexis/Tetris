#pragma once
#include <iostream>
#include <cassert> 
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

using namespace std;

class Matrice {
private:
    int SIZE_X, SIZE_Y;
    int** matrice;
public:
    Matrice(int X, int Y) {
        int i, j;
        this->SIZE_Y = X;
        this->SIZE_X = Y;
        this->matrice = new int* [SIZE_X];

        for (i = 0; i < SIZE_X; ++i) {
            matrice[i] = new int[SIZE_Y];
            for (j = 0; j < SIZE_Y; ++j) {
                matrice[i][j] = 0;
            }
        }
    }

    Matrice(int tab[4][4]) {
        int i, j;
        this->SIZE_Y = 4;
        this->SIZE_X = 4;
        this->matrice = new int* [SIZE_X];

        for (i = 0; i < SIZE_X; ++i) {
            matrice[i] = new int[SIZE_Y];
            for (j = 0; j < SIZE_Y; ++j) {
                matrice[i][j] = tab[i][j];
            }
        }
    }

    /*~Matrice() {
        int i;
        for (i = 0; i < SIZE_Y; ++i)
            delete[] matrice[i];
        delete[] matrice;
    }*/

    void set(int X, int Y, int value) {
        assert(0 < X < this->SIZE_X - 1 && 0 < Y < this->SIZE_Y - 1);
        matrice[X][Y] = value;
    }

    inline int get(int x, int y) { return matrice[x][y]; }
    inline int getSizeX() { return SIZE_X; }
    inline int getSizeY() { return SIZE_Y; }


    void insert(int X, int Y, Matrice forme) {
        int i, j;
        for (i = X; i < X + forme.SIZE_X; ++i)
            for (j = Y; j < Y + forme.SIZE_Y; ++j)
                if(forme.get(i - X, j - Y))
                    set(i, j, forme.get(i - X, j - Y));
    }

    void rotate() {
        int i, j;
        int ret = SIZE_Y;
        this->SIZE_Y = SIZE_X;
        this->SIZE_X = ret;

        int** retMat = matrice;

        this->matrice = new int* [SIZE_X];

        for (i = 0; i < SIZE_X; ++i) {
            matrice[i] = new int[SIZE_Y];
            for (j = 0; j < SIZE_Y; ++j) {
                this->matrice[i][3 - j] = retMat[j][i];
            }
        }
    }

    void unrotate() {
        int i, j;
        int ret = SIZE_Y;
        this->SIZE_Y = SIZE_X;
        this->SIZE_X = ret;

        int** retMat = matrice;

        this->matrice = new int* [SIZE_X];

        for (i = SIZE_X - 1; i >= 0; --i) {
            matrice[i] = new int[SIZE_Y];
            for (j = SIZE_Y - 1; j >= 0; --j) {
                this->matrice[i][j] = retMat[j][3 - i];
            }
        }
    }

    //En fonction de la taille du vecteur le mutiplicateur de score sera plus grand
    vector<int> detecteLignePleine() {
        int i, j;
        bool lignePleine;
        vector<int> result;
        for (i = 0; i < this->SIZE_Y; ++i) {
            lignePleine = true;
            for (j = 0; j < this->SIZE_X; ++j) {
                if (!this->get(j, i))
                    lignePleine = false;
            }
            if (lignePleine)
                result.push_back(i);
        }
        return result;
    }

    void retireLignePleine(vector<int> nbLigne) {
        int i, x, y, ligneActu;
        for (int i = 0; i < nbLigne.size(); i++) {
            ligneActu = nbLigne[i];
            for (x = 0; x < this->SIZE_X; ++x)
                for (y = ligneActu; y > 0; --y)
                    matrice[x][y] = matrice[x][y-1];
        }
        for (i = 0; i < SIZE_X; ++i)
            this->matrice[i][0] = 0;
    }

    void afficheMatrice() {
        int i, j;
        for (i = 0; i < SIZE_X; ++i) {
            for (j = 0; j < SIZE_Y; ++j)
                cout << this->matrice[i][j] << " , ";
            cout << endl;
        }
    }
};