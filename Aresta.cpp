#include "Aresta.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

Aresta::Aresta()
{
	this->iD_No = NULL;
	this->pesoAresta = NULL;
	this->proxAresta = NULL;
}

Aresta::Aresta(int iD_No, float pesoAresta) {
    this->iD_No = iD_No;
    this->pesoAresta = pesoAresta;
    this->proxAresta = NULL;
}

Aresta::~Aresta() {

}

void Aresta::setPesoAresta(float pesoAr)
{
    this->pesoAresta = pesoAr;
}
float Aresta::getPesoAresta ()
{
    return this->pesoAresta;
}
void Aresta::setiD_No(int id_No)
{
    this->iD_No = id_No;
}
int Aresta::getId_No()
{
    return this->iD_No;
}
void Aresta::setProxAresta(Aresta *proximaAresta)
{
    this->proxAresta = proximaAresta;
}
Aresta * Aresta::getProxAresta ()
{
    return this->proxAresta;
}

