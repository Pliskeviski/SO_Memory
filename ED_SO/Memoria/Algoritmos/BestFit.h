#pragma once

#include "../Algoritmo.h"

class BestFit : public Algoritmo {
public:
	BestFit();
	void InsereProcesso(Processo* p) override;
private:
};
