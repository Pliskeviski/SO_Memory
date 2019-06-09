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

void QuickFit::OrganizaListas() {
	this->OrganizaLivresOcupadas();
	this->OrganizaOcupados();
	this->OrganizaLivres();
	this->OrganizaOcupadasOrdem();
	this->OrganizaListasEspacos();
}

void* QuickFit::InsereProcesso(Processo* p, LISTA lista, bool somenteProcura) {
	int melhor = -1;
	for (int i : this->tamanhos) {
		if (i > p->EspacoMemoria) {
			melhor = i;
		}
		else {
			break;
		}
	}

	if (melhor == -1)
		return NULL;
	
	auto espaco = this->listasEspaco[melhor];

	if (espaco->GetSize() == 0) {
		std::cout << "Espaço insuficiente\n";
		return NULL;
	}

	return this->InserePosicao(p, espaco->get(0));
}

void QuickFit::OrganizaListasEspacos() {
	for (int i : this->tamanhos) 
		this->listasEspaco[i]->Reset();

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

			for (int i = this->tamanhos.size() - 1; i != 0; i--) {
				if (this->tamanhos[i] == sequenciaAtual) {
					EspacoMemoria* espacoMemoria = new EspacoMemoria(((EspacoMemoria*)node->conteudo)->node, ((EspacoMemoria*)node->conteudo)->sequencia);
					this->listasEspaco[this->tamanhos[i]]->Inserir(espacoMemoria);
				}
			}
			
			sequenciaAtual = 0;
			nodeInicioSequencia = NULL;
		}
	}

	
}
