#include "Algoritmo.h"

#include "../Helper/Meditor.h"

#include <algorithm> 
#include <chrono> 
#include <iomanip>

Algoritmo::Algoritmo(std::string nome) : nome(nome) {
	this->l_memoria_principal = new Lista<Processo>();

	this->l_livres_ocupados = new Lista<EspacoMemoria>();
	this->l_livres = new Lista<EspacoMemoria>();
	this->l_livres_ordenada = new Lista<EspacoMemoria>();
	this->l_ocupados = new Lista<EspacoMemoria>();
	this->l_ocupados_ordenado = new Lista<EspacoMemoria>();
}

int Algoritmo::Init(const char* filePath) {
	if (this->CarregaProcessosArquivo(filePath) == -1) return -1;

	for (Processo p : this->processos_arquivo) {
		for(int i = 0; i < p.EspacoMemoria; i++)
			this->Insere(&p, LISTA::NOLISTA); // Inicia os processos na memoria
	}
	
	return 0;
}

/*
	Insere o Processo no conteudo Node
*/
Node* Algoritmo::InserePosicao(Processo* p, Node* node) {
	Node* primeiro = NULL;
	for (int i = 0; i < p->EspacoMemoria; i++) {
		Node* inserido = NULL;
		if (primeiro == NULL)
			inserido = primeiro = this->l_memoria_principal->InserirConteudo(p, node);
		else
			inserido = this->l_memoria_principal->InserirConteudo(p, node);
		
		if (inserido == NULL) return NULL;

		node = node->proximo;
	}

	return primeiro;
}

bool Algoritmo::RemoveProcesso(const char* nome) {
	Processo p(nome);
	return this->l_memoria_principal->RemoverConteudo(p);
}

int Algoritmo::CarregaProcessosArquivo(const char* filePath, int max_itens) {
	FILE* file = std::fopen(filePath, "r+");
	if (!file) {
		std::cout << "Erro ao abrir o arquivo\n";
		return -1;
	}

	char nome[12];
	int  espac;
	int  alloc;

	for (; std::fscanf(file, "%s %d %d", nome, &espac, &alloc) != -1; this->processos_arquivo.insert(this->processos_arquivo.begin(), Processo(nome, alloc, espac))) 
		if (max_itens > 0 && this->processos_arquivo.size() >= max_itens) break;

	fclose(file);

	std::reverse(this->processos_arquivo.begin(), this->processos_arquivo.end());

	return 0;
}

void Algoritmo::OrganizaListas() {
	this->OrganizaLivresOcupadas();
	this->OrganizaOcupados();
	this->OrganizaLivres();
	this->OrganizaOcupadasOrdem();
}

void Algoritmo::OrganizaLivresOcupadas() {
	this->l_livres_ocupados->Reset();
	Node* inicio = NULL;
	int sequencia = 0;

	std::string ultimoProcesso = "";

	for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {
		auto node = this->l_memoria_principal->get(i);
		if (node == NULL) continue;

		std::string nomeProcesso = (node->conteudo == NULL ? "NULL" : ((Processo*)node->conteudo)->Nome);

		if (ultimoProcesso != nomeProcesso) {
			sequencia = 0;
			inicio = NULL;
		}

		if (node->conteudo == NULL) {
			if (inicio == NULL && node->conteudo == NULL && nomeProcesso == "NULL") { // Sequencia de nulos
				EspacoMemoria* espacoMemoria = new EspacoMemoria(node, sequencia++);
				inicio = this->l_livres_ocupados->Inserir(espacoMemoria);
			}
			else if (node->conteudo == NULL && nomeProcesso == "NULL") {
				((EspacoMemoria*)inicio->conteudo)->sequencia = sequencia++;
			}
			else if (node->conteudo != NULL && nomeProcesso == "NULL") {
				inicio = NULL;
				sequencia = 0;
			}
		}

		if (node->conteudo != NULL) {
			if (inicio == NULL && node->conteudo != NULL && ultimoProcesso != nomeProcesso) { // Sequencia de processos
				EspacoMemoria* espacoMemoria = new EspacoMemoria(node, sequencia++);
				inicio = this->l_livres_ocupados->Inserir(espacoMemoria);
			}
			else if (node->conteudo != NULL && ultimoProcesso == nomeProcesso) {
				((EspacoMemoria*)inicio->conteudo)->sequencia = sequencia++;
			}
			else if (node->conteudo == NULL && ultimoProcesso != nomeProcesso) {
				inicio = NULL;
				sequencia = 0;
			}

		}
		
		ultimoProcesso = nomeProcesso;
	}
}

