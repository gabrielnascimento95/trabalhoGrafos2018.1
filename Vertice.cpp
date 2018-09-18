#include "Vertice.h"
#include "Aresta.h"
#include <string.h>
#include <stdlib.h>

using namespace std;


Vertice::Vertice(int iD) {
    this->iD = iD;
    this->pesoNo = 0;
    this->listaAresta = NULL;
    this->proxNo = NULL;
    this->cor = -1;
}

Vertice::~Vertice() {

}

int Vertice::GetID() const {
        return this->iD;
}

void Vertice::SetID(int iD) {
        this->iD = iD;
}

Aresta* Vertice::GetListaAresta() const {
        return this->listaAresta;
}

void Vertice::SetListaAresta(Aresta* listaAresta) {
        this->listaAresta = listaAresta;
}

int Vertice::GetPesoNo() const {
        return this->pesoNo;
}

void Vertice::SetPesoNo(float pesoNo) {
        this->pesoNo = pesoNo;
}

Vertice* Vertice::GetProxNo() const {
        return this->proxNo;
}

void Vertice::SetProxNo(Vertice* proxNo) {
        this->proxNo = proxNo;
}

int Vertice::getCor()
{
	return this->cor;
}

void Vertice::setCor(int cor)
{
	this->cor = cor;
}
