#include "MenuMemoria.h"

#include <iomanip>
#include <fstream>

#include <chrono>
#include <thread>

void limpar() {
#ifdef __linux__ 
	system("clear");
#else
	system("cls");
#endif
}

MenuMemoria::MenuMemoria(std::string arquivo) {
	this->m_Algoritmos.push_back(new FirstFit());
	this->m_Algoritmos.push_back(new BestFit());
	this->m_Algoritmos.push_back(new WorstFit());

	for (auto alg : this->m_Algoritmos)
		alg->Init(arquivo.c_str());

	this->addItem("0 - Novo Processo", BIND_FN(MenuMemoria::NovoProcesso));
	this->addItem("1 - Remover Processo", BIND_FN(MenuMemoria::RemoverProcesso));
	this->addItem("2 - Mostra Memoria", BIND_FN(MenuMemoria::MostraMemoria));
	this->addItem("3 - Mostrar Estatistica", BIND_FN(MenuMemoria::MostrarEstatistica));
	this->addItem("4 - Expandir Memoria", BIND_FN(MenuMemoria::ExpandirMemoria));
	this->addItem("5 - Reduzir Memoria", BIND_FN(MenuMemoria::ReduzirMemoria));
	this->addItem("6 - Executa Arquivo", BIND_FN(MenuMemoria::ExecutaArquivo));
	this->addItem("7 - Exportar Resultados", BIND_FN(MenuMemoria::ExportarResultados));
	this->addItem("8 - Exportar Memoria", BIND_FN(MenuMemoria::ExportarMemoria));
	this->addItem("9 - Sair", BIND_FN(Menu::Sair));
}

MenuMemoria::~MenuMemoria() {
	// TODO: delete nos algorimos
}

void MenuMemoria::NovoProcesso(void* p) {

	std::string nome;
	unsigned int tamanho;
	std::string dinamica;
	unsigned int lista;
	Algoritmo* algoritmo = NULL;
	std::string somente_procura;

	if (p == NULL) {
		std::cin.get();

		std::cout << "Digite o nome do processo: \n";
		std::getline(std::cin, nome);

		std::cout << "Digite o tamanho do processo: \n";
		std::cin >> tamanho;

		algoritmo = this->RecuperaAlgoritmo();

		std::cin.get();

		std::cout << "Memoria dinamica? S|N \n";
		std::getline(std::cin, dinamica);
		
		std::cout << "Somente Procura? S|N\n";
		std::getline(std::cin, somente_procura);

		std::cout << "Digite a lista a ser utilizada: \n1-Lista simples\n2-Lista livre\n3-Lista livre ordenada\n";
		std::cin >> lista;
	}
	else {
		AdicionaProcesso* ap = (AdicionaProcesso*)p;
		nome = ap->processo.Nome;
		tamanho = ap->processo.EspacoMemoria;
		dinamica = ap->processo.Alocacao == true ? "S" : "N";
		algoritmo = this->RecuperaAlgoritmo(ap->algoritmo);
		lista = ap->lista;
		somente_procura = ap->somenteProcura == true ? "S" : "N";
	}

	Processo processo = Processo(nome.c_str(), (dinamica == "S"), tamanho);

	double tempo = algoritmo->Insere(&processo, (LISTA)lista, (somente_procura == "S"));
	
	if (tempo > 0) {
		algoritmo->AdicionaOperacao(Operacao(1, tempo, (LISTA)lista));
		std::cout << "Processo inserido em: " << tempo << " microseconds\n\n";
	}
}

void MenuMemoria::RemoverProcesso(void* p) {
	std::string nome;
	Algoritmo* algoritmo = NULL;

	if (p == NULL) {
		std::cin.get();

		std::cout << "Digite o nome do processo: \n";
		std::getline(std::cin, nome);
		
		algoritmo = this->RecuperaAlgoritmo();
	}
	else {
		RemoveProcesso* rp = (RemoveProcesso*)p;
		nome = rp->nome_processo;
		algoritmo = this->RecuperaAlgoritmo(rp->algoritmo);
	}

	double tempo = algoritmo->RemoveNome(nome.c_str());

	if (tempo > 0) {
		std::cout << "Processo removido em: " << tempo << " microseconds\n\n";
		algoritmo->AdicionaOperacao(Operacao(2, tempo));
	}
}

