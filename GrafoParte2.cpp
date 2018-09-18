#include "GrafoParte2.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

GrafoParte2::GrafoParte2()
{
	this->ordem = 0;
	this->listaNos = NULL;
}

GrafoParte2::~GrafoParte2()
{
	
}

void GrafoParte2::setOrdem(int ordem)
{
	this->ordem = ordem;
}

int GrafoParte2::getOrdem()
{
	return this->ordem;
}

void GrafoParte2::setListaNos(VerticeParte2 *vertice)
{
	this->listaNos = vertice;
}

VerticeParte2* GrafoParte2::getListaNos()
{
	return this->listaNos;
}