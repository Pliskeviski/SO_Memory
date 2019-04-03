#include <iostream>

#include "GerarArquivo/GerarArquivo.h"

#include "Memoria/Algoritmos/FirstFit.h"

int main(int argc, char *argv[]) {
	//GerarArquivo::NovoArquivo("processos.txt", 10);
	
	FirstFit* firstFit = new FirstFit();
	firstFit->Init("processos.txt");
	
	firstFit->Remove("P5");

	firstFit->Insere(Processo("Teste", false, 100));
	
	firstFit->Remove("P6");
	firstFit->Remove("P1");

	firstFit->Print();

	std::cin.get();
}