void MenuMemoria::MostraMemoria(void* p) {
	limpar();

	Algoritmo* algoritmo = this->RecuperaAlgoritmo();

	algoritmo->Print();

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::MostrarEstatistica(void* p) {
	
	Algoritmo* algoritmo = this->RecuperaAlgoritmo();
	
	this->ImprimeVetorEstatistica(algoritmo);

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::ExpandirMemoria(void* p) {
	limpar();

	Algoritmo* algoritmo = this->RecuperaAlgoritmo();

	algoritmo->Insere(NULL, LISTA::PRINCIPAL, true);

	if (p == NULL) {
		std::cout << "\nPressione enter para continuar...\n";
		std::cin.get();
		std::cin.get();
	}

	limpar();
}

void MenuMemoria::ReduzirMemoria(void* p) {
	limpar();

	Algoritmo* algoritmo = this->RecuperaAlgoritmo();

	limpar();

	int tamanho = 0;
	
	std::cout << "Digite o tamanho a ser removido: \n";
	std::cin >> tamanho;

	for (int i = 0; i < tamanho; i++) {
		if (algoritmo->Remove() == 0) {
			std::cout << "Memoria reduzida\n";
		}
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

	if (script != NULL) {
		std::cout << "\n";
		std::ifstream arquivo(script);

		int x, tamanho, alocacao, algoritmo, lista, somente_procura;
		char nome[12];

		Processo* p = NULL;
		AdicionaProcesso* ap = NULL;
		RemoveProcesso* rp = NULL;

		for (std::string line; std::getline(arquivo, line); ) {
			switch (line[0]) {
			case '0':
				sscanf(line.c_str(), "%d %s %d %d %d %d %d", &x, nome, &tamanho, &alocacao, &algoritmo, &lista, &somente_procura);
				p = new Processo(nome, alocacao, tamanho);
				ap = new AdicionaProcesso(*p, algoritmo, (LISTA)lista, somente_procura);

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

void MenuMemoria::ExportarResultados(void* p) {
	std::string nome_arquivo;

	if(p != NULL) 
		nome_arquivo = (char*)p;
	
	while (nome_arquivo.size() == 0) {
		std::cout << "Digite o nome do arquivo (sem extencao) \n";
		std::cin >> nome_arquivo;
	}

	nome_arquivo.append(".csv");

	std::ofstream arquivo;
	arquivo.open(nome_arquivo);

	for (int i = 1; i < this->m_Algoritmos.size() + 1; i++) {
		Algoritmo* alg = this->RecuperaAlgoritmo(i);

		for (Operacao op : alg->RecuperaOperacoes()) {
			std::string lista;
			std::string operacao;

			switch (op.lista) {
			case 1:
				lista = "Livres Ocupados";
				break;
			case 2:
				lista = "Livres";
				break;
			case 3:
				lista = "Livres Ordenados";
				break;
			default:
				lista = "?";
				break;
			}

			switch (op.operacao) {
			case 1:
				operacao = "Insercao";
				break;
			case 2:
				operacao = "Remocao";
				break;
			default:
				operacao = "?";
				break;
			}

			arquivo << alg->getName() << ";" << operacao << ";" << lista << ";" << op.tempo << "\n";
		}
	}
}

void MenuMemoria::ExportarMemoria(void* p) {
	for (int i = 1; i < this->m_Algoritmos.size(); i++) {
		Algoritmo* alg = this->RecuperaAlgoritmo(i);

		std::ofstream arquivo;
		arquivo.open("Resultado\\" + alg->getName() + "_result.csv");

		auto lista = alg->RecuperaLivresOcupadas();

		for (int i = 0; i < lista->GetSize(); i++) {
			EspacoMemoria* conteudo = (EspacoMemoria*)lista->get(i)->conteudo;
			auto node = conteudo->node;
			std::string nome = ((Processo*)node->conteudo == NULL ? "--" : ((Processo*)node->conteudo)->Nome);

			int tam = (conteudo->sequencia + 1);
			if (nome != "--") tam = 0;

			arquivo << nome << ", " << tam << "\n";
		}

	}
}

void MenuMemoria::ImprimeVetorEstatistica(Algoritmo* algoritmo) {
	auto vetor = algoritmo->RecuperaOperacoes();
	
	std::cout << std::setw(5) << std::right << "Estatisticas " << algoritmo->getName() << std::endl;

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
			lista = "Livres Ocupados";
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

Algoritmo* MenuMemoria::RecuperaAlgoritmo(int alg) {
	Algoritmo* alg_ = NULL;
	
	if (alg != -1) {
		alg--;

		if (!(alg < 0 || alg >= this->m_Algoritmos.size())) {
			alg_ = this->m_Algoritmos[alg];
		}
	}

	while (alg_ == NULL) {
		std::cout << "Digite o algoritmo a ser utilizado: \n";
	
		for (int i = 0; i < this->m_Algoritmos.size(); i++) {
			std::cout << i + 1 << "-" << this->m_Algoritmos[i]->getName() << "\n";
		}

		int opcao;
		std::cin >> opcao;
		opcao--;

		if (opcao < 0 || opcao >= this->m_Algoritmos.size()) {
			std::cout << "Opção inválida, tenta novamente.\n";
			std::cin.get();
		}
		else {
			alg_ = this->m_Algoritmos[opcao];
		}
	}
	return alg_;
}
