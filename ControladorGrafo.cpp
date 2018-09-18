// Preferimos utilizar o Controlador para n�o colocarmos tudo dentro da classe grafos. Somente uma quest�o de organiza��o onde o controlador conversa com a classe. Caso fosse utilizada alguma interface gr�fica, o uso do controlador tamb�m iria auxiliar.
#include "ControladorGrafo.h"
#include "Grafo.h"
#include <string.h>
#include <stdlib.h>
#include "Vertice.h"
#include <iostream>
#include <stdio.h>

using namespace std;

ControladorGrafo::ControladorGrafo(int tipoGrafo, char arquivo[50]) // Responsavel pela leitura do grafo
{
	this->tipoGrafo = tipoGrafo; // � informado pelo usu�rio assim que se inicia o execut�vel
	if (tipoGrafo == 0) //tipoGrafo == 0 se refere a Grafo Direcionado
	{
		int ordemGrafo;
		FILE *file;
		file = fopen(arquivo, "r"); // Abre o arquivo
		if (file == NULL)  // Se houve erro na abertura, emite mensagem
		{
			printf("Algum erro com o endere�o do documento");
			return;
		}
		if(!feof(file)) // Caso nao haja erro na abertura
		{
			fscanf(file,"%d \n \n", &ordemGrafo); // L� a ordem no grafo
			g = new Grafo(ordemGrafo);
		}
		while (!feof(file)) // Leitura do arquivo
		{
			int v1, v2;
			float v3;
			fscanf(file, "%d %d %f", &v1, &v2, &v3); // ID do V�rtice, ID da aresta, Peso da Aresta
			if (v2 == -1)
			{
				criarVerticeIndividual(v1); // Utiliza a tag e descobre que o v�rtice n�o tem aresta
			}
			else
			{
				criarVertice(v1, v2, v3); // Cria normalmente
			}
		}
		fclose(file);
	}
	else //tipoGrafo == 1, Grafo n�o direcionado
	{
		int ordemGrafo;
		FILE *file;
		file = fopen(arquivo, "r");
		if (file == NULL)  // Se houve erro na abertura, emite mensagem
		{
			printf("Algum erro com o endere�o do documento");
			return;
		}
		if(!feof(file)) // Caso nao haja erro na abertura
		{
			fscanf(file,"%d \n \n", &ordemGrafo); // L� a ordem do grafo
			g = new Grafo(ordemGrafo);
		}
		while (!feof(file)) // Leitura do arquivo
		{
			int v1, v2; 
			float v3;
			fscanf(file, "%d %d %f", &v1, &v2, &v3); //ID do V�rtice, ID da aresta, Peso da Aresta
			if (v2 == -1) 
			{
				criarVerticeIndividual(v1); // V�rtice sem arestas
			}
			else
			{
				criarVertice(v1, v2, v3); // Necess�rio repetir, pois o grafo n�o � orientado
				criarVertice(v2, v1, v3);
			}
		}
		fclose(file); // Fecha o arquivo de leitura
	}
}

ControladorGrafo::~ControladorGrafo() //Destruturor
{
	delete g; 
}

int ControladorGrafo::getTipoGrafo() //Funcao para retornar se um grafo � direcionado ou n�o direcionado
{
	return tipoGrafo;
}

void ControladorGrafo::criarVerticeIndividual(int id) // Insere o v�rtice individual na lista
{
	if (id > 0)
	{
		Vertice *v = new Vertice(id); // Um novo v�rtice � criado.
		insereVerticeLista(v); // Insere o vertice na lista de vertices do grafo
		atualizarOrdemPositivo(); // Atualiza a ordem do grafo
	}
	else
	{
		cout << "V�rtice menor que zero" << endl;
	}
}

void ControladorGrafo::criarVertice(int id, int id2, float pesoAresta){ //Funcao utilizada para que um v�rtice seja criado a partir da leitura do documento informado pelo usu�rio via linha de comando.
	bool existeVertice = false;
	bool existeAresta = false;
	Vertice *vertice = g->GetListaNos(); // Recebe a lista de v�rtices do grafo
	if (vertice != 0) // Nesse caso, a Lista de V�rtices no Grafo n�o est� vazia
	{
		while (vertice != 0) // Tenta achar na lista de v�rtices o v�rtice informado
 	  	{	
			if (vertice->GetID() == id) // Existe na lista o v�rtice
			{
				existeVertice = true;
				Aresta *a = vertice->GetListaAresta();
				while (a != 0) // Verifica se a ligacao entre os dois vertices j� existe
				{
					if (a->getId_No() == id2) // Existe a ligacao
					{
						cout << "Ja existe vertice e aresta com esses valores" << endl;
						cout << "Nao eh possivel o cadastro" << endl;
						cout << "Grafo simples" << endl;
						existeAresta = true;		
						break;
					}
					a = a->getProxAresta(); // N�o existe a ligacao
                }
				if (!existeAresta) // N�o existe a aresta entre os dois vertices
				{
					insereVerticeAresta(vertice, id2, pesoAresta); // Cria a aresta entre os dois vertices
					break;
				}
				break;
			}
			vertice = vertice->GetProxNo();
		}
			if (!existeVertice) // N�o existe na lista o v�rtice informado
			{
				Vertice *v = new Vertice(id); // Novo v�rtice � criado
				insereVerticeLista(v); // Insere na Lista de V�rtices do Grafo
    			insereVerticeAresta(v, id2, pesoAresta); // Insere no V�rtice a sua Lista de Arestas		
			}
		}
	else // Nesse caso, a Lista de V�rtices no Grafo est� vazia
	{
		Vertice *v = new Vertice(id);
		insereVerticeLista(v); // Insere na Lista de V�rtices do Grafo
 		insereVerticeAresta(v, id2, pesoAresta); // Insere no V�rtice a sua Lista de Arestas		
	}
}

