#include <iostream>
#include <string>

#include <filesystem>

#include "GerarArquivo/GerarArquivo.h"
#include "GerarScript/GerarScript.h"

#include "Helper/MenuMemoria.h"

int main(int argc, char *argv[]) {

	const char* arquivo = "arquivo\\memoria_principal_50_0.txt";
	const char* script  = "script.so";

	int tamanho_arquivo = 0; // 200;
	int tamanho_script = 0; // 100;

	int tamanho_maximo = 0; // 2000;

	bool executa_testes = false;
	bool executa_testes2 = true;

	for (int i = 0; i < argc; i++)
	{
		if(std::string(argv[i]) == "-r")
			executa_testes = true;

		if (std::string(argv[i]) == "-l") {
			arquivo = argv[i + 1];
			if(std::string(argv[i + 2]) != " " && std::string(argv[i + 2]) != "-") {
				tamanho_arquivo = atoi(argv[i + 2]);
			}
		} 
		
		if (std::string(argv[i]) == "-s") {
			script = argv[i + 1];
			if(std::string(argv[i + 2]) != " " && std::string(argv[i + 2]) != "-") {
				tamanho_script = atoi(argv[i + 2]);
			}
		}
	}

	std::cin.get();

	if(tamanho_arquivo > 0) 
		GerarArquivo::NovoArquivo(arquivo, tamanho_arquivo); 
	
	if(tamanho_script > 0) 
		GerarScript::NovoScript(script, tamanho_script, 10);

	if (tamanho_maximo > 0) {
		GerarArquivo::NovoArquivoTamMemoria(arquivo, tamanho_maximo, 5, "50");
	}


	MenuMemoria* menu;
	
	if(executa_testes) {
		int quantidade_testes = 1;
		int quantidade_processos = 200;

		for(int i = 1; i <= quantidade_testes; i++) {
			std::string nome_arquivo = "./resultados/arquivo" + std::to_string(i);
			std::string arquivo_texto = "./resultados/arquivo" + std::to_string(i);
			arquivo_texto.append(".txt");

			GerarArquivo::NovoArquivo(nome_arquivo.c_str(), quantidade_processos);

			menu = new MenuMemoria(nome_arquivo);
			menu->getItemMenu(6).funcao((void*)NULL);			
			menu->getItemMenu(7).funcao((void*)nome_arquivo.c_str());			
			delete menu;
		}
	}
	else if (executa_testes2) {
		std::string path = "arquivo\\memoria";
		
		for (const auto & entry : std::filesystem::directory_iterator(path)) {
			if (!entry.exists()) continue;
			
			std::string nome_arquivo = entry.path().string();
			
			std::cout << nome_arquivo << std::endl;
			menu = new MenuMemoria(nome_arquivo);

			nome_arquivo = nome_arquivo.substr(nome_arquivo.find_last_of('\\') + 1);
			nome_arquivo.insert(0, "arquivo\\resultados\\");
			menu->getItemMenu(6).funcao((void*)NULL);
			menu->getItemMenu(7).funcao((void*)nome_arquivo.c_str());
			menu->getItemMenu(8).funcao((void*)nome_arquivo.c_str());
			delete menu;
		}
	}
	else {
		menu = new MenuMemoria("arquivo.txt");
		while (1) menu->LeEvento();
		delete menu;
	}

	std::cout << "fim\n";

	std::cin.get();
}