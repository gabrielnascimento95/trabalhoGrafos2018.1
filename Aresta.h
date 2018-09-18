#ifndef ARESTA_H
#define ARESTA_H

class Aresta{
    private:
        float pesoAresta; // Peso da aresta informado na leitura do arquivo
        int iD_No; // ID do Vértice que está conectado ao vértice que pertence a aresta
        Aresta *proxAresta; // Próxima aresta do vértice da aresta
    public:
    	Aresta();
        Aresta(int id_No, float pAresta);
        ~Aresta();
        void setPesoAresta(float pesoAr);
        float getPesoAresta ();
        void setiD_No(int id_No);
        int getId_No();
        void setProxAresta(Aresta *proximaAresta);
        Aresta *getProxAresta ();
};

#endif /* ARESTA_H */

