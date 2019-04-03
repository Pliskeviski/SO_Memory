#include "FirstFit.h"

FirstFit::FirstFit() : Algoritmo() {
}

void FirstFit::InsereProcesso(Processo* p) {
	for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
		auto node = this->l_livres_ocupados->get(i);
		if (node->conteudo == NULL) {
			std::cout << "Inserindo processo " << p->Nome << std::endl;
			this->InserePosicao(p, node);
			return;
		}
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
}

void FirstFit::RemoveProcesso(const char* nome) {
	Processo p(nome);
	this->l_livres_ocupados->RemoverConteudo(p);
	this->l_ocupados->Remover(p);
}

