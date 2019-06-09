#include "BestFit.h"

#include <iomanip>

BestFit::BestFit() : Algoritmo("BestFit") {
}

void* BestFit::InsereProcesso(Processo* p, LISTA lista) {

	void* melhorPos = NULL;

	if (lista == LISTA::PRINCIPAL) {
		int melhorSequencia = -1;

		for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
			Node* node = this->l_livres_ocupados->get(i);
			EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

			if ((espaco->sequencia < melhorSequencia || melhorSequencia == -1) && espaco->sequencia >= p->EspacoMemoria && espaco->node->conteudo == NULL) {
				melhorPos = ((EspacoMemoria*)this->l_livres_ocupados->get(i)->conteudo)->node;
				melhorSequencia = espaco->sequencia;
			}
		}
	}
	else if (lista == LISTA::LIVRE) {
		int melhorSequencia = -1;
		
		for (int i = 0; i < this->l_livres->GetSize(); i++) {
			auto node = ((EspacoMemoria*)this->l_livres->get(i)->conteudo);
			if (node->sequencia < melhorSequencia || melhorSequencia == -1 && node->sequencia >= p->EspacoMemoria) {
				melhorPos = ((EspacoMemoria*)this->l_livres->get(i)->conteudo)->node;
				melhorSequencia = node->sequencia;
			}
		}
	}
	else if (lista == LISTA::LIVREORDENADA) {
		int melhorSequencia = -1;
		for (int i = 0; i < this->l_livres_ordenada->GetSize(); i++) {
			auto node = ((EspacoMemoria*)this->l_livres_ordenada->get(i)->conteudo);
			if (node->sequencia < melhorSequencia || melhorSequencia == -1 && node->sequencia >= p->EspacoMemoria) {
				melhorPos = ((EspacoMemoria*)this->l_livres_ordenada->get(i)->conteudo)->node;
				melhorSequencia = node->sequencia;
			}
		}
	}

	if (melhorPos != NULL) {
		std::cout << "Inserindo processo " << p->Nome << std::endl;
		return this->InserePosicao(p, (Node*)melhorPos);
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;
}