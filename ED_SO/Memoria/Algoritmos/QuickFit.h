#pragma once

#include <map>
#include <vector>

#include "../Algoritmo.h"

class QuickFit : public Algoritmo {
public:
	QuickFit();
	void Print() override;
	void OrganizaListas() override;
protected:
	virtual void* InsereProcesso(Processo* p, LISTA lista) override;

	std::vector<int> tamanhos;
private: 
	std::map<int, Lista<EspacoMemoria>*> listasEspaco;
	void OrganizaListasEspacos();
};