void Algoritmo::OrganizaOcupados() {
	this->l_ocupados->Reset();
	Node* inicio = NULL;
	int sequencia = 0;

	for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {
		auto node = this->l_memoria_principal->get(i);
		if (node == NULL) continue;

		if (inicio == NULL && node->conteudo != NULL) {
			EspacoMemoria* espacoMemoria = new EspacoMemoria(node, sequencia++);
			inicio = this->l_ocupados->Inserir(espacoMemoria);
		}
		else if (node->conteudo != NULL) {
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
	this->l_livres_ordenada->Reset();

	Node* inicio = NULL;
	Node* inicioOrd = NULL;
	int sequencia = 0;

	for (int i = 0; i < this->l_memoria_principal->GetSize(); i++) {
		auto node = this->l_memoria_principal->get(i);
		if (node == NULL) continue;

		if (inicio == NULL && node->conteudo == NULL) {
			inicio = this->l_livres->Inserir(new EspacoMemoria(node, sequencia));
			inicioOrd = this->l_livres_ordenada->Inserir(new EspacoMemoria(node, sequencia));
			sequencia++;
		}
		else if (node->conteudo == NULL) {
			((EspacoMemoria*)inicio->conteudo)->sequencia = sequencia;
			((EspacoMemoria*)inicioOrd->conteudo)->sequencia = sequencia;
			sequencia++;
		}
		else {
			inicio = NULL;
			inicioOrd = NULL;
			sequencia = 0;
		}
	}

	BubbleSort::bubbleSort(this->l_livres_ordenada);
}

void Algoritmo::OrganizaOcupadasOrdem() {
	this->l_ocupados_ordenado->Reset();

	for (int i = 0; i < this->l_ocupados->GetSize(); i++) {
		auto node = this->l_ocupados->get(i);
		if (node == NULL) continue;

		EspacoMemoria* espacoMemoria = new EspacoMemoria(((EspacoMemoria*)node->conteudo)->node, ((EspacoMemoria*)node->conteudo)->sequencia);
		this->l_ocupados_ordenado->Inserir(espacoMemoria);
	}

	BubbleSort::bubbleSort(this->l_ocupados_ordenado);
}

double Algoritmo::Insere(Processo* p, LISTA lista, bool somenteProcura) {
	Processo* processo = NULL;

	if (p != NULL && p->Nome != "--")
		processo = new Processo(p->Nome.c_str(), p->Alocacao, p->EspacoMemoria);

	Meditor tempo;

	void* retorno = NULL;

	if (lista == LISTA::NOLISTA)
		retorno = (void*)this->l_memoria_principal->Inserir(processo); // Processo vai ser inserido no fim da lista
	else {
		//std::cout << "Inserindo processo " << p->Nome << std::endl;
		retorno = this->InsereProcesso(processo, lista, somenteProcura);
	}


	if (retorno != NULL && lista != LISTA::NOLISTA) {
		auto t = tempo.Fim();
		this->OrganizaListas();
		return t;
	}
	else
		return 0;
}

double Algoritmo::RemoveNome(const char* nome) {
	Meditor tempo;

	bool removido = this->RemoveProcesso(nome);
	
	if(removido)
		this->OrganizaListas();
	else {
		//std::cout << "Nao foi possivel remover o processo!\n";
		return -1;
	}

	auto t = tempo.Fim();
	return t;
}

int Algoritmo::Remove() {
	auto node = this->l_livres_ordenada->get(0);
	if (node == NULL) {
		//std::cout << "Nenhuma posicao livre para exclusao\n";
		return -1;
	}
	else {
		EspacoMemoria* espaco = (EspacoMemoria*)node->conteudo;
		if (this->l_memoria_principal->RemoveNode((Node*)espaco->node)) {
			return 0;
		}
		this->OrganizaListas();
	}

	return -1;
}

void Algoritmo::Print() {
	std::cout << std::setw(5) << std::right << "Memoria " << this->getName() << std::endl;

	// Livres Ocupadas
	std::cout << std::setw(20) << std::right << "\nLivres Ocupadas" << std::endl;
	std::cout << std::setw(5) << std::right << "Posicao" << " - " << "Nome" << " - " << "Tamanho" << std::endl;
	for (int i = 0; i < this->l_livres_ocupados->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_livres_ocupados->get(i)->conteudo;
		auto node = conteudo->node;
		std::string nome = ((Processo*)node->conteudo == NULL ? "NULL" : ((Processo*)node->conteudo)->Nome);

		std::cout << std::setw(7) << std::right << node->index << " - " << std::setw(4) << nome << " - " << (conteudo->sequencia + 1) << std::endl;
	}

	// Ocupados
	std::cout << std::setw(20) << std::right << "\nOcupados" << std::endl;
	std::cout << std::setw(5) << std::right << "Posicao" << " - " << "Tamanho" << std::endl;
	for (int i = 0; i < this->l_ocupados->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_ocupados->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(7) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}

	// Ocupados Ordenados
	std::cout << std::setw(20) << std::right << "\nOcupados Ordenados" << std::endl;
	std::cout << std::setw(5) << std::right << "Posicao" << " - " << "Tamanho" << std::endl;
	for (int i = 0; i < this->l_ocupados_ordenado->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_ocupados_ordenado->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(7) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}

	// Livres
	std::cout << std::setw(20) << std::right << "\nLivres" << std::endl;
	std::cout << std::setw(5) << std::right << "Posicao" << " - " << "Tamanho" << std::endl;
	for (int i = 0; i < this->l_livres->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_livres->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(7) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}

	// Livres Ordenadas
	std::cout << std::setw(20) << std::right << "\nLivres Ordenadas" << std::endl;
	std::cout << std::setw(5) << std::right << "Posicao" << " - " << "Tamanho" << std::endl;
	for (int i = 0; i < this->l_livres_ordenada->GetSize(); i++) {
		EspacoMemoria* conteudo = (EspacoMemoria*)this->l_livres_ordenada->get(i)->conteudo;
		auto node = conteudo->node;

		std::cout << std::setw(7) << std::right << node->index << " - " << conteudo->sequencia << std::endl;
	}
}

void Algoritmo::AdicionaOperacao(Operacao op) {
	this->operacoes.push_back(op);
}

std::vector<Operacao>& Algoritmo::RecuperaOperacoes() {
	return this->operacoes;
}

std::string& Algoritmo::getName() {
	return this->nome;
}

Lista<EspacoMemoria>* Algoritmo::RecuperaLivresOcupadas() {
	return this->l_livres_ocupados;
}

Algoritmo::~Algoritmo() {
	delete this->l_memoria_principal;
	delete this->l_livres_ordenada;
	delete this->l_livres;
	delete this->l_ocupados;
	delete this->l_ocupados_ordenado;
}
