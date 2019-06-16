#include <iostream>

#include "GerarArquivo/GerarArquivo.h"
#include "GerarScript/GerarScript.h"

#include "Helper/MenuMemoria.h"

int main(int argc, char *argv[]) {
	GerarArquivo::NovoArquivo("processos.txt", 500); 
	GerarScript::NovoScript("script.so", 200, 50);

	MenuMemoria menu("processos.txt");

	while (1) menu.LeEvento();

	std::cin.get();
}