#include "Grafo.h"
#include <string.h>
#include <stdlib.h>
#include "Vertice.h"
#include <iostream>

using namespace std;

Grafo::Grafo(int ordem)
{
    this->ordem = ordem;
    this->listaNos = NULL;
	this->grauGrafo = 0;
    this->numArestas = 0;
}

Grafo::Grafo(int ordem, int grauGrafo, int numArestas)
{
    this->ordem = ordem;
    this->grauGrafo = grauGrafo;
    this->numArestas = numArestas;
    this->listaNos = NULL;
}

Grafo::~Grafo() {
	Vertice *v = listaNos;
	while (v != 0)
	{
		Aresta *a = v->GetListaAresta();
		while (a != 0)
		{
			v->SetListaAresta(a->getProxAresta());
			delete a;
		}
		listaNos = v->GetProxNo();
		delete v;
	}
}

int Grafo::GetGrauGrafo() const {
        return this->grauGrafo;
}

void Grafo::SetGrauGrafo(int grauGrafo) {
        this->grauGrafo = grauGrafo;
}

int Grafo::GetNumArestas() const {
        return this->numArestas;
}

void Grafo::SetNumArestas(int numArestas) {
        this->numArestas = numArestas;
}

int Grafo::GetOrdem() const {
        return this->ordem;
}

void Grafo::SetOrdem(int ordem) {
        this->ordem = ordem;
}

Vertice* Grafo::GetListaNos() const {
        return this->listaNos;
}

void Grafo::SetListaNos(Vertice* listaNos) {
        this->listaNos = listaNos;
}
