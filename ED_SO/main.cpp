#include <iostream>

#include "GerarArquivo/GerarArquivo.h"

#include "Memoria/Algoritmos/FirstFit.h"

int main(int argc, char *argv[]) {
	GerarArquivo::NovoArquivo("processos.txt", 10);
	
	FirstFit* firstFit = new FirstFit();
	firstFit->Init("processos.txt");
	
	std::cin.get();
}