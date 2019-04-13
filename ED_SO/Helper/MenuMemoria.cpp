#include "MenuMemoria.h"

#include <iomanip>

void limpar() {
#ifdef __linux__ 
	system("clear");
#else
	system("cls");
#endif
}

MenuMemoria::MenuMemoria(std::string arquivo) {
	this->firstFit = new FirstFit();
	this->bestFit = new BestFit();
	this->worstFit = new WorstFit();

	this->firstFit->Init(arquivo.c_str());
	this->bestFit->Init(arquivo.c_str());
	this->worstFit->Init(arquivo.c_str());

	this->addItem("0 - Novo Processo", BIND_FN(MenuMemoria::NovoProcesso));
	this->addItem("1 - Remover Processo", BIND_FN(MenuMemoria::RemoverProcesso));
	this->addItem("2 - Mostra Memoria", BIND_FN(MenuMemoria::MostraMemoria));
	this->addItem("3 - Mostrar Estatistica", BIND_FN(MenuMemoria::MostrarEstatistica));
	this->addItem("4 - Expandir Memoria", BIND_FN(MenuMemoria::ExpandirMemoria));
	this->addItem("5 - Reduzir Memoria", BIND_FN(MenuMemoria::ReduzirMemoria));
	this->addItem("6 - Sair", BIND_FN(Menu::Sair));
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
		tempo = this->firstFit->Insere(&processo);
		if (tempo > 0)
			this->operacoesFirstFit.push_back(Operacao(1, tempo));
		break;
	case 2:
		tempo = this->bestFit->Insere(&processo);
		if (tempo > 0)
			this->operacoesBestFit.push_back(Operacao(1, tempo));
		break;
	case 3:
		tempo = this->worstFit->Insere(&processo);
		if (tempo > 0)
			this->operacoesWorstFit.push_back(Operacao(1, tempo));
		break;
	default:
		break;
	}

	if (tempo > 0)
		std::cout << "Processo inserido em: " << tempo << " microseconds\n\n";
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
		tempo = this->firstFit->RemoveNome(nome.c_str());
		if (tempo > 0)
			this->operacoesFirstFit.push_back(Operacao(2, tempo));
		break;
	case 2:
		tempo = this->bestFit->RemoveNome(nome.c_str());
		if (tempo > 0)
			this->operacoesBestFit.push_back(Operacao(2, tempo));
		break;
	case 3:
		tempo = this->worstFit->RemoveNome(nome.c_str());
		if (tempo > 0)
			this->operacoesWorstFit.push_back(Operacao(2, tempo));
		break;
	default:
		break;
	}

	if (tempo > 0)
		std::cout << "Processo removido em: " << tempo << " microseconds\n\n";
}

void MenuMemoria::MostraMemoria() {
	limpar();

	unsigned int alg;
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
	std::cin >> alg;

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	limpar();

	switch (alg) {
	case 1:
		std::cout << std::setw(5) << std::right << "Memoria FirstFit" << std::endl;
		this->firstFit->Print();
		break;
	case 2:
		std::cout << std::setw(5) << std::right << "Memoria BestFit" << std::endl;
		this->bestFit->Print();
		break;
	case 3:
		std::cout << std::setw(5) << std::right << "Memoria WorstFit" << std::endl;
		this->worstFit->Print();
		break;
	default:
		break;
	}

	std::cout << "\nPressione enter para continuar...\n";
	std::cin.get();
	std::cin.get();

	limpar();
}

void MenuMemoria::MostrarEstatistica() {
	limpar();

	unsigned int alg;
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
	std::cin >> alg;

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	limpar();

	switch (alg) {
	case 1:
		std::cout << std::setw(5) << std::right << "Estatisticas FirstFit" << std::endl;
		this->ImprimeVetorEstatistica(this->operacoesFirstFit);
		break;
	case 2:
		std::cout << std::setw(5) << std::right << "Estatisticas BestFit" << std::endl;
		this->ImprimeVetorEstatistica(this->operacoesBestFit);
		break;
	case 3:
		std::cout << std::setw(5) << std::right << "Estatisticas WorstFit" << std::endl;
		this->ImprimeVetorEstatistica(this->operacoesWorstFit);
		break;
	default:
		break;
	}

	std::cout << "\nPressione enter para continuar...\n";
	std::cin.get();
	std::cin.get();

	limpar();
}

void MenuMemoria::ExpandirMemoria() {
	limpar();

	unsigned int alg;
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
	std::cin >> alg;

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	limpar();

	switch (alg) {
	case 1:
		this->firstFit->Insere(NULL, true);
		break;
	case 2:
		this->bestFit->Insere(NULL, true);
		break;
	case 3:
		this->worstFit->Insere(NULL, true);
		break;
	default:
		break;
	}

	std::cout << "\nPressione enter para continuar...\n";
	std::cin.get();
	std::cin.get();

	limpar();
}

void MenuMemoria::ReduzirMemoria() {
	limpar();

	unsigned int alg;
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
	std::cin >> alg;

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	limpar();

	switch (alg) {
	case 1:
		this->firstFit->Remove();
		break;
	case 2:
		this->bestFit->Remove();
		break;
	case 3:
		this->worstFit->Remove();
		break;
	default:
		break;
	}

	std::cout << "\nPressione enter para continuar...\n";
	std::cin.get();
	std::cin.get();

	limpar();
}

void MenuMemoria::ImprimeVetorEstatistica(std::vector<Operacao>& vetor) {
	if (vetor.size() == 0) {
		std::cout << "Nenhuma operacao realizada com esse algoritmo\n";
		return;
	}

	std::cout << std::setw(5) << std::right << "Operacao" << " - " << "Tempo" << std::endl;
	for (Operacao o : vetor) {
		std::string operacao;
		if (o.operacao == 1)
			operacao = "Insercao";
		else
			operacao = "Remocao";

		std::cout << std::setw(5) << std::right << operacao << " - " << o.tempo << std::endl;
	}
}
