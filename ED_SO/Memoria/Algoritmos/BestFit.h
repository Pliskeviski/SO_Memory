#pragma once

#include "../Algoritmo.h"

class BestFit : public Algoritmo {
public:
	BestFit();
	void Print() override;
protected:
	void* InsereProcesso(Processo* p, LISTA lista) override;
private:
};
