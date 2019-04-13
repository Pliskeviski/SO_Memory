#pragma once

#include <functional>
#include <vector>

#include "Menu.h"

#include "../Memoria/Algoritmos/FirstFit.h"
#include "../Memoria/Algoritmos/BestFit.h"
#include "../Memoria/Algoritmos/WorstFit.h"

struct Operacao {
	/*
		Operacao 1 = Insercao
		Operacao 2 = Remocao
	*/
	Operacao(int operacao, long tempo) : operacao(operacao), tempo(tempo) { }
	int operacao;
	long tempo;
};

struct AdicionaProcesso {
	AdicionaProcesso(Processo& processo, int algoritmo) : processo(processo), algoritmo(algoritmo) {}
	Processo& processo;
	int algoritmo;
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

	void ImprimeVetorEstatistica(std::vector<Operacao>& vetor);

	FirstFit* firstFit;
	BestFit* bestFit;
	WorstFit* worstFit;

	std::vector<Operacao> operacoesFirstFit;
	std::vector<Operacao> operacoesBestFit;
	std::vector<Operacao> operacoesWorstFit;
};
