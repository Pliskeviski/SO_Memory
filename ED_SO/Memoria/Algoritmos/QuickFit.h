#pragma once

#include "../Algoritmo.h"

class QuickFit : public Algoritmo {
public:
	QuickFit(const char* filePath);
private:
	virtual void InsereProcesso(Processo p);
	virtual void RemoveProcesso(Processo p);
}; 