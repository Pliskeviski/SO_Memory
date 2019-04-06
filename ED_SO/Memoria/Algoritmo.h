#pragma once
#include <vector>

#include "Processo.h"
#include "../Lista/Lista.h"
#include "EspacoMemoria.h"

// Classe base para a implementacao dos algoritmos
class Algoritmo {
public:
	Algoritmo();
	int Init(const char* filePath);
	void Insere(Processo p);
	void Remove(const char* nome);

	void Print();

protected:
	void OrganizaOcupados();

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

	Lista<Processo>* l_memoria_principal;

	Lista<EspacoMemoria>* l_livres_ocupados;
	Lista<EspacoMemoria>* l_livres;
	Lista<EspacoMemoria>* l_ocupados;
	Lista<EspacoMemoria>* l_ocupados_ordenado;

private:
	/*
		Carrega os Processos do arquivo para um vetor
	*/
	int CarregaProcessosArquivo(const char* filePath);
	std::vector<Processo> processos_arquivo;
};
