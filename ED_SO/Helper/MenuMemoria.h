#pragma once

#include <functional>
#include <vector>

#include "Menu.h"

#include "../Memoria/Algoritmos/FirstFit.h"
#include "../Memoria/Algoritmos/BestFit.h"
#include "../Memoria/Algoritmos/WorstFit.h"
#include "../Memoria/Algoritmos/QuickFit.h"

struct AdicionaProcesso {
	AdicionaProcesso(Processo& processo, int algoritmo, LISTA lista) : processo(processo), algoritmo(algoritmo), lista(lista) {}
	Processo& processo;
	int algoritmo;
	LISTA lista;
};

struct RemoveProcesso {
	RemoveProcesso(const char* nome_processo, int algoritmo) : nome_processo(nome_processo), algoritmo(algoritmo) {}
	std::string nome_processo;
	int algoritmo;
};

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

class MenuMemoria : public Menu {
public:
	MenuMemoria(std::string arquivo);
private:
	void NovoProcesso(void* p = NULL);
	void RemoverProcesso(void* p = NULL);
	void MostraMemoria(void* p = NULL);
	void MostrarEstatistica(void* p = NULL);
	void ExpandirMemoria(void* p = NULL);
	void ReduzirMemoria(void* p = NULL);
	void ExecutaArquivo(void* p = NULL);

	void ImprimeVetorEstatistica(Algoritmo* algoritmo);

	Algoritmo* RecuperaAlgoritmo(int alg = -1);

	FirstFit* firstFit;
	BestFit* bestFit;
	WorstFit* worstFit;
	QuickFit* quickFit;
};
