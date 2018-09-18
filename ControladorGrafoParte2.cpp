#include "ControladorGrafoParte2.h"
#include "GrafoParte2.h"
#include "VerticeParte2.h"
#include "Aresta.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

ControladorGrafoParte2::ControladorGrafoParte2(char arquivo[50])
{
	int id = 0;
	g = new GrafoParte2();
	FILE *file;
	file = fopen(arquivo, "r"); // Abre o arquivo
	if (file == NULL)  // Se houve erro na abertura, emite mensagem
	{
		printf("Algum erro com o endereço do documento");
		return;
	}
	while (!feof(file)) // Leitura do arquivo
	{
		int x, y;
		fscanf(file, "%d %d", &x, &y); // Realiza a leitura do valor x e y do ponto
		criarVertice(id, x, y); // Cria o vértice com id, valor x e valor y
		id++;
	}
	fclose(file);
	VerticeParte2 *v = g->getListaNos();
	g->setOrdem(id); // Coloca a ordem do grafo com o número de vértices
	int lc = id + 1; 
	int matriz[id][lc]; // Cria uma matriz com uma coluna a mais para receber o valor da média das linhas
	for (int i = 0; i < id; i++) // Popula a matriz
	{
		int media = 0;
		VerticeParte2 *aux = g->getListaNos();
		for (int j = 0; j < lc; j++)
		{
			if(i != j && j < lc-1) // Responsável por calcular a distância entre todos os pontos
			{
				int auxVal1 = aux->getX() - v->getX();
				int auxVal2 = aux->getY() - v->getY();
				auxVal1 = auxVal1 * auxVal1;
				auxVal2 = auxVal2 * auxVal2;
				int valFinal = auxVal1 + auxVal2;
				valFinal = sqrt(valFinal);
				matriz[i][j] = int (valFinal); 
				media = media + matriz[i][j];	
				aux = aux->getProx(); 
			}
			if (i == j)
			{
				matriz[i][j] = 0;
				aux = aux->getProx();
			}
		}
		matriz[i][id] = (int)media/(id-1);
		v = v->getProx();
	}
	if (id < 100) // Gera o grafo de conflito para instâncias menoers que 100
	{
		for (int i = 0; i < id; i++)
		{
			for (int j = 0; j < id; j++)
			{
				if (matriz[i][j] <= matriz[i][id]*0.3)
				{
					criarAresta(i, j, matriz[i][j]);	
					criarAresta(j, i, matriz[i][j]);	
				}
			}
		}
	}
	if (id > 100 && id < 400) // Gera o grafo de conflito para instâncias maiores que 100 e menores que 400
	{
		for (int i = 0; i < id; i++)
		{
			for (int j = 0; j < id; j++)
			{
				if (matriz[i][j] <= matriz[i][id]*0.10)
				{
					criarAresta(i, j, matriz[i][j]);	
					criarAresta(j, i, matriz[i][j]);	
				}
			}
		}
	}
	if (id > 400) // Gera o grafo de conflito para instâncias maiores que 400
	{
		for (int i = 0; i < id; i++)
		{
			for (int j = 0; j < id; j++)
			{
				if (matriz[i][j] <= matriz[i][id]*0.075)
				{
					criarAresta(i, j, matriz[i][j]);	
					criarAresta(j, i, matriz[i][j]);	
				}
			}
		}
	}
	int numCores = colorir(); // Tenta colorir com 3 cores
	cout << "Numero de cores utilizadas: " << numCores << endl;
	/* Infelizmente, faltou tentar realizar a atribuição de canais */
}

ControladorGrafoParte2::~ControladorGrafoParte2()
{
	
}

void ControladorGrafoParte2::criarVertice(int id, int x, int y) // Responsável por criar o vértice
{
	VerticeParte2 *v = new VerticeParte2(id, x, y);
	if (g->getListaNos() == NULL)
	{
		g->setListaNos(v);
	}
	else
	{
		VerticeParte2 *aux = g->getListaNos();
		while (aux->getProx() != NULL)
		{
			aux = aux->getProx();
		}
		aux->setProx(v);	
	  }	
}

void ControladorGrafoParte2::criarAresta(int numVertice, int numOutroVertice, int pesoVertice) //Responsável por criar a aresta entre dois vértices
{
	if (numVertice != numOutroVertice)
	{
		VerticeParte2 *v = g->getListaNos();
		while (v != NULL)
		{
			if (v->getID() == numVertice)
			{
				if (v->getAresta() != NULL)
				{
					Aresta *a = v->getAresta();	
					while (a->getProxAresta() != NULL)
					{
						if (a->getId_No() == numOutroVertice)
						{
							return;
						}
						a = a->getProxAresta();
					}
					if (a->getId_No() == numOutroVertice) 
					{
						return;
					}
					Aresta *aux = new Aresta(numOutroVertice, pesoVertice);
					a->setProxAresta(aux);
					int numArestas = v->getNumArestas();
					numArestas++;
					v->setNumArestas(numArestas);
					return;	
				}
				else
				{
					Aresta *a = new Aresta(numOutroVertice, pesoVertice);
					v->setAresta(a);
					v->setNumArestas(1);
					return;
				}
			}
			v = v->getProx();
		}
	}
}

