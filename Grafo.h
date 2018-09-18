#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"

class Grafo{
    private:
        int ordem; // Número de vértices
        int grauGrafo; // Não foi utilizado, mas foi mantido caso seja necessário em implementações futuras
        int numArestas; // Número de arestas do grafo
        Vertice *listaNos; // Lista de vértices do grafo
    public:
        Grafo(int ordem);
        Grafo(int ordem, int grauGrafo, int numArestas);
		~Grafo();
        int GetGrauGrafo() const;
        void SetGrauGrafo(int grauGrafo);
        int GetNumArestas() const;
        void SetNumArestas(int numArestas);
        int GetOrdem() const;
        void SetOrdem(int ordem);
        Vertice* GetListaNos() const;
        void SetListaNos(Vertice* listaNos);
};

#endif /* GRAFO_H */

