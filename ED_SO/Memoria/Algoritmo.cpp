#include "Algoritmo.h"

#include "../Helper/Meditor.h"

#define MAX 10

Algoritmo::Algoritmo() {
	this->l_memoria_principal = new Lista<Processo>();
	this->l_livres_ocupados = new Lista<EspacoMemoria>();
	this->l_livres = new Lista<EspacoMemoria>();
	this->l_ocupados = new Lista<EspacoMemoria>();
	this->l_ocupados_ordenado = new Lista<EspacoMemoria>();
}

int Algoritmo::Init(const char* filePath) {
	if (this->CarregaProcessosArquivo(filePath) == -1) return -1;

	for (Processo p : this->processos_arquivo) {
		Processo* processo = new Processo(p.Nome.c_str(), p.Alocacao, p.EspacoMemoria);
		this->l_memoria_principal->Inserir(processo);
		//this->l_ocupados->Inserir(processo);
	}
	
	return 0;
}

void Algoritmo::InserePosicao(Processo* p, Node* node) {
	auto n = this->l_memoria_principal->InserirConteudo(p, node);
	//this->l_ocupados->Inserir(p);
}

void Algoritmo::RemoveProcesso(const char* nome) {
	Processo p(nome);
	this->l_memoria_principal->RemoverConteudo(p);
	//this->l_ocupados->Remover(p);
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

void Algoritmo::OrganizaOcupados() {
	for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {

	}
}

void Algoritmo::Insere(Processo p) {
	Processo* processo = new Processo(p.Nome.c_str(), p.Alocacao, p.EspacoMemoria);

	Meditor tempo; 

	this->InsereProcesso(processo);
	
	this->OrganizaOcupados();
	
	auto t = tempo.Fim();
	std::cout << "Tempo: " << t << " ms" << std::endl;
}

void Algoritmo::Remove(const char* nome) {
	this->RemoveProcesso(nome);
}

void Algoritmo::Print() {
	std::cout << "Memoria principal\n";
	this->l_memoria_principal->Print();
	
	//std::cout << "Ocupados\n";
	//this->l_ocupados->Print();
}

Algoritmo::~Algoritmo() {
	delete this->l_memoria_principal;
	delete this->l_livres_ocupados;
	delete this->l_livres;
	delete this->l_ocupados;
	delete this->l_ocupados_ordenado;
}
