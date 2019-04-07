#include "Algoritmo.h"

#include "../Helper/Meditor.h"

#include <algorithm> 
#include <chrono> 
#include <iomanip>

#define MAX 10

Algoritmo::Algoritmo() {
	this->l_livres_ocupados = new Lista<Processo>();
	this->l_livres = new Lista<EspacoMemoria>();
	this->l_ocupados = new Lista<EspacoMemoria>();
	this->l_ocupados_ordenado = new Lista<EspacoMemoria>();
}

int Algoritmo::Init(const char* filePath) {
	if (this->CarregaProcessosArquivo(filePath) == -1) return -1;

	for (Processo p : this->processos_arquivo)
		this->Insere(p, true);
	
	return 0;
}

Node* Algoritmo::InserePosicao(Processo* p, Node* node) {
	return this->l_livres_ocupados->InserirConteudo(p, node);
}

bool Algoritmo::RemoveProcesso(const char* nome) {
	Processo p(nome);
	return this->l_livres_ocupados->RemoverConteudo(p);
}

int Algoritmo::CarregaProcessosArquivo(const char* filePath) {
	FILE* file = std::fopen(filePath, "r+");
	if (!file) {
		std::cout << "Erro ao abrir o arquivo\n";
		return -1;
	}

	char nome[12];
	int  espac;
	int  alloc;
	
	for (; std::fscanf(file, "%s %d %d", nome, &espac, &alloc) != -1; this->processos_arquivo.insert(this->processos_arquivo.begin(), Processo(nome, alloc, espac)))
		if (this->processos_arquivo.size() >= MAX) break;

	fclose(file);

	return 0;
}

void Algoritmo::OrganizaListas() {
	this->OrganizaOcupados();
	this->OrganizaLivres();
	this->OrganizaOcupadasOrdem();
}

void Algoritmo::OrganizaOcupados() {
	this->l_ocupados->Reset();
	Node* inicio = NULL;
	int sequencia = 0;

	for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
		if (inicio == NULL && this->l_livres_ocupados->get(i)->conteudo != NULL) {
			EspacoMemoria* espacoMemoria = new EspacoMemoria(this->l_livres_ocupados->get(i), sequencia++);
			inicio = this->l_ocupados->Inserir(espacoMemoria);
		}
		else if (this->l_livres_ocupados->get(i)->conteudo != NULL) {
			((EspacoMemoria*)inicio->conteudo)->sequencia = sequencia++;
		}
		else {
			inicio = NULL;
			sequencia = 0;
		}
	}
}

void Algoritmo::OrganizaLivres() {
	this->l_livres->Reset();
	Node* inicio = NULL;
	int sequencia = 0;

	for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
		if (inicio == NULL && this->l_livres_ocupados->get(i)->conteudo == NULL) {
			EspacoMemoria* espacoMemoria = new EspacoMemoria(this->l_livres_ocupados->get(i), sequencia++);
			inicio = this->l_livres->Inserir(espacoMemoria);
		}
		else if (this->l_livres_ocupados->get(i)->conteudo == NULL) {
			((EspacoMemoria*)inicio->conteudo)->sequencia = sequencia++;
		}
		else {
			inicio = NULL;
			sequencia = 0;
		}
	}

	BubbleSort::bubbleSort(this->l_livres);
}

void Algoritmo::OrganizaOcupadasOrdem() {
	this->l_ocupados_ordenado->Reset();

	for (int i = 0; i < this->l_ocupados->GetSize(); i++) {
		EspacoMemoria* espacoMemoria = new EspacoMemoria(((EspacoMemoria*)this->l_ocupados->get(i)->conteudo)->node, ((EspacoMemoria*)this->l_ocupados->get(i)->conteudo)->sequencia);
		this->l_ocupados_ordenado->Inserir(espacoMemoria);
	}

	BubbleSort::bubbleSort(this->l_ocupados_ordenado);
}

double Algoritmo::Insere(Processo p, bool dinamica) {
	Processo* processo = new Processo(p.Nome.c_str(), p.Alocacao, p.EspacoMemoria);

	Meditor tempo; 

	void* retorno = NULL;

	if(dinamica)
		retorno = (void*)this->l_livres_ocupados->Inserir(processo);
	else
		retorno = this->InsereProcesso(processo);

	if (retorno == NULL)
		return -1;

	this->OrganizaListas();

	auto t = tempo.Fim();

	return t;
}

double Algoritmo::Remove(const char* nome) {
	Meditor tempo;

	bool removido = this->RemoveProcesso(nome);
	
	if(removido)
		this->OrganizaListas();
	else {
		std::cout << "Nao foi possivel remover o processo!\n";
		return -1;
	}

	auto t = tempo.Fim();
	return t;
}

void Algoritmo::Print() {
	// Principal
	std::cout << std::setw(20) << std::right << "\nMemoria principal" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Nome" << std::endl;
	this->l_livres_ocupados->Print();
	
	// Ocupados
	std::cout << std::setw(20) << std::right << "\nOcupados" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	this->l_ocupados->Print();

	// Ocupados Ordenados
	std::cout << std::setw(20) << std::right << "\nOcupados Ordenados" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	this->l_ocupados_ordenado->Print();

	// Livres
	std::cout << std::setw(20) << std::right << "\nLivres Ordenados" << std::endl;
	std::cout << std::setw(5) << std::right << "Index" << " - " << "Sequencia" << std::endl;
	this->l_livres->Print();
}

Algoritmo::~Algoritmo() {
	delete this->l_livres_ocupados;
	delete this->l_livres_ocupados;
	delete this->l_livres;
	delete this->l_ocupados;
	delete this->l_ocupados_ordenado;
}
