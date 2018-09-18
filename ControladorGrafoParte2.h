#ifndef CONTROLADORGRAFOPARTE2_H
#define CONTROLADORGRAFOPARTE2_H
#include "GrafoParte2.h"

class ControladorGrafoParte2
{
private:
	GrafoParte2 *g;
	GrafoParte2 *gAux;
protected:
	
public:
	ControladorGrafoParte2(char arquivo[50]);
	~ControladorGrafoParte2();
	void criarVertice(int id, int x, int y);
	void criarAresta(int numVertice, int numOutroVertie, int pesoVertice);
	void excluirVertice(GrafoParte2 *g, int idVertice);
	void excluirAresta(VerticeParte2 *v);
	void auxExcluirAresta(GrafoParte2 *g, int id);
	int colorir();
	void auxColorir(int id, int cor);
	void GulosoAtribuicaoCanal();
	void GulosoRandomizadoAtribuicaoCanal();
	void GulosoRandomizadoReativoAtribuicaoCanal();
	GrafoParte2 * copiar(GrafoParte2 *g);
};

#endif