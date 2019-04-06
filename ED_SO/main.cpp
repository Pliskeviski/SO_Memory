#include <iostream>

#include "GerarArquivo/GerarArquivo.h"

#include "Memoria/Algoritmos/FirstFit.h"
#include "Memoria/Algoritmos/BestFit.h"
#include "Memoria/Algoritmos/WorstFit.h"

int main(int argc, char *argv[]) {
	GerarArquivo::NovoArquivo("processos.txt", 10);
	
	
	WorstFit* bestfit = new WorstFit();
	if (bestfit->Init("processos.txt") == -1) return -1;

	bestfit->Remove("P1");
	bestfit->Remove("P2");

	//worstfit->Remove("P5");

	bestfit->Remove("P7");
	bestfit->Remove("P8");
	bestfit->Remove("P9");

	bestfit->Insere(Processo("Teste", false, 100));

	bestfit->Print();

	std::cin.get();
}