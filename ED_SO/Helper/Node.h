#pragma once

struct Node {
	Node() {}
	Node(void* conteudo) : conteudo(conteudo), proximo(0) {}

	void* conteudo;
	Node* proximo;
};