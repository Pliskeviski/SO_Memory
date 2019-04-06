#include "WorstFit.h"

#include <unordered_map>

WorstFit::WorstFit() {
}

void WorstFit::InsereProcesso(Processo* p) {

	std::unordered_map<int, int> umap;

	int sequencia = 0;
	int inicioSequencia = 0;

	bool ultimoNulo = false;

	// Procura as sequencias de nulos na memoria
	for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {
		auto node = this->l_memoria_principal->get(i);

		if (node->conteudo == NULL) {
			if (ultimoNulo == false)
				inicioSequencia = i;

			ultimoNulo = true;
			sequencia++;
		}
		else {
			umap[inicioSequencia] = sequencia;
			ultimoNulo = false;
			sequencia = 0;
		}
	}

	// Recupera o melhor index (maior sequencia de nulos)
	int maiorSequencia = -1;
	int melhorIndex = -1;
	for (auto x : umap) {
		if (x.second > maiorSequencia) {
			maiorSequencia = x.second;
			melhorIndex = x.first;
		}
	}

	if (melhorIndex == -1)
		std::cout << "Nenhuma posicao livre foi encontrada\n";
	else
		this->InserePosicao(p, this->l_memoria_principal->get(melhorIndex));
}