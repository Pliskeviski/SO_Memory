#pragma once
#include <iostream>
#include <iomanip>

#include "../Helper/Node.h"

template<typename T = Node>
class Lista {
public:
	Lista();
	Node* Inserir(T* item);
	Node* InserirConteudo(T* conteudo, Node* node);
	void Remover(T item);
	bool RemoverConteudo(T node);
	bool RemoveNode(Node* node);
	
	void Reset();

	void Print();

	int GetSize();

	Node* get(int index);
	~Lista();
private:
	unsigned int size;
	Node* cabeca;
	Node* ultimo;
	unsigned int index;

	// Otimizacao na busca
	unsigned int ultimo_index;
	Node* ultimo_node;
};

template<typename T>
inline Lista<T>::Lista() {
	this->cabeca = NULL;
	this->ultimo = NULL;
	this->size = 0;
	this->index = 0;
}

template<typename T>
inline Node* Lista<T>::Inserir(T* item) {
	if (this->cabeca == NULL) {
		this->cabeca = new Node(item, this->index++);
		this->ultimo = cabeca;
		this->size++;
		return this->cabeca;
	}

	auto novo = new Node(item, this->index++);
	ultimo->proximo = novo;
	ultimo = novo;
	this->size++;
	return novo;
}

template<typename T>
inline Node* Lista<T>::InserirConteudo(T* conteudo, Node* node) {
	if (node->conteudo != NULL) return NULL; // Nao deixa inserir onde j� existe um conteudo

	node->conteudo = conteudo;
	return node;
}

template<typename T>
inline void Lista<T>::Remover(T item) {
	
	Node* prev = this->cabeca;
	Node* node = this->cabeca->proximo;

	if (prev != NULL && *(T*)prev->conteudo == item) {
		delete prev->conteudo;
		delete prev;
		this->cabeca = node;
		size--;
		return;
	}

	for (; node != NULL; node = node->proximo) {
		if (*(T*)node->conteudo == item) {
			if (prev != NULL) {
				prev->proximo = node->proximo;
				delete node->conteudo;
				delete node;
				size--;
				return;
			}
		}

		prev = node;
	}

	this->ultimo = this->get(this->GetSize() - 1);
}

template<typename T>
inline bool Lista<T>::RemoverConteudo(T conteudo) {
	Node* prev = this->cabeca;
	Node* node = this->cabeca->proximo;

	bool removido = false;

	if (prev != NULL && prev->conteudo != NULL && *(T*)prev->conteudo == conteudo) {
		this->cabeca->conteudo = NULL;
		return true;
	}

	for (; node != NULL; node = node->proximo) {
		if (node->conteudo != NULL && *(T*)node->conteudo == conteudo) {
			node->conteudo = NULL;
			removido = true;
		}

		prev = node;
	}

	return removido;
}

template<typename T>
inline bool Lista<T>::RemoveNode(Node* node) {
	Node* anterior = NULL;

	if (node == this->cabeca) {
		this->cabeca = node->proximo;
		delete node->conteudo;
		delete node;
		this->size--;
		return true;
	}

	anterior = this->cabeca;
	for (Node* nodeI = this->cabeca->proximo; nodeI != NULL; nodeI = nodeI->proximo) {
		if (nodeI == node) {
			anterior->proximo = nodeI->proximo;
			delete node->conteudo;
			delete node;
			this->size--;
			return true;
		}

		anterior = nodeI;
	}

	return false;
}

template<typename T>
inline void Lista<T>::Reset() {
	while (this->cabeca != NULL) {

		if(this->cabeca->conteudo != NULL)
			delete this->cabeca->conteudo;

		Node* cabeca = this->cabeca;
		Node* proximo = this->cabeca->proximo;
		delete cabeca;

		this->cabeca = proximo;
	}

	this->size = 0;
}

template<typename T>
inline void Lista<T>::Print() {
	auto node = this->cabeca;

	if (node == NULL) {
		std::cout << std::setw(5) << std::right << "Vazio" << std::endl;
		return;
	}

	for (; node != NULL; node = node->proximo) {
		if (node->conteudo != NULL)
			std::cout << std::setw(5) << std::right << node->index << " - " << *(T*)node->conteudo << std::endl;
		else
			std::cout << std::setw(5) << std::right << node->index << " - " << "NULL" << std::endl;
	}
}

template<typename T>
inline int Lista<T>::GetSize() {
	return this->size;
}

template<typename T>
inline Node* Lista<T>::get(int index) {
	auto node = this->cabeca;

	if (index == this->ultimo_index + 1) {
		this->ultimo_index++;
		this->ultimo_node = this->ultimo_node->proximo;
		return this->ultimo_node;
	}
	else {
		this->ultimo_index = 0;
		this->ultimo_node = NULL;
	}

	for (int i = 0; i <= index; i++) {
		if (node == NULL) break;

		if (i == index) {
			this->ultimo_index = i;
			this->ultimo_node = node;
			return node;
		}
		
		node = node->proximo;
	}

	return NULL;
}

template<typename T>
inline Lista<T>::~Lista() { // TODO
}
