#include <error>
class Forme {
	virtual int** getForme() {
		throw runtime_error("Impossible");
	}
	virtual void rotation() {
		throw runtime_error("Impossible");
	}
	//getForme qui est commun a tous
	//un class par forme et donc faire cune class forme partielement vide ?
	//les forme dessende tout les x temps (chrono)
	//rajouté un chrono pour faire dessendre les forme pour pas que ca aillent trop vite
};

class formeCube : public Forme {
private:
public:
	virtual int** getForme() {
		int** tab{ {1,1},{1,1} };
		return tab;
	}
};

class formeBarre : public Forme {
	//Barre
	{0, 1, 0, 0
	0, 1, 0, 0
	0, 1, 0, 0
	0, 1, 0, 0}

	{1, 1, 1, 1
	0, 0, 0, 0
	0, 0, 0, 0
	0, 0, 0, 0}
};

class formeZ : public Forme {
	//Z
	{1, 1, 0
	0, 1, 1
	0, 0, 0}

	{0, 0, 1
	0, 1, 1
	0, 1, 0}
};

class formeZInverse : public Forme {
	//Z inversé
	{0, 1, 1
	1, 1, 0
	0, 0, 0}

	{0, 1, 0
	0, 1, 1
	0, 0, 1}
};

class formeL : public Forme {
	//L
	{0, 1, 0
	0, 1, 0
	0, 1, 1}

	{1, 1, 1
	1, 0, 0
	0, 0, 0}

	{1, 1, 0
	0, 1, 0
	0, 1, 0}

	{0, 0, 1
	1, 1, 1
	0, 0, 0}
};

class formeLInverse : public Forme {
	//L inversé
	{0, 1, 0
	0, 1, 0
	1, 1, 0}

	{1, 0, 0
	1, 1, 1
	0, 0, 0}

	{0, 1, 1
	0, 1, 0
	0, 1, 0}

	{1, 1, 1
	0, 0, 1
	0, 0, 0}
};

class formePyramide : public Forme {
	//pyramide
	{0, 1, 0
	1, 1, 1
	0, 0, 0}

	{0, 1, 0
	0, 1, 1
	0, 1, 0}

	{1, 1, 1
	0, 1, 0
	0, 0, 0}

	{0, 1, 0
	1, 1, 0
	0, 1, 0}
};