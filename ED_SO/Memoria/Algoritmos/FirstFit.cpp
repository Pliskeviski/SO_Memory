#include "FirstFit.h"

FirstFit::FirstFit() : Algoritmo() {
}

void FirstFit::InsereProcesso(Processo* p) {
	for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {
		auto node = this->l_memoria_principal->get(i);
		if (node->conteudo == NULL) {
			std::cout << "Inserindo processo " << p->Nome << std::endl;
			this->InserePosicao(p, node);
			return;
		}
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
}