void ControladorGrafo::criarVerticeExec() //Funcao utilizada para que um v�rtice seja criado a partir da execucao no terminal
{
	int nVertice;
	cout << "Digite o numero do vertice " << endl;
	cin >> nVertice;
	if (existeVertice(nVertice)) // Nesse caso, o v�rtice a ser criado j� existe.
	{
		cout << "O vertice ja existe, experimente criar uma aresta" << endl;
	}
	else // Nesse caso, o v�rtice a ser criado nao existe.
	{
		if (nVertice > 0)
		{
			Vertice *v = new Vertice(nVertice); // Um novo v�rtice � criado.
			insereVerticeLista(v); // Insere o vertice na lista de vertices do grafo
			atualizarOrdemPositivo(); // Atualiza a ordem do grafo
			cout << "Sucesso!" << endl;
		}
		else
		{
			cout << "N�mero menor que 0!" << endl;
		}
		
	}
}

void ControladorGrafo::criarArestaExec() // Fun��o respons�vel por criar uma aresta durante a execu��o
{
	int nVertice; 
	int nVertice2;
	float pAresta;
	imprimeVertice(); // Lista os v�rtices
	cout << "Escolha um dos vertices listados acima" << endl;
	cin >> nVertice; // Usu�rio digita o v�rtice 
	cout << "Escolha agora qual vertice ira conectar" << endl;
	cin >> nVertice2; // Usu�rio digita o segundo v�rtice
	cout << "Qual o peso da nova aresta?" << endl;
	cin >> pAresta; // Usu�rio digita o peso da aresta 
	int verificAresta = existeAresta(nVertice, nVertice2); // Verifica se a aresta existe.
	if (getTipoGrafo() == 0 && existeVertice(nVertice) == 1 && existeVertice(nVertice2) == 1 && nVertice != nVertice2) 
	{ //IF acima verifica o tipoDoGrafo, se os vertices existem e se os v�rtices n�o s�o iguais
		if (verificAresta == 1) // Existe a aresta
		{
			cout << "Ja existe vertice e aresta com esses valores" << endl;
			cout << "Nao eh possivel o cadastro" << endl;
			cout << "Grafo simples" << endl;
		}
		else // N�o existe a aresta
		{
			Vertice *v = g->GetListaNos();
			while (v != 0) // Executa enquanto n�o for null, nesse caso, o grafo � direcionado
			{
				if (v->GetID() == nVertice) // Achou o v�rtice
				{
					insereVerticeAresta(v, nVertice2, pAresta); // Achou e faz a inser��o
			   	   	cout << "Insercao feita com sucesso" << endl;
					break;		
				}
				v = v->GetProxNo();
	 	   }
       }		
	}
	else if (existeVertice(nVertice) == 1 && existeVertice(nVertice2) == 1 && nVertice != nVertice2) 
 	{ // Nesse caso, o grafo � n�o direcionado. A verifica��o se os v�rtices existem s�o feitas e se os v�rtices s�o iguais tamb�m
		int verificAresta2 = existeAresta(nVertice2, nVertice); // Nesse caso, verifica, al�m da aresta do primeiro v�rtice pro segundo, a aresta do segundo pro primeiro
		if (verificAresta == 1 && verificAresta2 == 1) // Se ambas existirem, erro na inser��o.
		{
			cout << "Ja existe vertice e aresta com esses valores nos dois casos" << endl;
			cout << "Nao eh possivel o cadastro" << endl;
			cout << "Grafo simples" << endl;						
		}
		else if (existeAresta(nVertice, nVertice2) == 1 && existeAresta(nVertice2, nVertice) == 0) // Existe somente a aresta do primeiro pro segundo v�rtice
		{
			int resp = -1;
			cout << "Ja existe vertice e aresta com esses valores no caso do primeiro vertice" << endl;
			cout << "Deseja inserir somente em um vertice?" << endl; // Verifica com o usu�rio se deseja que a inser��o seja feita somente em uma aresta
			cout << "1 - Sim, 0 - Nao" << endl;
			cin >> resp;
			if (resp == 1)
			{
				Vertice *v = g->GetListaNos();
				while (v != 0) // Executa enquanto n�o for null
				{
					if (v->GetID() == nVertice2) // Localiza o v�rtice
					{	  
						insereVerticeAresta(v, nVertice, pAresta); // Insere a aresta
						cout << "Insercao feita com sucesso" << endl;	
						break;	
					}
					v = v->GetProxNo();
				}
			}
			else if (resp == 0)
			{
				cout << "Nao sera inserido" << endl;
			}
			else
			{
				cout << "Erro - insercao nao realizada" << endl;
			}
		}
		else if (existeAresta(nVertice, nVertice2) == 0 && existeAresta(nVertice2, nVertice) == 1) // Nesse caso, existe somente a aresta do segundo v�rtice pro primeiro.
		{
			int resp = -1;
			cout << "Ja existe vertice e aresta com esses valores no caso do segundo vertice" << endl; // Verifica com o usu�rio se deseja a inser��o
			cout << "Deseja inserir somente em um vertice?" << endl;
			cout << "1 - Sim, 0 - Nao" << endl;
			cin >> resp;
			if (resp == 1)
			{
				Vertice *v = g->GetListaNos();
				while (v != 0) // Executa enquanto n�o for null
				{
					if (v->GetID() == nVertice) // Localiza o v�rtice
					{	  
						insereVerticeAresta(v, nVertice, pAresta); // Realiza a inser��o
						cout << "Insercao feita com sucesso" << endl;		
						break;
					}
					v = v->GetProxNo();
				}
			}
			else if (resp == 0)
			{
				cout << "Nao sera inserido" << endl;
			}
			else
			{
				cout << "Erro - insercao nao realizada" << endl;
			}
		}
		else // As arestas s�o inexistente, logo, s�o criadas.
		{
			cout << "Arestas inexistentes, podem ser criados" << endl;
			Vertice *v = g->GetListaNos();
			while (v != 0)
			{
				if (v->GetID() == nVertice) // Localiza o primeiro v�rtice
				{
					insereVerticeAresta(v, nVertice2, pAresta); // Insere no primeiro v�rtice
				}
				if (v->GetID() == nVertice2) // Localiza o segundo v�rtice
				{
					insereVerticeAresta(v, nVertice, pAresta);	// Insere no segundo v�rtice		
				}
				v = v->GetProxNo();
			}
			cout << "Insercao feita com sucesso" << endl;
		}
	}
	else
	{
		cout << "O vertice selecionado nao existe, o vertice para conexao nao existe ou os vertices tem o mesmo valor" << endl;
	}
	
}

