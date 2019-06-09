#pragma once

#include "../Algoritmo.h"

class FirstFit : public Algoritmo {
public:
	FirstFit();
protected:
	virtual void* InsereProcesso(Processo* p, LISTA lista, bool somenteProcura) override;
};