#ifndef CONTROLADORGRAFO_H
#define CONTROLADORGRAFO_H
#include "Grafo.h"
#include "Vertice.h"

class ControladorGrafo
{
private:
	int tipoGrafo; // Grafo direcionado ou não direcionado
	Grafo *g; // Grafo
protected:
	
public: // Comentários das funções abaixo se encontram no .cpp
	ControladorGrafo(int tipoGrafo, char arquivo[50]);
	~ControladorGrafo();
	int getTipoGrafo ();
	void criarVerticeIndividual(int id);
	void criarVerticeExec();
	void criarArestaExec();
    void criarVertice(int id, int id2, float pesoAresta);
	void insereVerticeLista(Vertice *v);
	void insereVerticeAresta(Vertice *v, int id2, float pesoAresta);
	void excluirVertice();
	void excluirAresta(Vertice *v);
	void excluirAresta2(int idV1, int idV2);
	void excluirAresta2exec();
	void auxExcluirAresta(int id);
	int auxExcluirAresta2(int idV1, int idV2);
	void imprimeGrafo();
	void imprimeVertice();
	int existeVertice(int idV);
	int existeAresta(int idV1, int idV2);
	void atualizarGrauVerticePositivo(Vertice *v);
	void atualizarGrauVerticeNegativo(Vertice *v);
	void atualizarNumArestasPositivo();
	void atualizarNumArestasNegativo();
	void atualizarOrdemPositivo();
	void atualizarOrdemNegativo();
	void auxGrauDadoVertice();
	int grauSaidaVertice(int id);
	int grauEntradaVertice(int id);
	void ordemDoGrafo();
	void verificTrivial();
	void verificNulo();
	void verificKRegularidade();
	void auxVizinhanca();
	void vizinhanca(int tipoVizinhanca, int idVertice);
    void auxVerificMultigrafo();
    int verificMultigrafo();
	void verificGrafoCompleto();
	void sequenciaGrauVertices();
	int auxSequenciaGrauVertices(int idVertice);
	void gravarGrafo(char arquivo[100]);
	void QuickSort(int vet[], int inic, int fim);
	int particao(int vet[], int inic, int fim);
	void ehBipartido();
	bool auxEhBipartido(Vertice *v, int cor);
};

#endif /* CONTROLADORGRAFO_H */