void ControladorGrafo::insereVerticeLista(Vertice *v)//Funcao utilizada para que seja inserido na lista de v�rtices do grafo o novo v�rtice.
{
    Vertice *listaNos = g->GetListaNos(); 
    if (listaNos == NULL) // O Grafo n�o possui nenhum v�rtice
    {
        g->SetListaNos(v); // Coloca na lista do grafo o primeiro v�rtice
	}
    else
    {
        while (listaNos->GetProxNo() != NULL) // � necess�rio percorrer a lista de v�rtices do Grafo at� achar uma posi��o vazia e colocar o v�rtice
        {
     		listaNos = listaNos->GetProxNo(); // Coloca o v�rtice ap�s a localiza��o do antigo �ltimo v�rtice
        }
        listaNos->SetProxNo(v);
    }
}

void ControladorGrafo::insereVerticeAresta(Vertice *v, int id2, float pesoAresta)//Funcao para inserir no v�rtice selecionado a sua lista de arestas. 
{
	Aresta *lista = v->GetListaAresta();
    Aresta *a = new Aresta(id2, pesoAresta);
    if (v->GetListaAresta() == NULL) // No v�rtice selecionado, � preciso percorrer sua lista de arestas. Nesse caso, a lista de arestas est� vazia.
    {
        v->SetListaAresta(a); // Insere na primeira posi��o do v�rtice a aresta
    }
    else
    {
        while (lista->getProxAresta() != NULL) // J� h� na lista de arestas valores, � preciso achar o pr�ximo lugar vazio.
        {
           lista = lista->getProxAresta(); // Insere ap�s o antigo �ltimo lugar de aresta a nova �ltima aresta
        }
        lista->setProxAresta(a);
    }
    atualizarNumArestasPositivo();
    atualizarGrauVerticePositivo(v);
}

void ControladorGrafo::excluirVertice() // Fun��o respons�vel por excluir o v�rtice informado pelo usu�rio
{
	int id, certeza;
	imprimeVertice();
	cout << "Escolha o vertice para excluir " << endl;
	cin >> id;
	if (existeVertice(id) == 1) // Verifica se o v�rtice informado existe, se sim, pergunta se h� certeza da exclus�o
	{
		cout << "Tem certeza que deseja excluir? " << endl;
		cout << "1 - Sim, 2 - Nao " << endl;
		cin >> certeza;
		if (certeza == 1) // H� certeza
		{
			Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
			if (v->GetID() == id) // O v�rtice esta na primeira posicao da lista
			{
				excluirAresta(v); // Fun��o respons�vel por remover todas as arestas do v�rtice
				v->SetListaAresta(NULL); // Colocar como null a lista de arestas do v�rtice
				auxExcluirAresta(v->GetID()); // Exclui nos outros v�rtices a aresta que conecta um v�rtice qualquer ao v�rtice que ser� exclu�do
				Vertice *aux = v->GetProxNo(); // O v�rtice auxiliar recebe o v�rtice seguinte ao atual.
				delete v; // O v�rtice atual � exclu�do
				g->SetListaNos(aux); // A lista de v�rtices do grafo tem um novo v�rtice inicial
				atualizarOrdemNegativo(); // Diminui a ordem do grafo
				cout << "Vertice excluido com sucesso" << endl;
				return;
			}
			while (v->GetProxNo()->GetID() != id) // O vertice esta na segunda at� a �ltima posicao da lista
			{ 
				v = v->GetProxNo();
			}
			if (v->GetProxNo()->GetProxNo() != NULL) // O vertice n�o est� na �ltima posi��o da lista
			{
				Vertice *aux = v; 
				Vertice *aux2 = v->GetProxNo()->GetProxNo(); // O auxiliar recebe o n� ap�s o n� que ser� exclu�do
				v = v->GetProxNo(); // V recebe o n� a ser removido
				aux->SetProxNo(aux2); // O auxiliar com o n� antecessor ao que ser� removido coloca o pr�ximo como o sucessor do removido.
				excluirAresta(v); // As arestas s�o removidas
				auxExcluirAresta(v->GetID()); // Exclui as arestas dos outros v�rtices com o v�rtice a ser removido
				delete v;
				atualizarOrdemNegativo();
			}
			else  // O v�rtice esta na �ltima posi��o
			{
				Vertice *aux = v;
				v = v->GetProxNo(); // Recebe o n� a ser removido
				aux->SetProxNo(NULL); // O antecessor ao que ser� removido tem o pr�ximo n� apontado para NULL
				excluirAresta(v); // Exclui as aresta
				auxExcluirAresta(v->GetID()); // Exclui as arestas dos outros v�rtices com o v�rtice a ser removido
				delete v;
				atualizarOrdemNegativo();
			}
		}
		else if (certeza == 2)
		{	
			cout << "Voce desistiu de excluir o vertice " << endl;
		}		
		else
		{
			cout << "Erro - Nao sera excluido" << endl;
		}
	}
	else
	{
		cout << "Nao existe o vertice informado para excluir" << endl;
	}		
}

