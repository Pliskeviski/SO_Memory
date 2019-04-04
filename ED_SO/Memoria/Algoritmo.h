#pragma once
#include <vector>

#include "Processo.h"
#include "../Lista/Lista.h"

// Classe base para a implementacao dos algoritmos
class Algoritmo {
public:
	Algoritmo();
	int Init(const char* filePath);
	void Insere(Processo p);
	void Remove(const char* nome);

	void Print();

protected:
	void OrdenaOcupados();

	virtual ~Algoritmo();
	
	void InserePosicao(Processo* p, Node* node);
	
	/*
		Insere um novo processo na "memoria"
	*/
	virtual void InsereProcesso(Processo* p) = 0;

	/*
		Remove um processo da "memoria"
	*/
	virtual void RemoveProcesso(const char* nome);

	Lista<Processo>* l_livres_ocupados;
	Lista<>* l_livres;
	Lista<Processo>* l_ocupados;
	Lista<>* l_ocupados_ordenado;

private:
	/*
		Carrega os Processos do arquivo para um vetor
	*/
	int CarregaProcessosArquivo(const char* filePath);
	std::vector<Processo> processos_arquivo;
};
