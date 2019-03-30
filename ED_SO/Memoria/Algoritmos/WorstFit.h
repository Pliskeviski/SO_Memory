#pragma once

#include "../Algoritmo.h"

class WorstFit : public Algoritmo {
public:
	WorstFit(const char* filePath);
private:
	virtual void InsereProcesso(Processo p);
	virtual void RemoveProcesso(Processo p);
};