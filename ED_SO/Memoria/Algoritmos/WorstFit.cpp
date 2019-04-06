#include "WorstFit.h"

WorstFit::WorstFit() {
}

void* WorstFit::InsereProcesso(Processo* p) {
	if (this->l_livres->GetSize() == 0) {
		std::cout << "Nenhuma posicao livre foi encontrada\n";
	};

	auto node = ((EspacoMemoria*)this->l_livres->get(this->l_livres->GetSize() - 1)->conteudo)->node;

	return this->InserePosicao(p, node);
}