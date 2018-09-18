#ifndef VERTICE_H
#define VERTICE_H
#include "Aresta.h"

class Vertice {
private:
    int iD; // Identificador 
    int pesoNo; // Número de arestas 
    Vertice *proxNo; // Próximo vértice
    Aresta *listaAresta; // Lista de Arestas do vértice
    int cor; // Cor utilizado para grafo bipartido

public:

    Vertice(int iD);
    ~Vertice();
    int GetID() const;
    void SetID(int iD);
    Aresta* GetListaAresta() const;
    void SetListaAresta(Aresta* listaAresta);
    int GetPesoNo() const;
    void SetPesoNo(float pesoNo);
    Vertice* GetProxNo() const;
    void SetProxNo(Vertice* proxNo);
	void setCor(int cor);
	int getCor();
};

#endif /* VERTICE_H */

