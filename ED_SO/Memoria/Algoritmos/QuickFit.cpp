#include "QuickFit.h"

#include <iomanip>

QuickFit::QuickFit() : Algoritmo("QuickFit") {
	this->tamanhos.push_back(4);
	this->tamanhos.push_back(8);
	this->tamanhos.push_back(16);

	// Listas com os tamanhos mais "comuns"
	for (int i : this->tamanhos)
		this->listasEspaco.insert(std::pair<int, Lista<EspacoMemoria>*>(i, new Lista<EspacoMemoria>()));
}

void QuickFit::Print() {
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

	// Espacos
	std::cout << std::setw(20) << std::right << "\nEspacos" << std::endl;
	std::cout << std::setw(5) << std::right << "Espacos" << " - " <<  "Index" << " - " << "Sequencia" << std::endl;
	for (int i : this->tamanhos) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->listasEspaco[i]->get(i)->conteudo;
		auto node = conteudo->node;
		std::cout << std::setw(5) << std::right << i << node->index << " - " << conteudo->sequencia << std::endl;
	}
}

void QuickFit::OrganizaListas() {
	this->OrganizaOcupados();
	this->OrganizaLivres();
	this->OrganizaOcupadasOrdem();
	this->OrganizaListasEspacos();
}

void* QuickFit::InsereProcesso(Processo* p, LISTA lista) {

	return nullptr;
}

void QuickFit::OrganizaListasEspacos() {
	this->listasEspaco.clear();

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
		else if (node->conteudo == NULL) {
			sequenciaAtual++;
		}
		else if (node->conteudo != NULL && inSequencia) {
			inSequencia = false;

			for (int i = this->tamanhos.size(); i > 0; i--) {
				if (this->tamanhos[i] == i) {
					EspacoMemoria* espacoMemoria = new EspacoMemoria(((EspacoMemoria*)node->conteudo)->node, ((EspacoMemoria*)node->conteudo)->sequencia);
					this->listasEspaco[this->tamanhos[i]]->Inserir(espacoMemoria);
				}
			}
			
			sequenciaAtual = 0;
			nodeInicioSequencia = NULL;
		}
	}

	
}
