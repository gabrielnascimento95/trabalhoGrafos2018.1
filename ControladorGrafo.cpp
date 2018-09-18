// Preferimos utilizar o Controlador para não colocarmos tudo dentro da classe grafos. Somente uma questão de organização onde o controlador conversa com a classe. Caso fosse utilizada alguma interface gráfica, o uso do controlador também iria auxiliar.
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
	this->tipoGrafo = tipoGrafo; // É informado pelo usuário assim que se inicia o executável
	if (tipoGrafo == 0) //tipoGrafo == 0 se refere a Grafo Direcionado
	{
		int ordemGrafo;
		FILE *file;
		file = fopen(arquivo, "r"); // Abre o arquivo
		if (file == NULL)  // Se houve erro na abertura, emite mensagem
		{
			printf("Algum erro com o endereço do documento");
			return;
		}
		if(!feof(file)) // Caso nao haja erro na abertura
		{
			fscanf(file,"%d \n \n", &ordemGrafo); // Lê a ordem no grafo
			g = new Grafo(ordemGrafo);
		}
		while (!feof(file)) // Leitura do arquivo
		{
			int v1, v2;
			float v3;
			fscanf(file, "%d %d %f", &v1, &v2, &v3); // ID do Vértice, ID da aresta, Peso da Aresta
			if (v2 == -1)
			{
				criarVerticeIndividual(v1); // Utiliza a tag e descobre que o vértice não tem aresta
			}
			else
			{
				criarVertice(v1, v2, v3); // Cria normalmente
			}
		}
		fclose(file);
	}
	else //tipoGrafo == 1, Grafo não direcionado
	{
		int ordemGrafo;
		FILE *file;
		file = fopen(arquivo, "r");
		if (file == NULL)  // Se houve erro na abertura, emite mensagem
		{
			printf("Algum erro com o endereço do documento");
			return;
		}
		if(!feof(file)) // Caso nao haja erro na abertura
		{
			fscanf(file,"%d \n \n", &ordemGrafo); // Lê a ordem do grafo
			g = new Grafo(ordemGrafo);
		}
		while (!feof(file)) // Leitura do arquivo
		{
			int v1, v2; 
			float v3;
			fscanf(file, "%d %d %f", &v1, &v2, &v3); //ID do Vértice, ID da aresta, Peso da Aresta
			if (v2 == -1) 
			{
				criarVerticeIndividual(v1); // Vértice sem arestas
			}
			else
			{
				criarVertice(v1, v2, v3); // Necessário repetir, pois o grafo não é orientado
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

int ControladorGrafo::getTipoGrafo() //Funcao para retornar se um grafo é direcionado ou não direcionado
{
	return tipoGrafo;
}

void ControladorGrafo::criarVerticeIndividual(int id) // Insere o vértice individual na lista
{
	if (id > 0)
	{
		Vertice *v = new Vertice(id); // Um novo vértice é criado.
		insereVerticeLista(v); // Insere o vertice na lista de vertices do grafo
		atualizarOrdemPositivo(); // Atualiza a ordem do grafo
	}
	else
	{
		cout << "Vértice menor que zero" << endl;
	}
}

void ControladorGrafo::criarVertice(int id, int id2, float pesoAresta){ //Funcao utilizada para que um vértice seja criado a partir da leitura do documento informado pelo usuário via linha de comando.
	bool existeVertice = false;
	bool existeAresta = false;
	Vertice *vertice = g->GetListaNos(); // Recebe a lista de vértices do grafo
	if (vertice != 0) // Nesse caso, a Lista de Vértices no Grafo não está vazia
	{
		while (vertice != 0) // Tenta achar na lista de vértices o vértice informado
 	  	{	
			if (vertice->GetID() == id) // Existe na lista o vértice
			{
				existeVertice = true;
				Aresta *a = vertice->GetListaAresta();
				while (a != 0) // Verifica se a ligacao entre os dois vertices já existe
				{
					if (a->getId_No() == id2) // Existe a ligacao
					{
						cout << "Ja existe vertice e aresta com esses valores" << endl;
						cout << "Nao eh possivel o cadastro" << endl;
						cout << "Grafo simples" << endl;
						existeAresta = true;		
						break;
					}
					a = a->getProxAresta(); // Não existe a ligacao
                }
				if (!existeAresta) // Não existe a aresta entre os dois vertices
				{
					insereVerticeAresta(vertice, id2, pesoAresta); // Cria a aresta entre os dois vertices
					break;
				}
				break;
			}
			vertice = vertice->GetProxNo();
		}
			if (!existeVertice) // Não existe na lista o vértice informado
			{
				Vertice *v = new Vertice(id); // Novo vértice é criado
				insereVerticeLista(v); // Insere na Lista de Vértices do Grafo
    			insereVerticeAresta(v, id2, pesoAresta); // Insere no Vértice a sua Lista de Arestas		
			}
		}
	else // Nesse caso, a Lista de Vértices no Grafo está vazia
	{
		Vertice *v = new Vertice(id);
		insereVerticeLista(v); // Insere na Lista de Vértices do Grafo
 		insereVerticeAresta(v, id2, pesoAresta); // Insere no Vértice a sua Lista de Arestas		
	}
}

void ControladorGrafo::criarVerticeExec() //Funcao utilizada para que um vértice seja criado a partir da execucao no terminal
{
	int nVertice;
	cout << "Digite o numero do vertice " << endl;
	cin >> nVertice;
	if (existeVertice(nVertice)) // Nesse caso, o vértice a ser criado já existe.
	{
		cout << "O vertice ja existe, experimente criar uma aresta" << endl;
	}
	else // Nesse caso, o vértice a ser criado nao existe.
	{
		if (nVertice > 0)
		{
			Vertice *v = new Vertice(nVertice); // Um novo vértice é criado.
			insereVerticeLista(v); // Insere o vertice na lista de vertices do grafo
			atualizarOrdemPositivo(); // Atualiza a ordem do grafo
			cout << "Sucesso!" << endl;
		}
		else
		{
			cout << "Número menor que 0!" << endl;
		}
		
	}
}

void ControladorGrafo::criarArestaExec() // Função responsável por criar uma aresta durante a execução
{
	int nVertice; 
	int nVertice2;
	float pAresta;
	imprimeVertice(); // Lista os vértices
	cout << "Escolha um dos vertices listados acima" << endl;
	cin >> nVertice; // Usuário digita o vértice 
	cout << "Escolha agora qual vertice ira conectar" << endl;
	cin >> nVertice2; // Usuário digita o segundo vértice
	cout << "Qual o peso da nova aresta?" << endl;
	cin >> pAresta; // Usuário digita o peso da aresta 
	int verificAresta = existeAresta(nVertice, nVertice2); // Verifica se a aresta existe.
	if (getTipoGrafo() == 0 && existeVertice(nVertice) == 1 && existeVertice(nVertice2) == 1 && nVertice != nVertice2) 
	{ //IF acima verifica o tipoDoGrafo, se os vertices existem e se os vértices não são iguais
		if (verificAresta == 1) // Existe a aresta
		{
			cout << "Ja existe vertice e aresta com esses valores" << endl;
			cout << "Nao eh possivel o cadastro" << endl;
			cout << "Grafo simples" << endl;
		}
		else // Não existe a aresta
		{
			Vertice *v = g->GetListaNos();
			while (v != 0) // Executa enquanto não for null, nesse caso, o grafo é direcionado
			{
				if (v->GetID() == nVertice) // Achou o vértice
				{
					insereVerticeAresta(v, nVertice2, pAresta); // Achou e faz a inserção
			   	   	cout << "Insercao feita com sucesso" << endl;
					break;		
				}
				v = v->GetProxNo();
	 	   }
       }		
	}
	else if (existeVertice(nVertice) == 1 && existeVertice(nVertice2) == 1 && nVertice != nVertice2) 
 	{ // Nesse caso, o grafo é não direcionado. A verificação se os vértices existem são feitas e se os vértices são iguais também
		int verificAresta2 = existeAresta(nVertice2, nVertice); // Nesse caso, verifica, além da aresta do primeiro vértice pro segundo, a aresta do segundo pro primeiro
		if (verificAresta == 1 && verificAresta2 == 1) // Se ambas existirem, erro na inserção.
		{
			cout << "Ja existe vertice e aresta com esses valores nos dois casos" << endl;
			cout << "Nao eh possivel o cadastro" << endl;
			cout << "Grafo simples" << endl;						
		}
		else if (existeAresta(nVertice, nVertice2) == 1 && existeAresta(nVertice2, nVertice) == 0) // Existe somente a aresta do primeiro pro segundo vértice
		{
			int resp = -1;
			cout << "Ja existe vertice e aresta com esses valores no caso do primeiro vertice" << endl;
			cout << "Deseja inserir somente em um vertice?" << endl; // Verifica com o usuário se deseja que a inserção seja feita somente em uma aresta
			cout << "1 - Sim, 0 - Nao" << endl;
			cin >> resp;
			if (resp == 1)
			{
				Vertice *v = g->GetListaNos();
				while (v != 0) // Executa enquanto não for null
				{
					if (v->GetID() == nVertice2) // Localiza o vértice
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
		else if (existeAresta(nVertice, nVertice2) == 0 && existeAresta(nVertice2, nVertice) == 1) // Nesse caso, existe somente a aresta do segundo vértice pro primeiro.
		{
			int resp = -1;
			cout << "Ja existe vertice e aresta com esses valores no caso do segundo vertice" << endl; // Verifica com o usuário se deseja a inserção
			cout << "Deseja inserir somente em um vertice?" << endl;
			cout << "1 - Sim, 0 - Nao" << endl;
			cin >> resp;
			if (resp == 1)
			{
				Vertice *v = g->GetListaNos();
				while (v != 0) // Executa enquanto não for null
				{
					if (v->GetID() == nVertice) // Localiza o vértice
					{	  
						insereVerticeAresta(v, nVertice, pAresta); // Realiza a inserção
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
		else // As arestas são inexistente, logo, são criadas.
		{
			cout << "Arestas inexistentes, podem ser criados" << endl;
			Vertice *v = g->GetListaNos();
			while (v != 0)
			{
				if (v->GetID() == nVertice) // Localiza o primeiro vértice
				{
					insereVerticeAresta(v, nVertice2, pAresta); // Insere no primeiro vértice
				}
				if (v->GetID() == nVertice2) // Localiza o segundo vértice
				{
					insereVerticeAresta(v, nVertice, pAresta);	// Insere no segundo vértice		
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

void ControladorGrafo::insereVerticeLista(Vertice *v)//Funcao utilizada para que seja inserido na lista de vértices do grafo o novo vértice.
{
    Vertice *listaNos = g->GetListaNos(); 
    if (listaNos == NULL) // O Grafo não possui nenhum vértice
    {
        g->SetListaNos(v); // Coloca na lista do grafo o primeiro vértice
	}
    else
    {
        while (listaNos->GetProxNo() != NULL) // É necessário percorrer a lista de vértices do Grafo até achar uma posição vazia e colocar o vértice
        {
     		listaNos = listaNos->GetProxNo(); // Coloca o vértice após a localização do antigo último vértice
        }
        listaNos->SetProxNo(v);
    }
}

void ControladorGrafo::insereVerticeAresta(Vertice *v, int id2, float pesoAresta)//Funcao para inserir no vértice selecionado a sua lista de arestas. 
{
	Aresta *lista = v->GetListaAresta();
    Aresta *a = new Aresta(id2, pesoAresta);
    if (v->GetListaAresta() == NULL) // No vértice selecionado, é preciso percorrer sua lista de arestas. Nesse caso, a lista de arestas está vazia.
    {
        v->SetListaAresta(a); // Insere na primeira posição do vértice a aresta
    }
    else
    {
        while (lista->getProxAresta() != NULL) // Já há na lista de arestas valores, é preciso achar o próximo lugar vazio.
        {
           lista = lista->getProxAresta(); // Insere após o antigo último lugar de aresta a nova última aresta
        }
        lista->setProxAresta(a);
    }
    atualizarNumArestasPositivo();
    atualizarGrauVerticePositivo(v);
}

void ControladorGrafo::excluirVertice() // Função responsável por excluir o vértice informado pelo usuário
{
	int id, certeza;
	imprimeVertice();
	cout << "Escolha o vertice para excluir " << endl;
	cin >> id;
	if (existeVertice(id) == 1) // Verifica se o vértice informado existe, se sim, pergunta se há certeza da exclusão
	{
		cout << "Tem certeza que deseja excluir? " << endl;
		cout << "1 - Sim, 2 - Nao " << endl;
		cin >> certeza;
		if (certeza == 1) // Há certeza
		{
			Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
			if (v->GetID() == id) // O vértice esta na primeira posicao da lista
			{
				excluirAresta(v); // Função responsável por remover todas as arestas do vértice
				v->SetListaAresta(NULL); // Colocar como null a lista de arestas do vértice
				auxExcluirAresta(v->GetID()); // Exclui nos outros vértices a aresta que conecta um vértice qualquer ao vértice que será excluído
				Vertice *aux = v->GetProxNo(); // O vértice auxiliar recebe o vértice seguinte ao atual.
				delete v; // O vértice atual é excluído
				g->SetListaNos(aux); // A lista de vértices do grafo tem um novo vértice inicial
				atualizarOrdemNegativo(); // Diminui a ordem do grafo
				cout << "Vertice excluido com sucesso" << endl;
				return;
			}
			while (v->GetProxNo()->GetID() != id) // O vertice esta na segunda até a última posicao da lista
			{ 
				v = v->GetProxNo();
			}
			if (v->GetProxNo()->GetProxNo() != NULL) // O vertice não está na última posição da lista
			{
				Vertice *aux = v; 
				Vertice *aux2 = v->GetProxNo()->GetProxNo(); // O auxiliar recebe o nó após o nó que será excluído
				v = v->GetProxNo(); // V recebe o nó a ser removido
				aux->SetProxNo(aux2); // O auxiliar com o nó antecessor ao que será removido coloca o próximo como o sucessor do removido.
				excluirAresta(v); // As arestas são removidas
				auxExcluirAresta(v->GetID()); // Exclui as arestas dos outros vértices com o vértice a ser removido
				delete v;
				atualizarOrdemNegativo();
			}
			else  // O vértice esta na última posição
			{
				Vertice *aux = v;
				v = v->GetProxNo(); // Recebe o nó a ser removido
				aux->SetProxNo(NULL); // O antecessor ao que será removido tem o próximo nó apontado para NULL
				excluirAresta(v); // Exclui as aresta
				auxExcluirAresta(v->GetID()); // Exclui as arestas dos outros vértices com o vértice a ser removido
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

void ControladorGrafo::excluirAresta(Vertice *v) // Função responsável por excluir todas as arestas de um vértice
{
	Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas do vértice
	if (a != 0) // Verifica se a lista está vazia
	{	
		while (a->getProxAresta() != 0) // Enquanto não for null, avança na lista pegando a próxima aresta e excluindo a atuwl
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

void ControladorGrafo::auxExcluirAresta(int id) // Função responsável por excluir todas as arestas dos vértices que se conectam ao vértice que será excluído
{
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v != 0) // Percorre a lista de vértices
	{	
		if (v->GetID() != id) // Se o id do vértice for diferente ao id passado por parâmetro,  
		{
			if (v->GetListaAresta()!=0) // Verifica se a lista de arestas do vértice não está vazia
			{
				Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas de cada vértice
				if (a->getId_No() == id) // Se a aresta a ser removida é a primeira.
				{
					Aresta *aux = a->getProxAresta();
					v->SetListaAresta(aux);
					atualizarGrauVerticeNegativo(v);
					atualizarNumArestasNegativo();
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
			   		atualizarGrauVerticeNegativo(v);
					atualizarNumArestasNegativo();
					delete a;
				} 
			}
		}
		v = v->GetProxNo();
	}
}

void ControladorGrafo::excluirAresta2exec() // Função responsável por chamar a função que exclui a aresta entre dois vértices durante a execução 
{
	int idV1, idV2;
	imprimeGrafo();
	cout << "Escolha a aresta entre dois grafos para excluir" << endl;
	cin >> idV1;
	cin >> idV2;
	if (existeVertice(idV1) == 1 && existeVertice(idV2) == 1) // Verifica se os vértices existem
	{
		if (existeAresta(idV1, idV2) == 1) // Verifica se a aresta existe
		{
			excluirAresta2(idV1, idV2); // Exclui a aresta se existir
		    if (getTipoGrafo() == 1) 
			{
				excluirAresta2(idV2, idV1); // Se for não direcionado, exclui a outra aresta também.
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

void ControladorGrafo::excluirAresta2(int idV1, int idV2) // Função que exclui a aresta entre dois vértices
{
	Vertice *v = g->GetListaNos();
	int cont = 0;
	int nDeArestas = auxExcluirAresta2(idV1, idV2); // Retorna o numero de arestas que ligam dois vertices, se for multigrafo.
	while (v != 0) // Percore a lista de vértices
	{
		if (v->GetID() == idV1) // Id do vértice é igual ao id que será removido.
		{
			Aresta *a = v->GetListaAresta(); // Recebe a lista de aresta
			if (a->getId_No()==idV2) // Está na primeira posição da lista e ID da aresta é igual ao id do segundo vértice
			{
				Aresta *aux = a->getProxAresta(); // Recebe a próxima aresta
				v->SetListaAresta(aux); // Pega o vértice e coloca uma nova aresta na cabeça da lista de arestas
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
			if (a->getProxAresta() != NULL && a->getProxAresta()->getId_No() == idV2) // Faz a remoção semelhante a exclusão do vértice
			{
                Aresta *aux = a; // Aux recebe Vértice atual
				Aresta *aux2 = a->getProxAresta()->getProxAresta(); // Pega o sucessor ao vértice que será removido
				a = a->getProxAresta(); // Avança para o que será removido
				aux->setProxAresta(aux2); // Coloca a próxima aresta do antecessor com a do sucessor
				atualizarNumArestasNegativo();
				delete a;
			} 
			else if(a->getProxAresta() == NULL && a->getId_No() == idV2) // Está na última posição da lista
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
	if (nDeArestas > 1) // A princípio consideramos que poderia haver multigrafo, depois de uma conversa com o professor, vimos que não era necessário
	{ // Função faria a exclusão caso fosse multigrafo
		while (cont < nDeArestas)
		{
			excluirAresta2(idV1, idV2);
			cont++;
		}
	}
	atualizarGrauVerticeNegativo(v);
}

int ControladorGrafo::auxExcluirAresta2(int idV1, int idV2) // Retorna o número de arestas entre dois vértices
{ // Caso pudesse ser multigrafo, também seria utilizada
	int cont = 0; 
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v != 0) // Enquanto não for null, vai percorrendo os vértices
	{
		if (v->GetID() == idV1) 
		{
			Aresta *a = v->GetListaAresta();
			while (a != NULL)
			{
				if (a->getId_No() == idV2)
				{
					cont++; // Foi encontrada uma aresta que liga o vértice idV1 e o vértice idV2
				}
				a = a->getProxAresta();
			}
			return cont;
		}
		v = v->GetProxNo();
	}   	
	return cont;
}

void ControladorGrafo::imprimeGrafo() // Função utilizada para que o grafo seja impresso, seus vértices e arestas
{
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	Aresta *a; 
	while (v != NULL) // Percorre a lista de vértices
	{
		cout << "Identificador do Vértice " << v->GetID() << endl;
		a = v->GetListaAresta(); // Recebe a lista de arestas do vértice
        while (a != NULL)
        {
			cout << "Id do Vértice da Aresta " << a->getId_No() << endl;
			a = a->getProxAresta();
		}
		v = v->GetProxNo();
	}
}

void ControladorGrafo::imprimeVertice() // Função utilizada para a impressão somente de vértices
{
	Vertice *v = g->GetListaNos();
   	while (v != NULL)
    {
		cout << "Identificador do Vértice " << v->GetID() << endl;
		v = v->GetProxNo();
	}
}

int ControladorGrafo::existeVertice(int idV) // Função que verifica se determinado vértice existe fazendo comparações com os seus identificadores
{
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v!= NULL)
	{
		if (v->GetID() == idV) // Verifica se o id do vértice é o idV em procura.
		{
			return 1; // Se sim, retorna 1
		}
		v = v->GetProxNo();		
	}
	return 0; // Se não, retorna 0.
}

int ControladorGrafo::existeAresta(int idV1, int idV2) // Função responsável por verificar se uma aresta entre dois vértices existe
{
	bool existeAr = false; 
	Vertice *v = g->GetListaNos();
	while (v != 0) // Percorre os vértices
	{
		if (v->GetID() == idV1) // Verifica se o idV1 é igual ao ID do Vértice.
		{ 
			Aresta *a = v->GetListaAresta();
			while (a != NULL) // Percorre as arestas
			{
				if (a->getId_No() == idV2) // Acha a aresta entre os dois vértices
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
		return 0; // Retorna que não achou
	}
}

void ControladorGrafo::atualizarGrauVerticePositivo(Vertice *v) // Função responsável por atualizar o grau do vértice em mais um
{
	int grau;
	grau = v->GetPesoNo();
    grau++;
    v->SetPesoNo(grau);
}

void ControladorGrafo::atualizarGrauVerticeNegativo(Vertice *v) // Função responsável por atualizar o grau do vértice em menos um
{
	int grau;
	grau = v->GetPesoNo();
	grau--;
	v->SetPesoNo(grau);
}

void ControladorGrafo::atualizarNumArestasPositivo() // Função responsável por atualizar o número de arestas em mais um
{
	int nArestas = g->GetNumArestas();
	nArestas++;
	g->SetNumArestas(nArestas);
}

void ControladorGrafo::atualizarNumArestasNegativo() // Função responsável por atualizar o número de arestas em menos um
{
	int nArestas = g->GetNumArestas();
	nArestas--;
	g->SetNumArestas(nArestas);
}

void ControladorGrafo::atualizarOrdemPositivo() // Função responsável por atualizar a ordem do grafo em mais um
{
	int i = g->GetOrdem();
	i++;
	g->SetOrdem(i);
}

void ControladorGrafo::atualizarOrdemNegativo() // Função responsável por atualizar a ordem do grafo em menos um
{
	int i = g->GetOrdem();
	i--;
	g->SetOrdem(i);
}

void ControladorGrafo::auxGrauDadoVertice() // Função responsável por realizar a impressão do grau de um vértice
{
	int id;
	imprimeVertice();
	cout << "Digite o vertice desejado" << endl;
	cin >> id; 
	if (existeVertice(id) == 1) // Verifica se existe o vértice
	{
		if (getTipoGrafo() == 0) // Verifica o tipo de grafo, direcionado ou não direcionado.
		{
			cout << "O grau de entrada eh " << grauEntradaVertice(id) << endl; // Chama função para imprimir o grau de entrada de um vértice em grafo direcionado
			cout << "O grau de saida eh " << grauSaidaVertice(id) << endl; // Chama função para imprimir o grau de saída de um vértice em grafo direcionado.
		}
		else
		{
			cout << "O grau do vertice eh " << grauSaidaVertice(id) << endl; // Chama função para imprimir o grau de um vértice em um grafo não direcionado. Nesse caso, o grau de entrada vai ser sempre igual ao grau de saída 		
		}
	}
	else
	{
		cout << "O vertice nao existe" << endl;
	}
}

int ControladorGrafo::grauSaidaVertice(int id) // Responsável por relatar o grau de saída de um vértice
{
	int cont = 0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v != 0) // Percore a lista de vértices
	{
		if (v->GetID() == id) // Acha o vértice
		{
			cont = v->GetPesoNo(); // Pega o peso do vértice (Número de vértices com o qual se comunica)
			return cont; // Retorna o peso
		}
		v = v->GetProxNo();
	}
	return cont; // Retorna o peso
}

int ControladorGrafo::grauEntradaVertice(int id) // Responsável por relatar o grau de entrada de um vértice
{
	int cont = 0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v != 0) // Percorre a lista de vértices
	{
		if (v->GetID() != id) // Percorre todos os vértices, exceto ele mesmo.
		{
			Aresta *a = v->GetListaAresta();
			while (a != 0) // Verifica a lista de arestas de todos vértices, exceto ele mesmo.
			{
				if (a->getId_No() == id) // Se achar o identificador do vértice em questão na lista de arestas, adiciona um na conta do grau de entrada de determinado vértice
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

void ControladorGrafo::verificTrivial() // Verifica se o grafo é trivial
{
	if (g->GetOrdem() != 1) // Se a Ordem for igual a 1, significa que o grafo é trivial
	{
		cout << "O grafo nao eh trivial " << endl;
	}
	else
	{
		cout << "O grafo nao eh trivial " << endl;
	}
}

void ControladorGrafo::verificNulo() // Retorna se é grafo nulo
{
	if (g->GetOrdem() > 0) // Se ordem maior que 0, o grafo não é nulo
	{
		cout << "O grafo nao eh nulo " << endl;	
	}
	else // Se ordem igual a zero, o grafo é nulo
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
	Vertice *v = g->GetListaNos(); // Recebe a lista de nós
	if (v->GetPesoNo() != id) // Verifica o peso do primeiro nó (Número de vértices que possui)
	{
		EhKRegular = false; // Se for diferente do que o usuário informou, programa já para aqui.
	}
	if (v->GetProxNo() != 0) // Percorre o resto dos vértices
	{
	   	v = v->GetProxNo();
		while (v != 0)
		{
			if (v->GetPesoNo() != id)
			{
				EhKRegular = false; // Chegou aqui, descobre que não é regular. Se passar sem entrar, é K-Regular
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

void ControladorGrafo::auxVizinhanca() // Função onde o usuário irá decidir se deseja uma vizinhança aberta ou fechada
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
		if (existeVertice(idVertice) == 1) // Verifica a existêcia do vértice informado pelo usuário
			vizinhanca(tipoVizinhanca, idVertice); // Chama função de impressão
		else
			cout << "Vertice informado nao existe" << endl;
	}
	else
	{
		cout << "O valor inserido nao eh valido" << endl;
	}
}

void ControladorGrafo::vizinhanca(int tipoVizinhanca, int idVertice) // Imprime a vizinhança
{
	if (tipoVizinhanca == 0) // Verifica o tipo de vizinhança. Nesse caso, fechada
	{
		cout << "A vizinhanca fechada eh: Vertice " << idVertice; // Imprime o vértice
		Vertice *v = g->GetListaNos();
		while (v != 0) // Percorre até achar o vértice desejado e imprime as suas arestas.
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
		cout << "A vizinhanca aberta eh: "; // Vizinhança aberta.
		Vertice *v = g->GetListaNos();
		while (v != 0) // Percorre até achar o vértice desejado e imprime as suas arestas.
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

void ControladorGrafo::auxVerificMultigrafo() // Verifica se é multigrafo
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

int ControladorGrafo::verificMultigrafo() // Função que percorre o grafo para determinar
{
	int cont = 0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v != 0) // Percorre a lista de vértices
	{
		cont = 0;
		Aresta *a = v->GetListaAresta();
		while (a != 0) // Percorre a lista de arestas do vértice em questão
		{
			if (v->GetID()==a->getId_No()) // Se na sua lista de arestas houver duas arestas com o mesmo outro nó, o contador terá valor maior que 1
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
	return 1; // Se não, retorna 1.
}

void ControladorGrafo::verificGrafoCompleto() // Função responsável por verificar se o grafo é completo
{
	if (verificMultigrafo() == 1) // Verifica inicialmente se é multigrafo, se for, não é possível a verificação
	{
		int numOrdem = g->GetOrdem(); // Verifica a ordem do grafo.
		--numOrdem; // Decrementa a ordem do grafo, pois o grafo completo nesse caso, deverá ter vértices que possuam ordem-1 arestas. Devido ao fato que não pode ser multigrafo.
		bool ehCompleto = true;
		Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
		while (v != 0) // Percorre a lista de vértices
		{
			int cont = 0;
			Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas
			while (a != 0)
			{
				cont++; // Conta o número de arestas
				a = a->getProxAresta(); 
			}
			if (cont != numOrdem) // O número de arestas é diferentes da ordem-1?
			{
				ehCompleto = false; // É diferente, logo, o grafo não é completo
			}
			v = v->GetProxNo(); // Caso o contrário, continue percorrendo até verificar para todos os vértices
        }	
        if (ehCompleto) // Passou por todos e todos tiveram o mesmo grau, logo, é completo.
		{
			cout << "Grafo completo" << endl;
		}
		else
		{
			cout << "Grafo nao eh completo" << endl;
		}
	}
}

int ControladorGrafo::auxSequenciaGrauVertices(int idVertice) // Responsável por auxiliar na impressão da sequencia de graus do vértice
{
	int contador=0;
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v != 0) // Percorre a lista de vértices
	{
		Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas
		while (a != 0) // Percorre a lista de arestas
		{
			if (a->getId_No() == idVertice) // Localiza o vértice desejado
			{
				contador++; // Vai somando até percorrê-lo totalmente.
			}
			a = a->getProxAresta();
		}
		v = v->GetProxNo();
	}
	return contador; // Retorna o grau do vértice
}

void ControladorGrafo::sequenciaGrauVertices() // Responsável por gerenciar a impressão da sequência de graus do vértice
{
	if(tipoGrafo == 0) // Grafo é direcionado
	{
		int vetSaida[g->GetOrdem()]; // Responsável pelo grau de saída
		int vetEntrada[g->GetOrdem()]; // Responsável pelo grau de entrada
		Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
		int cont=0;
		while (v != 0) // Percorre a lista de vértices
		{
			vetSaida[cont] = grauSaidaVertice(v->GetID()); // Descobre o grau de saída do vértice utilizando a mesma função de grau dado vértice
			cont++;
			v = v->GetProxNo();
		}
		cont = 0;
		v = g->GetListaNos();
		while (v != 0)
		{
			vetEntrada[cont] = grauEntradaVertice(v->GetID());	// Descobre o grau de entrada do vértice utilizando a mesma função de grau dado vértice
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
	else // Grafo não é direcionado
	{
		int maior = g->GetOrdem()-1; // Necessário para o Quicksort
		int menor = 0; // Necessário para o QuickSort
		int vet[g->GetOrdem()]; // Vetor criado recebendo a ordem do grafo
		Vertice *v = g->GetListaNos(); // Recebe a lista de arestas
		int cont=0;
		while (v != 0)
		{
			vet[cont] = grauSaidaVertice(v->GetID()); // Retorna o grau de cada um dos vértices na interação, utilizando o descobre o grau de saída do vértice utilizando a mesma função utilizada anteriormente
			cont++;
			v = v->GetProxNo();
		}
		QuickSort(vet, menor, maior); // Função auxiliar para ordenar o vetor com Quicksort
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
// Resolvemos utilizar o quicksort pois é um método muito eficiente, além disso, é bastante rápido. Possui no pior caso complexidade pior caso 	O (n2). No caso médio, possui a complexidade de O(nlog n). E no melhor caso complexidade de O(nlog n) 
void ControladorGrafo::QuickSort(int vet[], int inic, int final) // Recebe o vetor, o menor valor e o maior valor
{
	if (inic < final) // Verifica se o inicial é menor que o final. Caso seja, utiliza a partição do vetor
	{
		int q = particao(vet, inic, final); // Particiona para descobrir o valor da metade do vetor
		QuickSort(vet, inic, q-1); // Chama recursivamente a metade inferior do vetor
		QuickSort(vet, q+1, final); // Chama recursivamente a metade superior do vetor
	}
}

int ControladorGrafo::particao(int vet[], int inic, int final) // Responsável pela partição do vetor
{
	int x = vet[final]; // Recebe a última posição
	int j = inic - 1; // J recebe o início - 1 
	for (int i = inic; i < final; i++) //
	{
		if (x < vet[i]) // O último valor é menor que o primeiro valor?
		{ // Se sim
			j = j + 1; // J é incrementado 
			int temp = vet[j]; // Temporário recebe o vetor na posição j
			vet[j] = vet[i]; // O vetor na posição J recebe o vetor na posição I.
			vet[i] = temp; // O vetor na posição I recebe o temporário
		}
	}	
	vet[final] = vet[j+1]; // O vetor na sua posição final recebe o vértice na posição J + 1
	vet[j+1] = x; // O vetor na sua posição j + 1 recebe x
	return j+1; // O valor de J é retornado
}

void ControladorGrafo::gravarGrafo(char arquivo[100]) // Função responsável por gravar o grafo em um segundo documento informado pela linha de comando
{
	FILE * file;
	file = fopen(arquivo, "wt");
	fprintf(file,"%d \n \n", g->GetOrdem()); // Recebe a ordem do grafo
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	if (file == NULL) 
	{
   	   printf("Problemas na CRIACAO do arquivo\n");
   	   exit(0);
	}
	while(v != 0) // Percorre a lista de vértices
	{
		if (v->GetProxNo() == 0) // Última posição da lista, necessário para tratar o \n e o documento não ter uma linha a mais
		{
			if (v->GetListaAresta() != 0)
			{
				Aresta *a = v->GetListaAresta();
				while (a->getProxAresta() != 0)
				{
					fprintf(file, "%d %d %.0f\n", v->GetID(), a->getId_No(), a->getPesoAresta()); // Escreve o ID do vértice, o ID do vértice da Aresta e o Peso da Aresta
					a = a->getProxAresta();
				}
				fprintf(file, "%d %d %.0f", v->GetID(), a->getId_No(), a->getPesoAresta());
			}
			else
			{
				fprintf(file, "%d -1 -1", v->GetID()); // Escreve o ID do vértice, o ID do vértice da Aresta e o Peso da Aresta
			} // -1 -1 usado como tag para leitura do arquivo, sabendo que o -1 representa um vértice sozinho
		}
		else // Outras posições da lista
		{	
			if (v->GetListaAresta() != 0)
			{	
				Aresta *a = v->GetListaAresta();
				while (a != 0)
				{
					fprintf(file, "%d %d %.0f\n", v->GetID(), a->getId_No(), a->getPesoAresta()); // Escreve o ID do vértice, o ID do vértice da Aresta e o Peso da Aresta
					a = a->getProxAresta();
				}
			}
			else
			{
				fprintf(file, "%d -1 -1\n", v->GetID()); // Escreve o ID do vértice, o ID do vértice da Aresta e o Peso da Aresta
			}
		}
        v = v->GetProxNo();
	}
	fclose(file);
}

void ControladorGrafo::ehBipartido() // Função responsável por averiguar se um grafo é bipartido. Utiliza busca em profundidade
{ // Coloca a cor em cada vértice como -1.
	bool retorno = true;
	Vertice *v = g->GetListaNos(); // Recebe a lista de vértices
	while (v!=0) // Percorre colorindo
	{
		v->setCor(-1);
		v = v->GetProxNo();
	}
	v = g->GetListaNos();
	while (v != 0) // Percore os vértices novamente, agora usando a função auxiliar.
	{
		if (v->getCor()==-1)
		{
			retorno = auxEhBipartido(v, -1); // Utiliza a função auxiliar que determina se é ou não bipartido
			if (!retorno) // Se em algum momento já houver problemas com a coloração, a função já para. 
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

bool ControladorGrafo::auxEhBipartido(Vertice *v, int cor) // A ideia é colorir o primeiro vértice com uma cor, seus vizinhos com outra cor. Durante a busca, se o vizinho de um nó tiver a mesma cor que ele (0 ou 1), logo, não pode ser bipartido.
{
	bool retorno = true;
	if(cor==-1) // Se a cor do vértice anterior era -1, pinta de 0. É usado somente no caso do primeiro vértice ou quando há mais de uma componente conexa.
	{
		v->setCor(0);
	}
	if(cor==1) // Se a cor do vértice anterior era 1, pinta de 0.
	{
		v->setCor(0);
	}
	if(cor==0) // Se a cor do vértice anterior era 0, pinta de 1.
	{
		v->setCor(1);
	}
	Aresta *a = v->GetListaAresta(); // Recebe a lista de arestas.
	while(a != 0) // Enquanto não for null
	{
		Vertice *aux = g->GetListaNos(); // Auxiliar recebe a lista de vértices do grafo
		while (aux != 0) // Enquanto não for null
		{
			if (a->getId_No() == aux->GetID()) // Encontrou a aresta com identificador igual ao identificador do vértice
			{
				if (aux->getCor() == v->getCor()) // Verifica se a cor é igual. Nesse caso, o vértice e o seu vizinho (aux) possuem a mesma cor, não podendo ser bipartido.
				{
					return false; // Não é bipartido.
				}
				if (aux->getCor() == 1 || aux->getCor() == 0) // Caso já possuam cor, avança pro próximo vértice para ser comparado com o próximo id de aresta do grafo.
				{
					break;
				}
				if (aux->getCor() == -1) // Se a cor do vizinho for -1, eu passo a cor do vértice atual e o auxiliar em recursão.
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
