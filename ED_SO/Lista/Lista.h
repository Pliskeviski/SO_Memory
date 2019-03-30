#pragma once
#include <iostream>


struct Node {
	Node() {}
	Node(void* conteudo) : conteudo(conteudo), proximo(NULL) {}

	void* conteudo;
	Node* proximo;
};

template<typename T>
class Lista {
public:
	Lista();
	bool Inserir(T* item);
	void Remover(T item);

	void Print();

	T get(int index);
	~Lista();
private:
	Node* cabeca;
	Node* ultimo;
	unsigned int size;
};

template<typename T>
inline Lista<T>::Lista() {
	this->cabeca = NULL;
	this->ultimo = NULL;
	this->size = 0;
}

template<typename T>
inline bool Lista<T>::Inserir(T* item) {
	if (this->cabeca == NULL) {
		this->cabeca = new Node(item);
		this->ultimo = cabeca;
		this->size++;
		return true;
	}

	try {
		auto novo = new Node(item);
		ultimo->proximo = novo;
		ultimo = novo;
	}
	catch (int e) {
		std::cout << "Erro ao inserir na Lista. " << e << std::endl;
		return false;
	}

	this->size++;
	return true;
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
inline void Lista<T>::Print() {
	auto node = this->cabeca;
	for (; node != NULL; node = node->proximo)
		std::cout << *(int*)node->conteudo << std::endl;
}

template<typename T>
inline T Lista<T>::get(int index) {
	auto node = this->cabeca;
	for (int i = 0; i <= index; i++) {
		if (node == NULL) break;

		if (i == index)
			return *(T*)node->conteudo;
		
		node = node->proximo;
	}

	return NULL;
}

template<typename T>
inline Lista<T>::~Lista() { // TODO
	//while (this->size != 0)
		//this->Remover((T*)this->cabeca->conteudo);
}