void ControladorGrafoParte2::excluirVertice(GrafoParte2 *g, int idVertice)
{
	VerticeParte2 *v = g->getListaNos(); // Recebe a lista de vértices
	if (v->getID() == idVertice) // O vértice esta na primeira posicao da lista
	{
		if (v->getAresta() != NULL)
		{
			excluirAresta(v); // Função responsável por remover todas as arestas do vértice
			v->setAresta(NULL); // Colocar como null a lista de arestas do vértice
			auxExcluirAresta(g, v->getID()); // Exclui nos outros vértices a aresta que conecta um vértice qualquer ao vértice que será excluído
			VerticeParte2 *aux = v->getProx(); // O vértice auxiliar recebe o vértice seguinte ao atual.
			delete v; // O vértice atual é excluído
			g->setListaNos(aux); // A lista de vértices do grafo tem um novo vértice inicial
			int ordem = g->getOrdem();
			ordem--;
			g->setOrdem(ordem);
			return;	
		}
		else
		{
			v->setAresta(NULL);
			auxExcluirAresta(g, v->getID());
			VerticeParte2 *aux = v->getProx(); // O vértice auxiliar recebe o vértice seguinte ao atual.
			delete v; // O vértice atual é excluído
			g->setListaNos(aux); // A lista de vértices do grafo tem um novo vértice inicial
			int ordem = g->getOrdem();
			ordem--;
			g->setOrdem(ordem);
			return;	
		}
		
	}
	while (v->getProx()->getID() != idVertice) // O vertice esta na segunda até a última posicao da lista
	{ 
		v = v->getProx();
	}
	if (v->getProx()->getProx() != NULL) // O vertice não está na última posição da lista
	{
		VerticeParte2 *aux = v; 
		VerticeParte2 *aux2 = v->getProx()->getProx(); // O auxiliar recebe o nó após o nó que será excluído
		v = v->getProx(); // V recebe o nó a ser removido
		aux->setProx(aux2); // O auxiliar com o nó antecessor ao que será removido coloca o próximo como o sucessor do removido.
		if (v->getAresta() != NULL)
		{
			excluirAresta(v); // As arestas são removidas
		}
		auxExcluirAresta(g, v->getID()); // Exclui as arestas dos outros vértices com o vértice a ser removido
		delete v;
		int ordem = g->getOrdem();
		ordem--;
		g->setOrdem(ordem);
	}
	else  // O vértice esta na última posição
	{
		VerticeParte2 *aux = v;
		v = v->getProx(); // Recebe o nó a ser removido
		aux->setProx(NULL); // O antecessor ao que será removido tem o próximo nó apontado para NULL
		if (v->getAresta() != NULL)
		{
			excluirAresta(v); // Exclui as aresta			
		}
		auxExcluirAresta(g, v->getID()); // Exclui as arestas dos outros vértices com o vértice a ser removido
		delete v;
		int ordem = g->getOrdem();
		ordem--;
		g->setOrdem(ordem);
	}
}

void ControladorGrafoParte2::excluirAresta(VerticeParte2 *v) // Função responsável por excluir todas as arestas de um vértice
{
	Aresta *a = v->getAresta(); // Recebe a lista de arestas do vértice
	if (a != 0) // Verifica se a lista está vazia
	{	
		while (a->getProxAresta() != 0) // Enquanto não for null, avança na lista pegando a próxima aresta e excluindo a atuwl
		 {	
			Aresta *aux = a; 
			a = a->getProxAresta();
			delete aux;
		}
	}
	delete a; 
}

void ControladorGrafoParte2::auxExcluirAresta(GrafoParte2 *g, int id) // Função responsável por excluir todas as arestas dos vértices que se conectam ao vértice que será excluído
{
	VerticeParte2 *v = g->getListaNos(); // Recebe a lista de vértices
	while (v != 0) // Percorre a lista de vértices
	{	
		if (v->getID() != id) // Se o id do vértice for diferente ao id passado por parâmetro,  
		{
			if (v->getAresta()!=0) // Verifica se a lista de arestas do vértice não está vazia
			{
				Aresta *a = v->getAresta(); // Recebe a lista de arestas de cada vértice
				if (a->getId_No() == id) // Se a aresta a ser removida é a primeira.
				{
					Aresta *aux = a->getProxAresta();
					v->setAresta(aux);
					int numArestas = v->getNumArestas();
					numArestas--;
					v->setNumArestas(numArestas);
					delete a;
				}
 	  	    	while (a->getProxAresta() != NULL) // Enquanto a aresta não for NULL, verifica a próxima se é a desejada a ser excluída.
            	{
            		if (a->getProxAresta()->getId_No() == id)
					{
						break; // Quando localiza, dá um break no while e segue a exclusão
					}
            		a = a->getProxAresta();
	  	    	}
				if (a->getProxAresta() != NULL && a->getProxAresta()->getId_No() == id) // A próxima aresta não é nula e a seguinte é a ser removida.
				{
                	Aresta *aux = a;
					Aresta *aux2 = a->getProxAresta()->getProxAresta(); // Recebe a aresta seguinte a ser removida
					a = a->getProxAresta(); // Recebe a aresta a ser removida
					aux->setProxAresta(aux2); // Faz com que o nó antecessor ao que será removido aponte para o sucessor ao ser removido.
			   		int numArestas = v->getNumArestas();
					numArestas--;
					v->setNumArestas(numArestas);
					delete a;
				} 
			}
		}
		v = v->getProx();
	}
}


