#pragma once

struct Node {
	Node() {}
	Node(void* conteudo, unsigned int index) : conteudo(conteudo), index(index), proximo(0) {}

	unsigned int index;
	void* conteudo;
	Node* proximo;
};