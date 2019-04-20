#pragma once

#include "../Algoritmo.h"

class FirstFit : public Algoritmo {
public:
	FirstFit();
	void Print() override;
protected:
	virtual void* InsereProcesso(Processo* p, LISTA lista) override;
};