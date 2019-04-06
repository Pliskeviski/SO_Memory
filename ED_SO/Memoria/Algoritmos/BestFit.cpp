#include "BestFit.h"

BestFit::BestFit() {
}

void* BestFit::InsereProcesso(Processo* p) {
	if (this->l_livres->GetSize() == 0) {
		std::cout << "Nenhuma posicao livre foi encontrada\n";
	};

	auto node = ((EspacoMemoria*)this->l_livres->get(0)->conteudo)->node;

	return this->InserePosicao(p, node);
}
