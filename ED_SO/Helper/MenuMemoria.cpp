#include "MenuMemoria.h"

#include <iomanip>
#include <fstream>

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
	this->addItem("6 - Executa Arquivo", BIND_FN(MenuMemoria::ExecutaArquivo));
	this->addItem("7 - Sair", BIND_FN(Menu::Sair));
}
void MenuMemoria::NovoProcesso(void* p) {

	std::string nome;
	unsigned int tamanho;
	std::string dinamica;
	unsigned int alg;
	unsigned int lista;

	if (p == NULL) {
		std::cin.get();

		std::cout << "Digite o nome do processo: \n";
		std::getline(std::cin, nome);

		std::cout << "Digite o tamanho do processo: \n";
		std::cin >> tamanho;

		std::cin.get();

		std::cout << "Memoria dinamica? S|N \n";
		std::getline(std::cin, dinamica);

		std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
		std::cin >> alg;

		std::cout << "Digite a lista a ser utilizada: \n1-Lista simples\n2-Lista livre\n3-Lista livre ordenada\n";
		std::cin >> lista;
	}
	else {
		AdicionaProcesso* ap = (AdicionaProcesso*)p;
		nome = ap->processo.Nome;
		tamanho = ap->processo.EspacoMemoria;
		dinamica = ap->processo.Alocacao == true ? "S" : "N";
		alg = ap->algoritmo;
		lista = ap->lista;

		//delete ap;
	}

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	Processo processo = Processo(nome.c_str(), (dinamica == "S"), tamanho);

	double tempo;

	switch (alg) {
	case 1:
		tempo = this->firstFit->Insere(&processo, (LISTA)lista);
		if (tempo > 0)
			this->operacoesFirstFit.push_back(Operacao(1, tempo, (LISTA)lista));
		break;
	case 2:
		tempo = this->bestFit->Insere(&processo, (LISTA)lista);
		if (tempo > 0)
			this->operacoesBestFit.push_back(Operacao(1, tempo, (LISTA)lista));
		break;
	case 3:
		tempo = this->worstFit->Insere(&processo, (LISTA)lista);
		if (tempo > 0)
			this->operacoesWorstFit.push_back(Operacao(1, tempo, (LISTA)lista));
		break;
	default:
		break;
	}

	if (tempo > 0)
		std::cout << "Processo inserido em: " << tempo << " microseconds\n\n";
}

