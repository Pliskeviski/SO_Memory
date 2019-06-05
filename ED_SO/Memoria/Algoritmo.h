#pragma once
#include <vector>

#include "Processo.h"
#include "../Lista/Lista.h"
#include "EspacoMemoria.h"

enum LISTA {
	NOLISTA = -1,
	PRINCIPAL = 0,
	LIVRE = 1,
	LIVREORDENADA = 2
};

struct Operacao {
	/*
		Operacao 1 = Insercao
		Operacao 2 = Remocao
	*/
	Operacao(int operacao, long tempo, LISTA lista = LISTA::NOLISTA) : operacao(operacao), tempo(tempo), lista(lista) {}
	int operacao;
	long tempo;
	LISTA lista;
};

// Classe base para a implementacao dos algoritmos
class Algoritmo {
public:
	Algoritmo(std::string nome);
	int Init(const char* filePath);

	/*
		dinamica = true
			cria um novo n�
		dinamica = false
			trabalha com os n�s j� existentes na lista
	*/
	double Insere(Processo* p, LISTA lista, bool dinamica = false);
	double RemoveNome(const char* nome);
	int Remove();

	virtual void Print();
	
	void AdicionaOperacao(Operacao op);
	std::vector<Operacao>& RecuperaOperacoes();

	std::string& getName();
protected:
	virtual ~Algoritmo();
	
	Node* InserePosicao(Processo* p, Node* node);
	
	/*
		Insere um novo processo na "memoria"
	*/
	virtual void* InsereProcesso(Processo* p, LISTA lista) = 0;

	/*
		Remove um processo da "memoria"
	*/
	virtual bool RemoveProcesso(const char* nome);

	Lista<Processo>* l_livres_ocupados; // Memoria principal

	Lista<EspacoMemoria>* l_livres;
	Lista<EspacoMemoria>* l_livres_ordenada;
	Lista<EspacoMemoria>* l_ocupados;
	Lista<EspacoMemoria>* l_ocupados_ordenado;

	virtual void OrganizaListas();
	void OrganizaOcupados();
	void OrganizaLivres();
	void OrganizaOcupadasOrdem();
private:
	/*
		Carrega os Processos do arquivo para um vetor
	*/
	int CarregaProcessosArquivo(const char* filePath, int max_itens = 0);
	std::vector<Processo> processos_arquivo;
	std::vector<Operacao> operacoes;
	std::string nome;
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