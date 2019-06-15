#include "FirstFit.h"

#include <iomanip>

FirstFit::FirstFit() : Algoritmo("FirstFit") {
}

void* FirstFit::InsereProcesso(Processo* p, LISTA lista, bool somenteProcura) {

	Node* posicaoInsercao = NULL;

	if (lista == LISTA::PRINCIPAL) {
		for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
			Node* node = this->l_livres_ocupados->get(i);
			EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

			if (espaco->node->conteudo == NULL && espaco->sequencia >= p->EspacoMemoria) {
				posicaoInsercao = espaco->node;
				break;
			}
		}
	}
	else if (lista == LISTA::LIVRE) { 
		for (int i = 0; i < this->l_livres->GetSize(); i++) {
			Node* node = this->l_livres->get(i);
			EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

			if (espaco->node->conteudo == NULL && espaco->sequencia >= p->EspacoMemoria) {
				posicaoInsercao = espaco->node;
				break;
			}
		}
	}
	else if (lista == LISTA::LIVREORDENADA) {
		for (int i = 0; i < this->l_livres_ordenada->GetSize(); i++) {
			Node* node = this->l_livres_ordenada->get(i);
			EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;

			if (espaco->node->conteudo == NULL && espaco->sequencia >= p->EspacoMemoria) {
				posicaoInsercao = espaco->node;
				break;
			}
		}
	}
	
	if (posicaoInsercao != NULL) {
		
		if (somenteProcura)
			return NULL;
		else
			return this->InserePosicao(p, posicaoInsercao);
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;

}