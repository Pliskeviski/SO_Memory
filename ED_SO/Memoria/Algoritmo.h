#pragma once
#include <vector>

#include "Processo.h"
#include "../Lista/Lista.h"

// Classe base para a implementacao dos algoritmos
class Algoritmo {
public:
	Algoritmo();
	void Init(const char* filePath);
	void Insere(Processo p);
	void Remove(Processo p);

protected:
	virtual ~Algoritmo();
	
	/*
		Insere um novo processo na "memoria"
	*/
	virtual void InsereProcesso(Processo* p) = 0;

	/*
		Remove um processo da "memoria"
	*/
	virtual void RemoveProcesso(Processo p) = 0;

	Lista<Processo>* l_livres_ocupados;
	Lista<Processo>* l_livres;
	Lista<Processo>* l_ocupados;
	Lista<Processo>* l_ocupados_ordenado;

private:
	/*
		Carrega os Processos do arquivo para um vetor
	*/
	void CarregaProcessosArquivo(const char* filePath);
	std::vector<Processo> processos_arquivo;
};
