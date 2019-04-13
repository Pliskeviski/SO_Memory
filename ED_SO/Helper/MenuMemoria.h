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

#define BIND_FN(x) std::bind(&x, this)

class MenuMemoria : public Menu {
public:
	MenuMemoria(std::string arquivo);
private:
	void NovoProcesso();
	void RemoverProcesso();
	void MostraMemoria();
	void MostrarEstatistica();
	void ExpandirMemoria();
	void ReduzirMemoria();

	void ImprimeVetorEstatistica(std::vector<Operacao>& vetor);

	FirstFit* firstFit;
	BestFit* bestFit;
	WorstFit* worstFit;

	std::vector<Operacao> operacoesFirstFit;
	std::vector<Operacao> operacoesBestFit;
	std::vector<Operacao> operacoesWorstFit;
};