void ControladorGrafo::excluirAresta(Vertice *v) // Fun��o respons�vel por excluir todas as arestas de um v�rtice
{
	Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas do v�rtice
	if (a != 0) // Verifica se a lista est� vazia
	{	
		while (a->getProxAresta() != 0) // Enquanto n�o for null, avan�a na lista pegando a pr�xima aresta e excluindo a atuwl
		 {	
			Aresta *aux = a; 
			a = a->getProxAresta();
			delete aux;
			atualizarNumArestasNegativo();
		}
	}
	delete a;
	atualizarNumArestasNegativo(); 
}

void ControladorGrafo::auxExcluirAresta(int id) // Fun��o respons�vel por excluir todas as arestas dos v�rtices que se conectam ao v�rtice que ser� exclu�do
{
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v != 0) // Percorre a lista de v�rtices
	{	
		if (v->GetID() != id) // Se o id do v�rtice for diferente ao id passado por par�metro,  
		{
			if (v->GetListaAresta()!=0) // Verifica se a lista de arestas do v�rtice n�o est� vazia
			{
				Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas de cada v�rtice
				if (a->getId_No() == id) // Se a aresta a ser removida � a primeira.
				{
					Aresta *aux = a->getProxAresta();
					v->SetListaAresta(aux);
					atualizarGrauVerticeNegativo(v);
					atualizarNumArestasNegativo();
					delete a;
				}
 	  	    	while (a->getProxAresta() != NULL) // Enquanto a aresta n�o for NULL, verifica a pr�xima se � a desejada a ser exclu�da.
            	{
            		if (a->getProxAresta()->getId_No() == id)
					{
						break; // Quando localiza, d� um break no while e segue a exclus�o
					}
            		a = a->getProxAresta();
	  	    	}
				if (a->getProxAresta() != NULL && a->getProxAresta()->getId_No() == id) // A pr�xima aresta n�o � nula e a seguinte � a ser removida.
				{
                	Aresta *aux = a;
					Aresta *aux2 = a->getProxAresta()->getProxAresta(); // Recebe a aresta seguinte a ser removida
					a = a->getProxAresta(); // Recebe a aresta a ser removida
					aux->setProxAresta(aux2); // Faz com que o n� antecessor ao que ser� removido aponte para o sucessor ao ser removido.
			   		atualizarGrauVerticeNegativo(v);
					atualizarNumArestasNegativo();
					delete a;
				} 
			}
		}
		v = v->GetProxNo();
	}
}

void ControladorGrafo::excluirAresta2exec() // Fun��o respons�vel por chamar a fun��o que exclui a aresta entre dois v�rtices durante a execu��o 
{
	int idV1, idV2;
	imprimeGrafo();
	cout << "Escolha a aresta entre dois grafos para excluir" << endl;
	cin >> idV1;
	cin >> idV2;
	if (existeVertice(idV1) == 1 && existeVertice(idV2) == 1) // Verifica se os v�rtices existem
	{
		if (existeAresta(idV1, idV2) == 1) // Verifica se a aresta existe
		{
			excluirAresta2(idV1, idV2); // Exclui a aresta se existir
		    if (getTipoGrafo() == 1) 
			{
				excluirAresta2(idV2, idV1); // Se for n�o direcionado, exclui a outra aresta tamb�m.
			} 
		}
		else
		{
			cout << "A aresta informada nao existe" << endl;
		}
	}
	else
	{
		cout << "Um ou dois dos vertices informados nao existe" << endl;
	} 
}

void ControladorGrafo::excluirAresta2(int idV1, int idV2) // Fun��o que exclui a aresta entre dois v�rtices
{
	Vertice *v = g->GetListaNos();
	int cont = 0;
	int nDeArestas = auxExcluirAresta2(idV1, idV2); // Retorna o numero de arestas que ligam dois vertices, se for multigrafo.
	while (v != 0) // Percore a lista de v�rtices
	{
		if (v->GetID() == idV1) // Id do v�rtice � igual ao id que ser� removido.
		{
			Aresta *a = v->GetListaAresta(); // Recebe a lista de aresta
			if (a->getId_No()==idV2) // Est� na primeira posi��o da lista e ID da aresta � igual ao id do segundo v�rtice
			{
				Aresta *aux = a->getProxAresta(); // Recebe a pr�xima aresta
				v->SetListaAresta(aux); // Pega o v�rtice e coloca uma nova aresta na cabe�a da lista de arestas
				atualizarNumArestasNegativo();
				delete a;
			}
			while (a->getProxAresta() != NULL) // Tenta achar a aresta 
			{
				if (a->getProxAresta()->getId_No()==idV2)
				{
					break; // Achou
				}
				a = a->getProxAresta();
			}
			if (a->getProxAresta() != NULL && a->getProxAresta()->getId_No() == idV2) // Faz a remo��o semelhante a exclus�o do v�rtice
			{
                Aresta *aux = a; // Aux recebe V�rtice atual
				Aresta *aux2 = a->getProxAresta()->getProxAresta(); // Pega o sucessor ao v�rtice que ser� removido
				a = a->getProxAresta(); // Avan�a para o que ser� removido
				aux->setProxAresta(aux2); // Coloca a pr�xima aresta do antecessor com a do sucessor
				atualizarNumArestasNegativo();
				delete a;
			} 
			else if(a->getProxAresta() == NULL && a->getId_No() == idV2) // Est� na �ltima posi��o da lista
			{
				Aresta *aux = a;
				aux->setProxAresta(NULL);
				atualizarNumArestasNegativo();
				delete a;
			}
			break;
		}
		v = v->GetProxNo();
	}
	if (nDeArestas > 1) // A princ�pio consideramos que poderia haver multigrafo, depois de uma conversa com o professor, vimos que n�o era necess�rio
	{ // Fun��o faria a exclus�o caso fosse multigrafo
		while (cont < nDeArestas)
		{
			excluirAresta2(idV1, idV2);
			cont++;
		}
	}
	atualizarGrauVerticeNegativo(v);
}

