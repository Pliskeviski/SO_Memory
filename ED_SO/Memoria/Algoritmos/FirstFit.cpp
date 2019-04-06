#include "FirstFit.h"

FirstFit::FirstFit() : Algoritmo() {
}

void* FirstFit::InsereProcesso(Processo* p) {
	for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
		auto node = this->l_livres_ocupados->get(i);
		if (node->conteudo == NULL) {
			std::cout << "Inserindo processo " << p->Nome << std::endl;
			return this->InserePosicao(p, node);
		}
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;
}