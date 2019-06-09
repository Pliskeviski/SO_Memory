#include "WorstFit.h"

#include <iomanip>

WorstFit::WorstFit() : Algoritmo("WorstFit") {
}

void* WorstFit::InsereProcesso(Processo* p, LISTA lista, bool somenteProcura) {
	void* melhorPos = NULL;

	if (lista == LISTA::PRINCIPAL) {
		/*int melhorSequencia = -1;
		void* nodeInicioSequencia = NULL;

		int sequenciaAtual = 0;
		bool inSequencia = false;

		for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {
			auto node = this->l_memoria_principal->get(i);

			if (node->conteudo == NULL && !inSequencia) {
				inSequencia = true;
				sequenciaAtual++;
				nodeInicioSequencia = node;
			}
			else if (node->conteudo == NULL) {
				sequenciaAtual++;
			}
			else if (node->conteudo != NULL && inSequencia) {
				inSequencia = false;
				if (sequenciaAtual > melhorSequencia || melhorSequencia == -1) {
					melhorSequencia = sequenciaAtual;
					melhorPos = nodeInicioSequencia;
				}

				sequenciaAtual = 0;
			}
		}

		if (nodeInicioSequencia != NULL && melhorPos == NULL)
			melhorPos = nodeInicioSequencia;
*/
		//
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
			auto node = ((EspacoMemoria*)this->l_livres->get(i)->conteudo);
			if (node->sequencia > melhorSequencia || melhorSequencia == -1) {
				melhorPos = ((EspacoMemoria*)this->l_livres->get(i)->conteudo)->node;
				melhorSequencia = node->sequencia;
			}
		}
	}
	else if (lista == LISTA::LIVREORDENADA) {
		Node* node = this->l_livres_ordenada->get(this->l_livres_ordenada->GetSize() - 1);
		if (node != NULL)
			melhorPos = ((EspacoMemoria*)node->conteudo)->node;
	}

	if (melhorPos != NULL) {
		std::cout << "Inserindo processo " << p->Nome << std::endl;
		return this->InserePosicao(p, (Node*)melhorPos);
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;
}
