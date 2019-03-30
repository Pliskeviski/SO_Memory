#include "FirstFit.h"

FirstFit::FirstFit() : Algoritmo() { 
	
}

void FirstFit::InsereProcesso(Processo* p) {
	
	std::cout << "Inserindo processo " << p->Nome << std::endl;

	this->l_livres_ocupados->Inserir(p);
}

void FirstFit::RemoveProcesso(Processo p) {
	this->l_livres_ocupados->Remover(p);
}

