#pragma once

#include "../Algoritmo.h"

class BestFit : public Algoritmo {
public:
	BestFit();
protected:
	void* InsereProcesso(Processo* p) override;
private:
};