void MenuMemoria::RemoverProcesso(void* p) {
	std::string nome;
	unsigned int alg;

	if (p == NULL) {
		std::cin.get();

		std::cout << "Digite o nome do processo: \n";
		std::getline(std::cin, nome);
		
		std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
		std::cin >> alg;
	}
	else {
		RemoveProcesso* rp = (RemoveProcesso*)p;
		nome = rp->nome_processo;
		alg = rp->algoritmo;

		//delete rp;
	}

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

void MenuMemoria::MostraMemoria(void* p) {
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

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::MostrarEstatistica(void* p) {
	limpar();

	unsigned int alg;
	
	std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit\n4-Todos\n";
	std::cin >> alg;

	if (alg < 1 || alg > 5) {
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
	case 4:
		std::cout << std::setw(5) << std::right << "Estatisticas FirstFit" << std::endl;
		this->ImprimeVetorEstatistica(this->operacoesFirstFit);
		std::cout << std::endl;
		
		std::cout << std::setw(5) << std::right << "Estatisticas BestFit" << std::endl;
		this->ImprimeVetorEstatistica(this->operacoesBestFit);
		std::cout << std::endl;

		std::cout << std::setw(5) << std::right << "Estatisticas WorstFit" << std::endl;
		this->ImprimeVetorEstatistica(this->operacoesWorstFit);
		std::cout << std::endl;
		break;
	}

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::ExpandirMemoria(void* p) {
	limpar();

	unsigned int alg;
	if (p == NULL) {
		std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
		std::cin >> alg;
	}
	else {
		alg = *(int*)p;
	}

	if (alg < 1 || alg > 4) {
		std::cout << "Algoritmo invalido.\n";
		return;
	}

	limpar();

	switch (alg) {
	case 1:
		this->firstFit->Insere(NULL, LISTA::PRINCIPAL, true);
		break;
	case 2:
		this->bestFit->Insere(NULL, LISTA::PRINCIPAL, true);
		break;
	case 3:
		this->worstFit->Insere(NULL, LISTA::PRINCIPAL, true);
		break;
	default:
		break;
	}

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::ReduzirMemoria(void* p) {
	limpar();

	unsigned int alg;
	if (p == NULL) {
		std::cout << "Digite o algoritmo a ser utilizado: \n1-First Fit\n2-BestFit\n3-WorstFit \n";
		std::cin >> alg;
	}
	else {
		alg = *(int*)p;
	}

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

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::ExecutaArquivo(void* p) {
	// Carrega comandos de um arquivo e executa todos

	const char* script = "script.so";

	/*
		Insercao:
		0 Nome Tamanho Alocacao Algoritmo Lista
		Ex.: 0 P10 340 1 1 1

		Remocao:
		1 Nome Algoritmo
		Ex.: 1 P5 1

		Expandir Memoria:
		4 Algoritmo
		Ex.: 4 1

		Reduzir Memoria:
		4 Algoritmo
		Ex.: 5 1
	*/

	if (script != NULL) {
		std::cout << "\n";
		std::ifstream arquivo(script);

		int x, tamanho, alocacao, algoritmo, lista;
		char nome[12];

		Processo* p = NULL;
		AdicionaProcesso* ap = NULL;
		RemoveProcesso* rp = NULL;

		for (std::string line; std::getline(arquivo, line); ) {
			switch (line[0]) {
			case '0':
				sscanf(line.c_str(), "%d %s %d %d %d %d", &x, nome, &tamanho, &alocacao, &algoritmo, &lista);
				p = new Processo(nome, alocacao, tamanho);
				ap = new AdicionaProcesso(*p, algoritmo, (LISTA)lista);
				this->NovoProcesso((void*)ap);
				delete p;
				delete ap;
				break;
			case '1':
				sscanf(line.c_str(), "%d %s %d", &x, nome, &algoritmo);
				rp = new RemoveProcesso(nome, algoritmo);
				this->RemoverProcesso((void*)rp);
				delete rp;
				break;
			case '4':
				sscanf(line.c_str(), "%d %d", &x, &algoritmo);
				this->ExpandirMemoria((void*)&algoritmo);
				break;
			case '5':
				sscanf(line.c_str(), "%d %d", &x, &algoritmo);
				this->ReduzirMemoria((void*)&algoritmo);
				break;
			}

		}
	}

}

void MenuMemoria::ImprimeVetorEstatistica(std::vector<Operacao>& vetor) {
	if (vetor.size() == 0) {
		std::cout << "Nenhuma operacao realizada com esse algoritmo\n";
		return;
	}

	std::cout << std::setw(5) << std::right << "Operacao"  << " - " << "Tempo" << " - " << "Lista" << std::endl;
	for (Operacao o : vetor) {
		std::string operacao, lista;
		if (o.operacao == 1) 
			operacao = "Insercao";
		else
			operacao = "Remocao ";
		
		switch (o.lista) {
		case LISTA::NOLISTA:
			lista = "";
			break;
		case LISTA::PRINCIPAL:
			lista = "Principal";
			break;
		case LISTA::LIVRE:
			lista = "Livre";
			break;
		case LISTA::LIVREORDENADA:
			lista = "Livre ordenada";
			break;
		}

		std::cout << std::setw(5) << std::right << operacao << " - " << std::setw(5) << o.tempo << " - " << std::setw(5) << lista << std::endl;

	}
}
