#pragma once

#include <iostream>
#include <vector>
#include <functional>

using EventoFuncao = std::function<void()>;

class ItemMenu {
public:

	ItemMenu(std::string texto, const EventoFuncao& funcao) : texto(texto), funcao(funcao) { }
	std::string texto;
	EventoFuncao funcao;
};

class Menu {
public:
	Menu() {
	}

	void addItem(std::string texto, const EventoFuncao& funcao) {
		this->itens_menu.push_back(ItemMenu(texto, funcao));
	}

	void Desenha() {
		for (auto item : itens_menu)
			std::cout << item.texto.c_str() << std::endl;
	}

	void LeEvento() {
		this->Desenha();

		int entrada;
		std::cin >> entrada;

		if (entrada < 0 || entrada > this->itens_menu.size())
			return;

		#ifdef __linux__ 
			system("clear");
		#else
			system("cls");
		#endif

		this->itens_menu[entrada].funcao();
	}

	void Sair() {
		exit(0);
	}

private:
	std::vector<ItemMenu> itens_menu;
};