int ControladorGrafo::auxExcluirAresta2(int idV1, int idV2) // Retorna o n�mero de arestas entre dois v�rtices
{ // Caso pudesse ser multigrafo, tamb�m seria utilizada
	int cont = 0; 
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v != 0) // Enquanto n�o for null, vai percorrendo os v�rtices
	{
		if (v->GetID() == idV1) 
		{
			Aresta *a = v->GetListaAresta();
			while (a != NULL)
			{
				if (a->getId_No() == idV2)
				{
					cont++; // Foi encontrada uma aresta que liga o v�rtice idV1 e o v�rtice idV2
				}
				a = a->getProxAresta();
			}
			return cont;
		}
		v = v->GetProxNo();
	}   	
	return cont;
}

void ControladorGrafo::imprimeGrafo() // Fun��o utilizada para que o grafo seja impresso, seus v�rtices e arestas
{
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	Aresta *a; 
	while (v != NULL) // Percorre a lista de v�rtices
	{
		cout << "Identificador do V�rtice " << v->GetID() << endl;
		a = v->GetListaAresta(); // Recebe a lista de arestas do v�rtice
        while (a != NULL)
        {
			cout << "Id do V�rtice da Aresta " << a->getId_No() << endl;
			a = a->getProxAresta();
		}
		v = v->GetProxNo();
	}
}

void ControladorGrafo::imprimeVertice() // Fun��o utilizada para a impress�o somente de v�rtices
{
	Vertice *v = g->GetListaNos();
   	while (v != NULL)
    {
		cout << "Identificador do V�rtice " << v->GetID() << endl;
		v = v->GetProxNo();
	}
}

int ControladorGrafo::existeVertice(int idV) // Fun��o que verifica se determinado v�rtice existe fazendo compara��es com os seus identificadores
{
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v!= NULL)
	{
		if (v->GetID() == idV) // Verifica se o id do v�rtice � o idV em procura.
		{
			return 1; // Se sim, retorna 1
		}
		v = v->GetProxNo();		
	}
	return 0; // Se n�o, retorna 0.
}

int ControladorGrafo::existeAresta(int idV1, int idV2) // Fun��o respons�vel por verificar se uma aresta entre dois v�rtices existe
{
	bool existeAr = false; 
	Vertice *v = g->GetListaNos();
	while (v != 0) // Percorre os v�rtices
	{
		if (v->GetID() == idV1) // Verifica se o idV1 � igual ao ID do V�rtice.
		{ 
			Aresta *a = v->GetListaAresta();
			while (a != NULL) // Percorre as arestas
			{
				if (a->getId_No() == idV2) // Acha a aresta entre os dois v�rtices
				{
				   	existeAr = true;
					break;
				}
					a = a->getProxAresta();
			}
		}
		v = v->GetProxNo();
	}
    if (existeAr)
	{
		return 1; // Retorna que achou
	}
	else
	{
		return 0; // Retorna que n�o achou
	}
}

void ControladorGrafo::atualizarGrauVerticePositivo(Vertice *v) // Fun��o respons�vel por atualizar o grau do v�rtice em mais um
{
	int grau;
	grau = v->GetPesoNo();
    grau++;
    v->SetPesoNo(grau);
}

void ControladorGrafo::atualizarGrauVerticeNegativo(Vertice *v) // Fun��o respons�vel por atualizar o grau do v�rtice em menos um
{
	int grau;
	grau = v->GetPesoNo();
	grau--;
	v->SetPesoNo(grau);
}

void ControladorGrafo::atualizarNumArestasPositivo() // Fun��o respons�vel por atualizar o n�mero de arestas em mais um
{
	int nArestas = g->GetNumArestas();
	nArestas++;
	g->SetNumArestas(nArestas);
}

void ControladorGrafo::atualizarNumArestasNegativo() // Fun��o respons�vel por atualizar o n�mero de arestas em menos um
{
	int nArestas = g->GetNumArestas();
	nArestas--;
	g->SetNumArestas(nArestas);
}

void ControladorGrafo::atualizarOrdemPositivo() // Fun��o respons�vel por atualizar a ordem do grafo em mais um
{
	int i = g->GetOrdem();
	i++;
	g->SetOrdem(i);
}

void ControladorGrafo::atualizarOrdemNegativo() // Fun��o respons�vel por atualizar a ordem do grafo em menos um
{
	int i = g->GetOrdem();
	i--;
	g->SetOrdem(i);
}

void ControladorGrafo::auxGrauDadoVertice() // Fun��o respons�vel por realizar a impress�o do grau de um v�rtice
{
	int id;
	imprimeVertice();
	cout << "Digite o vertice desejado" << endl;
	cin >> id; 
	if (existeVertice(id) == 1) // Verifica se existe o v�rtice
	{
		if (getTipoGrafo() == 0) // Verifica o tipo de grafo, direcionado ou n�o direcionado.
		{
			cout << "O grau de entrada eh " << grauEntradaVertice(id) << endl; // Chama fun��o para imprimir o grau de entrada de um v�rtice em grafo direcionado
			cout << "O grau de saida eh " << grauSaidaVertice(id) << endl; // Chama fun��o para imprimir o grau de sa�da de um v�rtice em grafo direcionado.
		}
		else
		{
			cout << "O grau do vertice eh " << grauSaidaVertice(id) << endl; // Chama fun��o para imprimir o grau de um v�rtice em um grafo n�o direcionado. Nesse caso, o grau de entrada vai ser sempre igual ao grau de sa�da 		
		}
	}
	else
	{
		cout << "O vertice nao existe" << endl;
	}
}

int ControladorGrafo::grauSaidaVertice(int id) // Respons�vel por relatar o grau de sa�da de um v�rtice
{
	int cont = 0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v != 0) // Percore a lista de v�rtices
	{
		if (v->GetID() == id) // Acha o v�rtice
		{
			cont = v->GetPesoNo(); // Pega o peso do v�rtice (N�mero de v�rtices com o qual se comunica)
			return cont; // Retorna o peso
		}
		v = v->GetProxNo();
	}
	return cont; // Retorna o peso
}

