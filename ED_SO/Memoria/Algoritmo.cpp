#include "Algoritmo.h"

#include "../Helper/Meditor.h"

#define MAX 10

Algoritmo::Algoritmo() {
	this->l_livres_ocupados = new Lista<Processo>();
	this->l_livres = new Lista<>();
	this->l_ocupados = new Lista<Processo>();
	this->l_ocupados_ordenado = new Lista<>();
}

void Algoritmo::Init(const char* filePath) {
	this->CarregaProcessosArquivo(filePath);

	for (Processo p : this->processos_arquivo) {
		Processo* processo = new Processo(p.Nome.c_str(), p.Alocacao, p.EspacoMemoria);
		this->l_livres_ocupados->Inserir(processo);
		this->l_ocupados->Inserir(processo);
	}
}

void Algoritmo::InserePosicao(Processo* p, Node* node) {
	auto n = this->l_livres_ocupados->InserirConteudo(p, node);
	this->l_ocupados->Inserir(p);
}

void Algoritmo::CarregaProcessosArquivo(const char* filePath) {
	FILE* file = std::fopen(filePath, "r+");
	if (!file) {
		std::cout << "Erro ao abrir o arquivo\n";
		return;
	}

	char nome[12];
	int  espac;
	int  alloc;
	
	for (; std::fscanf(file, "%s %d %d", nome, &espac, &alloc) != -1; this->processos_arquivo.insert(this->processos_arquivo.begin(), Processo(nome, alloc, espac)))
		if (this->processos_arquivo.size() >= MAX) break;

	fclose(file);
}

void Algoritmo::OrdenaOcupados() {
}

void Algoritmo::Insere(Processo p) {
	Processo* processo = new Processo(p.Nome.c_str(), p.Alocacao, p.EspacoMemoria);

	Meditor tempo; 

	this->InsereProcesso(processo);
	
	this->OrdenaOcupados();
	
	auto t = tempo.Fim();
	std::cout << "Tempo: " << t << " ms" << std::endl;
}

void Algoritmo::Remove(const char* nome) {
	this->RemoveProcesso(nome);
}

void Algoritmo::Print() {
	std::cout << "Livres Ocupados\n";
	this->l_livres_ocupados->Print();
	
	std::cout << "Ocupados\n";
	this->l_ocupados->Print();
}

Algoritmo::~Algoritmo() {
	delete l_livres_ocupados;
	delete l_livres;
	delete l_ocupados;
	delete l_ocupados_ordenado;
}
