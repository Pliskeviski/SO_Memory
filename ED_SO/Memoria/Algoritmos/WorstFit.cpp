#include "WorstFit.h"

#include <iomanip>

WorstFit::WorstFit() : Algoritmo("WorstFit") {
}

void* WorstFit::InsereProcesso(Processo* p, LISTA lista, bool somenteProcura) {
	void* melhorPos = NULL;

	if (lista == LISTA::PRINCIPAL) {
		int melhorSequencia = -1;

		for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
			Node* node = this->l_livres_ocupados->get(i);
			EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

			if ((espaco->sequencia > melhorSequencia || melhorSequencia == -1) && espaco->sequencia >= p->EspacoMemoria && espaco->node->conteudo == NULL) {
				melhorPos = ((EspacoMemoria*)node->conteudo)->node;
				melhorSequencia = espaco->sequencia;
			}
		}
	}
	else if (lista == LISTA::LIVRE) {
		int melhorSequencia = -1;

		for (int i = 0; i < this->l_livres->GetSize(); i++) {
			Node* node = this->l_livres->get(i);
			EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

			if ((espaco->sequencia > melhorSequencia || melhorSequencia == -1) && espaco->sequencia >= p->EspacoMemoria && espaco->node->conteudo == NULL) {
				melhorPos = espaco->node;
				melhorSequencia = espaco->sequencia;
			}
		}
	}
	else if (lista == LISTA::LIVREORDENADA) {
		Node* node = this->l_livres_ordenada->RecuperaUltimo();
		EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

		if (espaco->sequencia >= p->EspacoMemoria) {
			melhorPos = espaco->node;
		}
		//for (int i = this->l_livres_ordenada->GetSize() - 1; i >= 0; i--) {
		//	Node* node = this->l_livres_ordenada->get(i);
		//	EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;
		//
		//	if (espaco->sequencia >= p->EspacoMemoria) {
		//		melhorPos = espaco->node;
		//		break;
		//	}
		//}
		//for (int i = 0; i < this->l_livres_ordenada->GetSize(); i++) {
		//	Node* node = this->l_livres_ordenada->get(i);
		//	EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;
		//
		//	if ((espaco->sequencia > melhorSequencia || melhorSequencia == -1) && espaco->sequencia >= p->EspacoMemoria && espaco->node->conteudo == NULL) {
		//		melhorPos = espaco->node;
		//		melhorSequencia = espaco->sequencia;
		//	}
		//}
	}

	if (melhorPos != NULL) {

		if (somenteProcura)
			return (void*)p;
		else
			return this->InserePosicao(p, (Node*)melhorPos);
	}

	//std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;
}