int ControladorGrafo::grauEntradaVertice(int id) // Respons�vel por relatar o grau de entrada de um v�rtice
{
	int cont = 0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v != 0) // Percorre a lista de v�rtices
	{
		if (v->GetID() != id) // Percorre todos os v�rtices, exceto ele mesmo.
		{
			Aresta *a = v->GetListaAresta();
			while (a != 0) // Verifica a lista de arestas de todos v�rtices, exceto ele mesmo.
			{
				if (a->getId_No() == id) // Se achar o identificador do v�rtice em quest�o na lista de arestas, adiciona um na conta do grau de entrada de determinado v�rtice
				{
					cont++;
				}
				a = a->getProxAresta();
			}
		}
		v = v->GetProxNo();
	}
	return cont;
}

void ControladorGrafo::ordemDoGrafo() // Retorna a ordem do grafo.
{
	cout << "A ordem do grafo eh " << g->GetOrdem();
}

void ControladorGrafo::verificTrivial() // Verifica se o grafo � trivial
{
	if (g->GetOrdem() != 1) // Se a Ordem for igual a 1, significa que o grafo � trivial
	{
		cout << "O grafo nao eh trivial " << endl;
	}
	else
	{
		cout << "O grafo nao eh trivial " << endl;
	}
}

void ControladorGrafo::verificNulo() // Retorna se � grafo nulo
{
	if (g->GetOrdem() > 0) // Se ordem maior que 0, o grafo n�o � nulo
	{
		cout << "O grafo nao eh nulo " << endl;	
	}
	else // Se ordem igual a zero, o grafo � nulo
	{
		cout << "O grafo eh nulo " << endl;
	}
}

void ControladorGrafo::verificKRegularidade() // VEerifica a K-Regularidade de um grafo
{
	bool EhKRegular = true;
	int id;
	cout << "Digite o valor de K para verificar a K-Regularidade" << endl;
	cin >> id;
	Vertice *v = g->GetListaNos(); // Recebe a lista de n�s
	if (v->GetPesoNo() != id) // Verifica o peso do primeiro n� (N�mero de v�rtices que possui)
	{
		EhKRegular = false; // Se for diferente do que o usu�rio informou, programa j� para aqui.
	}
	if (v->GetProxNo() != 0) // Percorre o resto dos v�rtices
	{
	   	v = v->GetProxNo();
		while (v != 0)
		{
			if (v->GetPesoNo() != id)
			{
				EhKRegular = false; // Chegou aqui, descobre que n�o � regular. Se passar sem entrar, � K-Regular
				break;
			}
			v = v->GetProxNo(); 
		}
	}
	if (EhKRegular)
	{
		cout << "O grafo eh K-Regular " << endl;		
	}
	else
	{
		cout << "O grafo nao eh K-Regular " << endl;
	}
}

void ControladorGrafo::auxVizinhanca() // Fun��o onde o usu�rio ir� decidir se deseja uma vizinhan�a aberta ou fechada
{
	int tipoVizinhanca;
	int idVertice;
	cout << "Digite 1 para vizinhanca aberta e 0 para vizinhanca fechada" << endl;
	cin >> tipoVizinhanca;
	imprimeGrafo();
	cout << "Digite o vertice desejado" << endl;
	cin >> idVertice;
	if (tipoVizinhanca == 0 || tipoVizinhanca == 1)
	{
		if (existeVertice(idVertice) == 1) // Verifica a exist�cia do v�rtice informado pelo usu�rio
			vizinhanca(tipoVizinhanca, idVertice); // Chama fun��o de impress�o
		else
			cout << "Vertice informado nao existe" << endl;
	}
	else
	{
		cout << "O valor inserido nao eh valido" << endl;
	}
}

void ControladorGrafo::vizinhanca(int tipoVizinhanca, int idVertice) // Imprime a vizinhan�a
{
	if (tipoVizinhanca == 0) // Verifica o tipo de vizinhan�a. Nesse caso, fechada
	{
		cout << "A vizinhanca fechada eh: Vertice " << idVertice; // Imprime o v�rtice
		Vertice *v = g->GetListaNos();
		while (v != 0) // Percorre at� achar o v�rtice desejado e imprime as suas arestas.
		{
			if (v->GetID() == idVertice)
			{
				Aresta *a = v->GetListaAresta();
				while (a != 0)
				{
					cout << ", Vertice " << a->getId_No();
					a = a->getProxAresta();
				}
				cout << endl;
				break;
			}
			v = v->GetProxNo();
		}
	}
	else
	{		
		cout << "A vizinhanca aberta eh: "; // Vizinhan�a aberta.
		Vertice *v = g->GetListaNos();
		while (v != 0) // Percorre at� achar o v�rtice desejado e imprime as suas arestas.
		{
			if (v->GetID() == idVertice)
			{
				Aresta *a = v->GetListaAresta();
				while (a != 0)
				{
					cout << "Vertice " << a->getId_No() << endl;;
					a = a->getProxAresta();
				}
				break;
			}
			v = v->GetProxNo();
		}
		
	}
}

void ControladorGrafo::auxVerificMultigrafo() // Verifica se � multigrafo
{
	if (verificMultigrafo()==1)
	{
		cout << "Eh multigrafo" << endl;
	}
	else
	{
		cout << "Nao eh multigrafo" << endl;
	}
}

int ControladorGrafo::verificMultigrafo() // Fun��o que percorre o grafo para determinar
{
	int cont = 0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v != 0) // Percorre a lista de v�rtices
	{
		cont = 0;
		Aresta *a = v->GetListaAresta();
		while (a != 0) // Percorre a lista de arestas do v�rtice em quest�o
		{
			if (v->GetID()==a->getId_No()) // Se na sua lista de arestas houver duas arestas com o mesmo outro n�, o contador ter� valor maior que 1
			{
				cont++;
			}
			a = a->getProxAresta();
		} 
		if (cont > 1)
		{
			return 0; // Caso seja multigrafo, retorna 0
		}
		v = v->GetProxNo();
	}
	return 1; // Se n�o, retorna 1.
}

