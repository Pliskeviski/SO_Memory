#include <iostream>

#include "GerarArquivo/GerarArquivo.h"

#include "Memoria/Algoritmos/FirstFit.h"
#include "Memoria/Algoritmos/BestFit.h"
#include "Memoria/Algoritmos/WorstFit.h"

int main(int argc, char *argv[]) {
	GerarArquivo::NovoArquivo("processos.txt", 10);
	
	/*FirstFit* firstFit = new FirstFit();
	firstFit->Init("processos.txt");
	
	firstFit->Remove("P5");

	firstFit->Insere(Processo("Teste", false, 100));
	
	firstFit->Remove("P6");
	firstFit->Remove("P1");

	firstFit->Print();*/

	/*BestFit* bestfit = new BestFit();
	if(bestfit->Init("processos.txt") == -1) return -1;

	bestfit->Remove("P1");
	bestfit->Remove("P2");
	bestfit->Remove("P3");
	bestfit->Remove("P5");
	bestfit->Remove("P6");

	bestfit->Insere(Processo("Teste", false, 100));

	bestfit->Print();*/
	
	WorstFit* worstfit = new WorstFit();
	if (worstfit->Init("processos.txt") == -1) return -1;

	worstfit->Remove("P1");
	worstfit->Remove("P2");
	worstfit->Remove("P3");
	worstfit->Remove("P5");
	worstfit->Remove("P6");

	worstfit->Insere(Processo("Teste", false, 100));

	worstfit->Print();

	std::cin.get();
}