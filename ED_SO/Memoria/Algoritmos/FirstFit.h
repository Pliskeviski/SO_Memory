#pragma once

#include "../Algoritmo.h"

class FirstFit : public Algoritmo {
public:
	FirstFit();
protected:
	virtual void InsereProcesso(Processo* p) override;
	virtual void RemoveProcesso(Processo p) override;
};