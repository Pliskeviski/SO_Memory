#pragma once
#include <iostream>

#include "../Helper/Node.h"

template<typename T = Node>
class Lista {
public:
	Lista();
	Node* Inserir(T* item);
	Node* InserirConteudo(T* conteudo, Node* node);
	void Remover(T item);
	bool RemoverConteudo(T node);

	void Print();

	int GetSize();

	Node* get(int index);
	~Lista();
private:
	unsigned int size;
	Node* cabeca;
	Node* ultimo;
};

template<typename T>
inline Lista<T>::Lista() {
	this->cabeca = NULL;
	this->ultimo = NULL;
	this->size = 0;
}

template<typename T>
inline Node* Lista<T>::Inserir(T* item) {
	if (this->cabeca == NULL) {
		this->cabeca = new Node(item);
		this->ultimo = cabeca;
		this->size++;
		return this->cabeca;
	}

	try {
		auto novo = new Node(item);
		ultimo->proximo = novo;
		ultimo = novo;
		this->size++;
		return novo;
	}
	catch (int e) {
		std::cout << "Erro ao inserir na Lista. " << e << std::endl;
		return NULL;
	}
}

template<typename T>
inline Node* Lista<T>::InserirConteudo(T* conteudo, Node* node) {
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
}

template<typename T>
inline bool Lista<T>::RemoverConteudo(T conteudo) {
	Node* prev = this->cabeca;
	Node* node = this->cabeca->proximo;

	if (prev != NULL && prev->conteudo != NULL && *(T*)prev->conteudo == conteudo) {
		this->cabeca->conteudo = NULL;
		return true;
	}

	for (; node != NULL; node = node->proximo) {
		if (node->conteudo != NULL && *(T*)node->conteudo == conteudo) {
			node->conteudo = NULL;
			return true;
		}

		prev = node;
	}

	return false;
}

template<typename T>
inline void Lista<T>::Print() {
	auto node = this->cabeca;
	for (; node != NULL; node = node->proximo) {
		if (node->conteudo != NULL)
			std::cout << *(T*)node->conteudo << std::endl;
		else
			std::cout << "NULL" << std::endl;
	}
}

template<typename T>
inline int Lista<T>::GetSize() {
	return this->size;
}

template<typename T>
inline Node* Lista<T>::get(int index) {
	auto node = this->cabeca;
	for (int i = 0; i <= index; i++) {
		if (node == NULL) break;

		if (i == index)
			return node;
		
		node = node->proximo;
	}

	return NULL;
}

template<typename T>
inline Lista<T>::~Lista() { // TODO
	//while (this->size != 0)
		//this->Remover((T*)this->cabeca->conteudo);
}