void ControladorGrafo::verificGrafoCompleto() // Fun��o respons�vel por verificar se o grafo � completo
{
	if (verificMultigrafo() == 1) // Verifica inicialmente se � multigrafo, se for, n�o � poss�vel a verifica��o
	{
		int numOrdem = g->GetOrdem(); // Verifica a ordem do grafo.
		--numOrdem; // Decrementa a ordem do grafo, pois o grafo completo nesse caso, dever� ter v�rtices que possuam ordem-1 arestas. Devido ao fato que n�o pode ser multigrafo.
		bool ehCompleto = true;
		Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
		while (v != 0) // Percorre a lista de v�rtices
		{
			int cont = 0;
			Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas
			while (a != 0)
			{
				cont++; // Conta o n�mero de arestas
				a = a->getProxAresta(); 
			}
			if (cont != numOrdem) // O n�mero de arestas � diferentes da ordem-1?
			{
				ehCompleto = false; // � diferente, logo, o grafo n�o � completo
			}
			v = v->GetProxNo(); // Caso o contr�rio, continue percorrendo at� verificar para todos os v�rtices
        }	
        if (ehCompleto) // Passou por todos e todos tiveram o mesmo grau, logo, � completo.
		{
			cout << "Grafo completo" << endl;
		}
		else
		{
			cout << "Grafo nao eh completo" << endl;
		}
	}
}

int ControladorGrafo::auxSequenciaGrauVertices(int idVertice) // Respons�vel por auxiliar na impress�o da sequencia de graus do v�rtice
{
	int contador=0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v != 0) // Percorre a lista de v�rtices
	{
		Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas
		while (a != 0) // Percorre a lista de arestas
		{
			if (a->getId_No() == idVertice) // Localiza o v�rtice desejado
			{
				contador++; // Vai somando at� percorr�-lo totalmente.
			}
			a = a->getProxAresta();
		}
		v = v->GetProxNo();
	}
	return contador; // Retorna o grau do v�rtice
}

void ControladorGrafo::sequenciaGrauVertices() // Respons�vel por gerenciar a impress�o da sequ�ncia de graus do v�rtice
{
	if(tipoGrafo == 0) // Grafo � direcionado
	{
		int vetSaida[g->GetOrdem()]; // Respons�vel pelo grau de sa�da
		int vetEntrada[g->GetOrdem()]; // Respons�vel pelo grau de entrada
		Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
		int cont=0;
		while (v != 0) // Percorre a lista de v�rtices
		{
			vetSaida[cont] = grauSaidaVertice(v->GetID()); // Descobre o grau de sa�da do v�rtice utilizando a mesma fun��o de grau dado v�rtice
			cont++;
			v = v->GetProxNo();
		}
		cont = 0;
		v = g->GetListaNos();
		while (v != 0)
		{
			vetEntrada[cont] = grauEntradaVertice(v->GetID());	// Descobre o grau de entrada do v�rtice utilizando a mesma fun��o de grau dado v�rtice
			v = v->GetProxNo();
			cont++;
		}
		cout << "Vertice   ||   Entrada   ||   Saida " << endl;	
		v = g->GetListaNos();
		for (int i = 0; i < g->GetOrdem(); i++)
		{
			cout << "    ";
			cout << v->GetID();
			cout << "     ";
			cout << "     ";
			cout << vetEntrada[i];
			cout << "     ";
			cout << "     ";
			cout << "     ";
			cout << vetSaida[i];
			cout << endl;	
			v = v->GetProxNo();
		}
	}
	else // Grafo n�o � direcionado
	{
		int maior = g->GetOrdem()-1; // Necess�rio para o Quicksort
		int menor = 0; // Necess�rio para o QuickSort
		int vet[g->GetOrdem()]; // Vetor criado recebendo a ordem do grafo
		Vertice *v = g->GetListaNos(); // Recebe a lista de arestas
		int cont=0;
		while (v != 0)
		{
			vet[cont] = grauSaidaVertice(v->GetID()); // Retorna o grau de cada um dos v�rtices na intera��o, utilizando o descobre o grau de sa�da do v�rtice utilizando a mesma fun��o utilizada anteriormente
			cont++;
			v = v->GetProxNo();
		}
		QuickSort(vet, menor, maior); // Fun��o auxiliar para ordenar o vetor com Quicksort
		cout << "A sequencia de graus eh" << endl;	
		cout << "< ";
		for (cont = 0; cont < g->GetOrdem(); cont++)
		{
			cout << vet[cont] << ", "; // Imprime a sequencia de graus
		}
		cout << " >";
		cout << endl;
	}
}
// Resolvemos utilizar o quicksort pois � um m�todo muito eficiente, al�m disso, � bastante r�pido. Possui no pior caso complexidade pior caso 	O (n2). No caso m�dio, possui a complexidade de O(nlog n). E no melhor caso complexidade de O(nlog n) 
void ControladorGrafo::QuickSort(int vet[], int inic, int final) // Recebe o vetor, o menor valor e o maior valor
{
	if (inic < final) // Verifica se o inicial � menor que o final. Caso seja, utiliza a parti��o do vetor
	{
		int q = particao(vet, inic, final); // Particiona para descobrir o valor da metade do vetor
		QuickSort(vet, inic, q-1); // Chama recursivamente a metade inferior do vetor
		QuickSort(vet, q+1, final); // Chama recursivamente a metade superior do vetor
	}
}