int ControladorGrafoParte2::colorir() // Função responsável por colorir utilizando o Algoritmo de Johnson - Detalhado no relatório
{
	int contInicial = 0; // Recebe um contador inicial com zero
	GrafoParte2 *auxiliar = copiar(g); // Copia o grafo, dois grafos iguais em endereços de memória diferentes
	while (auxiliar->getListaNos() != NULL) // Colore enquanto houver vértices sem cor.
	{
		GrafoParte2 *auxiliar2 = copiar(auxiliar); // Uma segunda cópia do grafo é utilizada
		while (auxiliar2->getListaNos() != NULL) // Colore de acordo com os subconjuntos independentes do Grafo, enquanto houver.
		{
			VerticeParte2 *verticeAux = auxiliar2->getListaNos(); 
			VerticeParte2 *menor = verticeAux;
			while (verticeAux != NULL) // Descobre o menor vértice sem cor
			{
				if (verticeAux->getNumArestas() < menor->getNumArestas())
				{
					menor = verticeAux;
				}
				verticeAux = verticeAux->getProx();
			}
			int id = menor->getID();
			auxColorir(menor->getID(), contInicial); //Colore o menor
			Aresta *auxAresta = menor->getAresta();
			while (auxAresta != NULL)
			{
				int id2 = auxAresta->getId_No();
				auxAresta = auxAresta->getProxAresta();
				excluirVertice(auxiliar2, id2); // Exclui do segundo grafo auxiliar
			}
			excluirVertice(auxiliar2, id); //Exclui do segundo grafo auxiliar
			excluirVertice(auxiliar, id); //Exclui do primeiro grafo auxiliar
		}
		contInicial++;
	}
	return contInicial;
}


void ControladorGrafoParte2::auxColorir(int id, int cor) //Função responsável por colocar a cor no vértice
{
	VerticeParte2 *v = g->getListaNos();
	while (v != NULL)
	{
		if (id == v->getID())
		{
			v->setCor(cor);
			break;
		}
		v = v->getProx();
	}
}

GrafoParte2* ControladorGrafoParte2::copiar(GrafoParte2 *g) // Função responsável por realizar a cópia de um grafo.
{
	GrafoParte2 *g2 = new GrafoParte2();
	int ordem = g->getOrdem();
	g2->setOrdem(ordem);
	VerticeParte2 *v = g->getListaNos();
	while (v != NULL)
	{
		VerticeParte2 *vAux = new VerticeParte2();
		int id = v->getID();
		int numArestas = v->getNumArestas();
		vAux->setID(id);
		vAux->setNumArestas(numArestas);
		Aresta *a = v->getAresta();
		while (a != NULL)
		{
			Aresta *auxAresta = new Aresta();
			int idAresta = a->getId_No();
			int pesoAresta =  a->getPesoAresta();
			auxAresta->setiD_No(idAresta);
			auxAresta->setPesoAresta(pesoAresta);
			if (vAux->getAresta() == NULL)
			{
				vAux->setAresta(auxAresta);
			}
			else
			{
				Aresta *auxFinal = vAux->getAresta();
				while (auxFinal->getProxAresta() != NULL)
				{
					auxFinal = auxFinal->getProxAresta();
				}
				auxFinal->setProxAresta(auxAresta);
			}
			a = a->getProxAresta();
		}
		if (g2->getListaNos() == NULL)
		{
			g2->setListaNos(vAux);
		}
		else
		{
			VerticeParte2 *vAux2 = g2->getListaNos();
			while (vAux2->getProx() != NULL)
			{
				vAux2 = vAux2->getProx();
			}
			vAux2->setProx(vAux);
		}
		v = v->getProx();
	}
	return g2;
}

void ControladorGrafoParte2::GulosoAtribuicaoCanal()
{
	
}

void ControladorGrafoParte2::GulosoRandomizadoAtribuicaoCanal()
{
	
}

void ControladorGrafoParte2::GulosoRandomizadoReativoAtribuicaoCanal()
{
	
}