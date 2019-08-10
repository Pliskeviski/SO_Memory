#include <iostream>
#include <string>

#include "GerarArquivo/GerarArquivo.h"
#include "GerarScript/GerarScript.h"

#include "Helper/MenuMemoria.h"

int main(int argc, char *argv[]) {

	char* arquivo = "arquivo.txt";
	char* script  = "script.so";

	int tamanho_arquivo = 0;
	int tamanho_script = 0;

	bool executa_testes = false;

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

	if(tamanho_arquivo > 0) 
		GerarArquivo::NovoArquivo(arquivo, tamanho_arquivo); 
	
	if(tamanho_script > 0) 
		GerarScript::NovoScript(script, tamanho_script, 50);

	
	MenuMemoria* menu;
	
	if(executa_testes) {
		int quantidade_testes = 100;
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
	} else {
		menu = new MenuMemoria("processos.txt");
		while (1) menu->LeEvento();
		delete menu;
	}

	std::cin.get();
}