int ControladorGrafo::particao(int vet[], int inic, int final) // Respons�vel pela parti��o do vetor
{
	int x = vet[final]; // Recebe a �ltima posi��o
	int j = inic - 1; // J recebe o in�cio - 1 
	for (int i = inic; i < final; i++) //
	{
		if (x < vet[i]) // O �ltimo valor � menor que o primeiro valor?
		{ // Se sim
			j = j + 1; // J � incrementado 
			int temp = vet[j]; // Tempor�rio recebe o vetor na posi��o j
			vet[j] = vet[i]; // O vetor na posi��o J recebe o vetor na posi��o I.
			vet[i] = temp; // O vetor na posi��o I recebe o tempor�rio
		}
	}	
	vet[final] = vet[j+1]; // O vetor na sua posi��o final recebe o v�rtice na posi��o J + 1
	vet[j+1] = x; // O vetor na sua posi��o j + 1 recebe x
	return j+1; // O valor de J � retornado
}

void ControladorGrafo::gravarGrafo(char arquivo[100]) // Fun��o respons�vel por gravar o grafo em um segundo documento informado pela linha de comando
{
	FILE * file;
	file = fopen(arquivo, "wt");
	fprintf(file,"%d \n \n", g->GetOrdem()); // Recebe a ordem do grafo
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	if (file == NULL) 
	{
   	   printf("Problemas na CRIACAO do arquivo\n");
   	   exit(0);
	}
	while(v != 0) // Percorre a lista de v�rtices
	{
		if (v->GetProxNo() == 0) // �ltima posi��o da lista, necess�rio para tratar o \n e o documento n�o ter uma linha a mais
		{
			if (v->GetListaAresta() != 0)
			{
				Aresta *a = v->GetListaAresta();
				while (a->getProxAresta() != 0)
				{
					fprintf(file, "%d %d %.0f\n", v->GetID(), a->getId_No(), a->getPesoAresta()); // Escreve o ID do v�rtice, o ID do v�rtice da Aresta e o Peso da Aresta
					a = a->getProxAresta();
				}
				fprintf(file, "%d %d %.0f", v->GetID(), a->getId_No(), a->getPesoAresta());
			}
			else
			{
				fprintf(file, "%d -1 -1", v->GetID()); // Escreve o ID do v�rtice, o ID do v�rtice da Aresta e o Peso da Aresta
			} // -1 -1 usado como tag para leitura do arquivo, sabendo que o -1 representa um v�rtice sozinho
		}
		else // Outras posi��es da lista
		{	
			if (v->GetListaAresta() != 0)
			{	
				Aresta *a = v->GetListaAresta();
				while (a != 0)
				{
					fprintf(file, "%d %d %.0f\n", v->GetID(), a->getId_No(), a->getPesoAresta()); // Escreve o ID do v�rtice, o ID do v�rtice da Aresta e o Peso da Aresta
					a = a->getProxAresta();
				}
			}
			else
			{
				fprintf(file, "%d -1 -1\n", v->GetID()); // Escreve o ID do v�rtice, o ID do v�rtice da Aresta e o Peso da Aresta
			}
		}
        v = v->GetProxNo();
	}
	fclose(file);
}

void ControladorGrafo::ehBipartido() // Fun��o respons�vel por averiguar se um grafo � bipartido. Utiliza busca em profundidade
{ // Coloca a cor em cada v�rtice como -1.
	bool retorno = true;
	Vertice *v = g->GetListaNos(); // Recebe a lista de v�rtices
	while (v!=0) // Percorre colorindo
	{
		v->setCor(-1);
		v = v->GetProxNo();
	}
	v = g->GetListaNos();
	while (v != 0) // Percore os v�rtices novamente, agora usando a fun��o auxiliar.
	{
		if (v->getCor()==-1)
		{
			retorno = auxEhBipartido(v, -1); // Utiliza a fun��o auxiliar que determina se � ou n�o bipartido
			if (!retorno) // Se em algum momento j� houver problemas com a colora��o, a fun��o j� para. 
				break; 
		}
		v = v->GetProxNo();
	}
	if (retorno)
	{
		cout << "Eh bipartido" << endl;
	}
	else
	{
		cout << "Nao eh bipartido" << endl;
	}
}

bool ControladorGrafo::auxEhBipartido(Vertice *v, int cor) // A ideia � colorir o primeiro v�rtice com uma cor, seus vizinhos com outra cor. Durante a busca, se o vizinho de um n� tiver a mesma cor que ele (0 ou 1), logo, n�o pode ser bipartido.
{
	bool retorno = true;
	if(cor==-1) // Se a cor do v�rtice anterior era -1, pinta de 0. � usado somente no caso do primeiro v�rtice ou quando h� mais de uma componente conexa.
	{
		v->setCor(0);
	}
	if(cor==1) // Se a cor do v�rtice anterior era 1, pinta de 0.
	{
		v->setCor(0);
	}
	if(cor==0) // Se a cor do v�rtice anterior era 0, pinta de 1.
	{
		v->setCor(1);
	}
	Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas.
	while(a != 0) // Enquanto n�o for null
	{
		Vertice *aux = g->GetListaNos(); // Auxiliar recebe a lista de v�rtices do grafo
		while (aux != 0) // Enquanto n�o for null
		{
			if (a->getId_No() == aux->GetID()) // Encontrou a aresta com identificador igual ao identificador do v�rtice
			{
				if (aux->getCor() == v->getCor()) // Verifica se a cor � igual. Nesse caso, o v�rtice e o seu vizinho (aux) possuem a mesma cor, n�o podendo ser bipartido.
				{
					return false; // N�o � bipartido.
				}
				if (aux->getCor() == 1 || aux->getCor() == 0) // Caso j� possuam cor, avan�a pro pr�ximo v�rtice para ser comparado com o pr�ximo id de aresta do grafo.
				{
					break;
				}
				if (aux->getCor() == -1) // Se a cor do vizinho for -1, eu passo a cor do v�rtice atual e o auxiliar em recurs�o.
				{
					retorno = auxEhBipartido(aux, v->getCor()); 
                }	
			}
			aux = aux->GetProxNo();
		}
		a = a->getProxAresta();
	}
	if (retorno)
	{
		return true;
	}
	else
	{
		return false;
	}
}
