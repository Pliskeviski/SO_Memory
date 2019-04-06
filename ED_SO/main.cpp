#include <iostream>

#include "GerarArquivo/GerarArquivo.h"

#include "Memoria/Algoritmos/FirstFit.h"
#include "Memoria/Algoritmos/BestFit.h"
#include "Memoria/Algoritmos/WorstFit.h"

int main(int argc, char *argv[]) {
	GerarArquivo::NovoArquivo("processos.txt", 10);
	
	
	WorstFit* worstFit = new WorstFit();
	if (worstFit->Init("processos.txt") == -1) return -1;

	worstFit->Remove("P1");
	worstFit->Remove("P2");

	//worstfit->Remove("P5");

	worstFit->Remove("P7");
	worstFit->Remove("P8");
	worstFit->Remove("P9");

	worstFit->Insere(Processo("Teste", false, 100));

	worstFit->Insere(Processo("Teste1", false, 100));

	worstFit->Insere(Processo("Teste2", false, 100));

	worstFit->Print();

	std::cin.get();
}