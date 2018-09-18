#include "VerticeParte2.h"
#include "Aresta.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

VerticeParte2::VerticeParte2(int id, int x, int y)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->numArestas = 0;
	this->prox = NULL;
	this->listaAresta = NULL;
	this->visitado = false;
	this->cor = -1;
}

VerticeParte2::~VerticeParte2()
{
	
}

VerticeParte2::VerticeParte2()
{
	this->prox = NULL;
	this->listaAresta = NULL;
	this->visitado = false;
	this->cor = -1;
}

void VerticeParte2::setID(int id)
{
	this->id = id;
}

int VerticeParte2::getID()
{
	return this->id;
}

void VerticeParte2::setX(int x)
{
	this->x = x;
}

int VerticeParte2::getX()
{
	return this->x;
}

void VerticeParte2::setY(int y)
{
	this->y = y;
}

int VerticeParte2::getY()
{
	return this->y;
}

void VerticeParte2::setVisitado(bool visitado)
{
	this->visitado = visitado;
}

bool VerticeParte2::getVisitado()
{
	return this->visitado;
}

void VerticeParte2::setCor(int cor)
{
	this->cor = cor;
}

int VerticeParte2::getCor()
{
	return this->cor;
}

void VerticeParte2::setNumArestas(int n)
{
	this->numArestas = n;
}

int VerticeParte2::getNumArestas()
{
	return this->numArestas;
}

void VerticeParte2::setProx(VerticeParte2 *v)
{
	this->prox = v;
}

VerticeParte2 *VerticeParte2::getProx()
{
	return this->prox;
}

void VerticeParte2::setAresta(Aresta *a)
{
	this->listaAresta = a;
}

Aresta *VerticeParte2::getAresta()
{
	return this->listaAresta;
}
