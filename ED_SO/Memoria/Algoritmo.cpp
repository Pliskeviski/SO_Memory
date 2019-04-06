#include "Algoritmo.h"

#include "../Helper/Meditor.h"

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

void Algoritmo::RemoveProcesso(const char* nome) {
	Processo p(nome);
	this->l_livres_ocupados->RemoverConteudo(p);
	this->OrganizaListas();
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
}

void Algoritmo::OrganizaOcupadasOrdem() {
	this->l_ocupados_ordenado->Reset();

	for (int i = 0; i < this->l_ocupados->GetSize(); i++) {
		EspacoMemoria* espacoMemoria = new EspacoMemoria(((EspacoMemoria*)this->l_ocupados->get(i)->conteudo)->node, ((EspacoMemoria*)this->l_ocupados->get(i)->conteudo)->sequencia);
		this->l_ocupados_ordenado->Inserir(espacoMemoria);
	}

	BubbleSort::bubbleSort(this->l_ocupados_ordenado);
}

void Algoritmo::Insere(Processo p, bool dinamica) {
	Processo* processo = new Processo(p.Nome.c_str(), p.Alocacao, p.EspacoMemoria);

	Meditor tempo; 

	if(dinamica)
		this->l_livres_ocupados->Inserir(processo);
	else
		this->InsereProcesso(processo);

	this->OrganizaListas();
	
	auto t = tempo.Fim();
	
	//std::cout << "Tempo: " << t << " ms" << std::endl;
}

void Algoritmo::Remove(const char* nome) {
	this->RemoveProcesso(nome);
	this->OrganizaListas();
}

void Algoritmo::Print() {
	std::cout << "Memoria principal\n";
	this->l_livres_ocupados->Print();
	
	std::cout << "\nOcupados\n";
	this->l_ocupados->Print();

	std::cout << "\nOcupados Ordenados\n";
	this->l_ocupados_ordenado->Print();

	std::cout << "\nLivres\n";
	this->l_livres->Print();
}

Algoritmo::~Algoritmo() {
	delete this->l_livres_ocupados;
	delete this->l_livres_ocupados;
	delete this->l_livres;
	delete this->l_ocupados;
	delete this->l_ocupados_ordenado;
}
