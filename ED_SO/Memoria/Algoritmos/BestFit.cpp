#include "BestFit.h"

#include <iomanip>

BestFit::BestFit() {
}

void* BestFit::InsereProcesso(Processo* p, LISTA lista) {

	void* melhorPos = NULL;

	if (lista == LISTA::PRINCIPAL) {
		int melhorSequencia = -1;
		void* nodeInicioSequencia = NULL;

		int sequenciaAtual = 0;
		bool inSequencia = false;

		for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
			auto node = this->l_livres_ocupados->get(i);
			
			if (node->conteudo == NULL && !inSequencia) {
				inSequencia = true;
				sequenciaAtual++;
				nodeInicioSequencia = node;
			}
			else if(node->conteudo == NULL) {
				sequenciaAtual++;
			}
			else if (node->conteudo != NULL && inSequencia) {
				inSequencia = false;
				if (sequenciaAtual < melhorSequencia || melhorSequencia == -1) {
					melhorSequencia = sequenciaAtual;
					melhorPos = nodeInicioSequencia;
				}
				
				sequenciaAtual = 0;
			}
		}
	}
	else if (lista == LISTA::LIVRE) {
		int melhorSequencia = -1;
		
		for (int i = 0; i < this->l_livres->GetSize(); i++) {
			auto node = ((EspacoMemoria*)this->l_livres->get(i)->conteudo);
			if (node->sequencia < melhorSequencia || melhorSequencia == -1) {
				melhorPos = ((EspacoMemoria*)this->l_livres->get(i)->conteudo)->node;
				melhorSequencia = node->sequencia;
			}
		}
	}
	else if (lista == LISTA::LIVREORDENADA) {
		Node* node = this->l_livres_ordenada->get(0);
		if (node == NULL) goto fim;

		melhorPos = ((EspacoMemoria*)node->conteudo)->node;
	}
	fim:

	if (melhorPos != NULL) {
		std::cout << "Inserindo processo " << p->Nome << std::endl;
		return this->InserePosicao(p, (Node*)melhorPos);
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;
}

void BestFit::Print() {
	// Principal
	std::cout << std::setw(20) << std::right << "\nMemoria principal" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Nome" << std::endl;
	this->l_livres_ocupados->Print();

	// Ocupados
	std::cout << std::setw(20) << std::right << "\nOcupados" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	for (int i = 0; i < this->l_ocupados->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_ocupados->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(5) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}

	// Ocupados Ordenados
	std::cout << std::setw(20) << std::right << "\nOcupados Ordenados" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	for (int i = 0; i < this->l_ocupados_ordenado->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_ocupados_ordenado->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(5) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}

	// Livres
	std::cout << std::setw(20) << std::right << "\nLivres" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	for (int i = 0; i < this->l_livres->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_livres->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(5) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}

	// Livres
	std::cout << std::setw(20) << std::right << "\nLivres Ordenadas" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	for (int i = 0; i < this->l_livres_ordenada->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_livres_ordenada->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(5) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}
}