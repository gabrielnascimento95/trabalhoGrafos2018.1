#include "ControladorGrafo.h"
#include "ControladorGrafoParte2.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int flag = -2;
	int flag2 = -2;
	int tipoTrabalho = -1;
	int tipoGrafo = -1;
	while (flag != -1)
	{
		cout << "Para parte 1 do trabalho: Digite 0 " << endl;
		cout << "Para parte 2 do trabalho: Digite 1 " << endl;
		cin >> tipoTrabalho;
		if (tipoTrabalho == 0)
		{
			flag = -1;
			while (flag2 != -1)
			{
				cout << "Para a construcao de um grafo direcionado: Digite 0 " << endl;
				cout << "Para a construcao de um grafo nao direcionado: Digite 1 "<< endl;
				cin >> tipoGrafo;
				if (tipoGrafo == 0 || tipoGrafo == 1)
				{
			    	flag2 = -1;	
					ControladorGrafo *c = new ControladorGrafo(tipoGrafo, argv[1]);
    				int i = -1;
    				while (i != 0)
    				{
            			cout << "1 - Inclusao de vertice " << endl;
            			cout << "2 - Inclusao de aresta " << endl;
            			cout << "3 - Exclusao de vertice " << endl;
            			cout << "4 - Exclusao de aresta " << endl;
            			cout << "5 - Grau de dado vertice " << endl;
            			cout << "6 - Verificar K-Regularidade do Grafo " << endl;
            			cout << "7 - Ordem do Grafo " << endl;
            			cout << "8 - Informar se eh Grafo Trivial " << endl;
            			cout << "9 - Informar se eh Grafo Nulo " << endl;
            			cout << "10 - Vizinhanca de determinado vertice " << endl;
            			cout << "11 - Verificar se eh multigrafo " << endl;
            			cout << "12 - Verificar se eh grafo completo " << endl;
            			cout << "13 - Verificar se eh grafo bipartido " << endl;
            			cout << "14 - Sequencia de graus de vertices do grafo " << endl;
            			cout << "15 - Imprimir grafo " << endl;
            			cout << "16 - Salvar em documento " << endl;
            			cout << "0 - Sair" << endl;
            			cin >> i;
            			switch (i)
            			{
            				case 0:
							{
								i = 0;
								break;
  	  	  	                }	
                			case 1:
                    		{
								c->criarVerticeExec();
								cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
								break;
                    		}
                			case 2:
                    		{
                    			c->criarArestaExec();
                  				cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i; 
                        		break;
                    		}
                			case 3:
                    		{
                    			c->excluirVertice();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i; 
                        		break;
                    		}
                			case 4:
                    		{
                    			c->excluirAresta2exec();
								cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 5:
                    		{
                    			c->auxGrauDadoVertice();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i; 
                        		break;
                    		}
                			case 6:
                    		{
                    			c->verificKRegularidade();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 7:
                    		{
                    			c->ordemDoGrafo();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i; 
								break;
                    		}
                			case 8:
                    		{
                    			c->verificTrivial();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i; 
                        		break;
                    		}
                			case 9:
							{
								c->verificNulo();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 10:
   	  	  	  	  	  	    {	
                    			c->auxVizinhanca();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 11:
		 		 		    {		
                    		   	c->auxVerificMultigrafo();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 12:
   	  	                    {	
                    			c->verificGrafoCompleto();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 13:
                    		{
                    			c->ehBipartido();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 14:
                    		{
                    			c->sequenciaGrauVertices();
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break;
                    		}
                			case 15:
                    		{
                    			c->imprimeGrafo(); 
                    			cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break; 
                    		}
               	   	   	   case 16:
			   	   	   	   {
					  			c->gravarGrafo(argv[2]);  
             					cout << "Deseja continuar?" << endl;
								cout << "-1  e para sim, 0 para nao" << endl;
								cin >> i;
                        		break; 
			   	   	   	   }
                          default:
                    	  {
                        	cout << "O numero informado nao eh valido " << endl;
                    		cout << "Deseja continuar?" << endl;
							cout << "-1  e para sim, 0 para nao" << endl;
							cin >> i;
							break;
                    	  } 
   			           }
    				}    	
				}
				else
				{
					cout << "Voce digitou um valor nao valido!" << endl;
				}
			}
		}
		else if (tipoTrabalho == 1)
		{
			ControladorGrafoParte2 *cgp2 = new ControladorGrafoParte2(argv[1]);
			flag = -1;
		}
		else
		{
			cout << "Entrada inválida!" << endl;	
		}
	}

    return 0;
}
