#pragma once

#include <map>
#include <vector>

#include "../Algoritmo.h"

class QuickFit : public Algoritmo {
public:
	QuickFit();
	void OrganizaListas() override;
protected:
	virtual void* InsereProcesso(Processo* p, LISTA lista, bool somenteProcura) override;

	std::vector<int> tamanhos;
private: 
	std::map<int, Lista<EspacoMemoria>*> listasEspaco;
	void OrganizaListasEspacos();
};