#pragma once

#include "../Algoritmo.h"

class WorstFit : public Algoritmo {
public:
	WorstFit();
	void* InsereProcesso(Processo* p, LISTA lista) override;
};