#ifndef GRAFOPARTE2_H
#define GRAFOPARTE2_H
#include "VerticeParte2.h"

class GrafoParte2
{
private:
	int ordem;
	VerticeParte2 *listaNos;
protected:
	
public:
	GrafoParte2();
	~GrafoParte2();
	void setOrdem (int ordem);
	int getOrdem ();
	void setListaNos(VerticeParte2 *vertice);
	VerticeParte2 *getListaNos();
};

#endif