#include "FirstFit.h"

#include <iomanip>

FirstFit::FirstFit() : Algoritmo("FirstFit") {
}

void* FirstFit::InsereProcesso(Processo* p, LISTA lista) {

	if (lista == LISTA::PRINCIPAL) { // TODO
		for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
			auto node = this->l_livres_ocupados->get(i);
			if (node->conteudo == NULL) {
				std::cout << "Inserindo processo " << p->Nome << std::endl;
				return this->InserePosicao(p, node);
			}
		}
	}
	else if (lista == LISTA::LIVRE) { // TODO
		for (int i = 0; i < this->l_livres->GetSize(); i++) {
			auto node = ((EspacoMemoria*)this->l_livres->get(i)->conteudo)->node;
			if (node->conteudo == NULL) {
				std::cout << "Inserindo processo " << p->Nome << std::endl;
				return this->InserePosicao(p, node);
			}
		}
	}
	else if (lista == LISTA::LIVREORDENADA) { // TODO
		for (int i = 0; i < this->l_livres_ordenada->GetSize(); i++) {
			auto node = ((EspacoMemoria*)this->l_livres_ordenada->get(i)->conteudo)->node;
			if (node->conteudo == NULL) {
				std::cout << "Inserindo processo " << p->Nome << std::endl;
				return this->InserePosicao(p, node);
			}
		}
	}

	std::cout << "Nenhuma posicao livre foi encontrada\n";
	return NULL;
}

void FirstFit::Print() {
	std::cout << std::setw(5) << std::right << "Memoria " << this->getName() << std::endl;

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
