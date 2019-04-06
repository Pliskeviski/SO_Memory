#include <iostream>

#include "../Helper/Node.h"
#include "Processo.h"

struct EspacoMemoria {
	EspacoMemoria(Node* node, int sequencia = 0) : node(node), sequencia(sequencia) {}

	Node* node;
	int sequencia;

	friend std::ostream& operator << (std::ostream &out, const EspacoMemoria &e) {
		out << e.node->index << " - " << e.sequencia;
		return out;
	}
};