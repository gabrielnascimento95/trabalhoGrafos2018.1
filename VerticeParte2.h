#ifndef VERTICEPARTE2_H
#define VERTICEPARTE2_H
#include "Aresta.h"

class VerticeParte2
{
private:
	int id;
	int x;
	int y;
	bool visitado;
	int cor;
	int numArestas;
	VerticeParte2 *prox;
	Aresta *listaAresta;
protected:
	
public:
	VerticeParte2(int id, int x, int y);
	~VerticeParte2();
	VerticeParte2();
	void setID (int id);
	int getID();
	void setX (int x);
	int getX ();
	void setY (int y);
	int getY ();
	void setVisitado(bool visitado);
	bool getVisitado();
	void setCor(int cor);
	int getCor();
	void setNumArestas (int n);
	int getNumArestas ();
	void setProx (VerticeParte2 *v);
	VerticeParte2 *getProx();
	void setAresta (Aresta *a);
	Aresta *getAresta ();
};

#endif