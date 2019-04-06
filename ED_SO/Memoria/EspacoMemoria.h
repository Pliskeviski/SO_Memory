#include "Processo.h"

struct EspacoMemoria {
	EspacoMemoria(void* node, Processo* processo, int sequencia) : node(node), processo(processo), sequencia(sequencia) {}
	void* node;
	Processo* processo;
	int sequencia;
};