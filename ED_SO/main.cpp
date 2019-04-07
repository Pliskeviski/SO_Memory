#include <iostream>

#include "GerarArquivo/GerarArquivo.h"

#include "Helper/MenuMemoria.h"

int main(int argc, char *argv[]) {
	GerarArquivo::NovoArquivo("processos.txt", 10);
	
	MenuMemoria menu("processos.txt");

	while (1) menu.LeEvento();

	std::cin.get();
}