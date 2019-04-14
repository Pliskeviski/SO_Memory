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

	/*
		dinamica = true
			cria um novo nó
		dinamica = false
			trabalha com os nós já existentes na lista
	*/
	double Insere(Processo* p, bool dinamica = false);
	double RemoveNome(const char* nome);
	void Remove();

	virtual void Print();

protected:
	virtual ~Algoritmo();
	
	Node* InserePosicao(Processo* p, Node* node);
	
	/*
		Insere um novo processo na "memoria"
	*/
	virtual void* InsereProcesso(Processo* p) = 0;

	/*
		Remove um processo da "memoria"
	*/
	virtual bool RemoveProcesso(const char* nome);

	Lista<Processo>* l_livres_ocupados; // Memoria principal

	Lista<EspacoMemoria>* l_livres;
	Lista<EspacoMemoria>* l_ocupados;
	Lista<EspacoMemoria>* l_ocupados_ordenado;

private:
	/*
		Carrega os Processos do arquivo para um vetor
	*/
	int CarregaProcessosArquivo(const char* filePath);
	std::vector<Processo> processos_arquivo;

	void OrganizaListas();
	void OrganizaOcupados();
	void OrganizaLivres();
	void OrganizaOcupadasOrdem();
};


class BubbleSort {
public:
	static void bubbleSort(Lista<EspacoMemoria>* lista) {
		int n = lista->GetSize();

		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - i - 1; j++) {
				if (((EspacoMemoria*)lista->get(j)->conteudo)->sequencia > ((EspacoMemoria*)lista->get(j + 1)->conteudo)->sequencia)
					swap(lista, j, j + 1);
			}
	}

private:
	static void swap(Lista<EspacoMemoria>* lista, int i, int j) {
		void* temp = lista->get(i)->conteudo;
		lista->get(i)->conteudo = lista->get(j)->conteudo;
		lista->get(j)->conteudo = temp;
	}
};