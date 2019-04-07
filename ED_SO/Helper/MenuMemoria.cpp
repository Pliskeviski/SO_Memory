#include "MenuMemoria.h"

MenuMemoria::MenuMemoria(std::string arquivo) {
	this->firstFit = new FirstFit();
	this->bestFit = new BestFit();
	this->worstFit = new WorstFit();

	this->firstFit->Init(arquivo.c_str());
	this->bestFit->Init(arquivo.c_str());
	this->worstFit->Init(arquivo.c_str());

	this->addItem("0 - Novo Processo", BIND_EVENT_FN(MenuMemoria::NovoProcesso));
	this->addItem("1 - Remover Processo", BIND_EVENT_FN(MenuMemoria::RemoverProcesso));
	this->addItem("2 - Mostra Memoria", BIND_EVENT_FN(MenuMemoria::MostraMemoria));
}
void MenuMemoria::NovoProcesso() {
	std::cin.get();

	std::string nome;
	std::cout << "Digite o nome do processo: \n";
	std::getline(std::cin, nome);

	unsigned int tamanho;
	std::cout << "Digite o tamanho do processo: \n";
	std::cin >> tamanho;

	std::cin.get();

	std::string dinamica;
	std::cout << "Memoria dinamica? S|N \n";
	std::getline(std::cin, dinamica);

	unsigned int alg;
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
	std::cin >> alg;

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	Processo processo = Processo(nome.c_str(), (dinamica == "S"), tamanho);

	double tempo;

	switch (alg) {
	case 1:
		tempo = this->firstFit->Insere(processo);
		if (tempo > 0)
			this->operacoesFirstFit.push_back(Operacao(1, tempo));
		break;
	case 2:
		tempo = this->bestFit->Insere(processo);
		if (tempo > 0)
			this->operacoesBestFit.push_back(Operacao(1, tempo));
		break;
	case 3:
		tempo = this->worstFit->Insere(processo);
		if (tempo > 0)
			this->operacoesWorstFit.push_back(Operacao(1, tempo));
		break;
	default:
		break;
	}

	if (tempo > 0)
		std::cout << "Processo inserido em: " << tempo << " microseconds\n";
}

void MenuMemoria::RemoverProcesso() {
	std::cin.get();

	std::string nome;
	std::cout << "Digite o nome do processo: \n";
	std::getline(std::cin, nome);
	
	unsigned int alg;
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
	std::cin >> alg;

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	double tempo;

	switch (alg) {
	case 1:
		tempo = this->firstFit->Remove(nome.c_str());
		if (tempo > 0)
			this->operacoesFirstFit.push_back(Operacao(1, tempo));
		break;
	case 2:
		tempo = this->bestFit->Remove(nome.c_str());
		if (tempo > 0)
			this->operacoesBestFit.push_back(Operacao(1, tempo));
		break;
	case 3:
		tempo = this->worstFit->Remove(nome.c_str());
		if (tempo > 0)
			this->operacoesWorstFit.push_back(Operacao(1, tempo));
		break;
	default:
		break;
}

	if (tempo > 0)
		std::cout << "Processo removido em: " << tempo << " microseconds\n";
}

void MenuMemoria::MostraMemoria() {
#ifdef __linux__ 
	system("clear");
#else
	system("cls");
#endif

	std::cout << "\n\nMemoria FirstFit\n";
	std::cout << "\n----------------------\n";
	this->firstFit->Print();
	std::cout << "----------------------";

	std::cout << "\n\nMemoria BestFit\n";
	std::cout << "\n----------------------\n";
	this->bestFit->Print();
	std::cout << "----------------------";

	std::cout << "\n\nMemoria WorstFit\n";
	std::cout << "\n----------------------\n";
	this->worstFit->Print();
	std::cout << "----------------------\n";
}
