#include "GerarArquivo.h"

#include <ctime>  
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

int _count = 0;
int get_random(int min, int max) {
	
	if (_count == 20) {
		std::chrono::milliseconds dura(200);
		std::this_thread::sleep_for(dura);
		srand(time(0));
		_count = 0;
	}

	int number = rand() % max + min;
	
	_count++;
	return number;
}

void GerarArquivo::NovoArquivo(const char* fileName, unsigned int amount) {
	FILE* f = fopen(fileName, "w+");

	for (int i = amount; i >= 0; i--) {

		unsigned int st = get_random(1, 10);

		unsigned int nd = get_random(0, 2);

		unsigned int nul = get_random(0, 7);

		if (nul != 1)
			fprintf(f, "P%d %d %d\n", i, st, nd);
		else
			fprintf(f, "-- %d %d\n", st, nd);
	}

	fclose(f);
}

void GerarArquivo::NovoArquivoTamMemoria(const char* fileName, unsigned int amount, unsigned int files, std::string prefix) {
	for (int g = 0; g < 3; g++) {
		if (g == 0) prefix = "50";
		if (g == 1) prefix = "ML";
		if (g == 2) prefix = "MO";

		for (int j = 0; j < files; j++) {
			int amt = amount;

			std::string nm("arquivo\\memoria\\memoria_principal_" + prefix + "_");
			nm.append(std::to_string(j));
			nm.append(".txt");

			FILE* f = fopen(nm.c_str(), "w+");

			int i = 0;
			int tam_ocp = 0;
			int tam_lvr = 0;

			for (; amt > 0; i++) {
				unsigned int st = get_random(1, 10);

				unsigned int nd = get_random(0, 2);

				unsigned int nul = get_random(0, 10);

				if (amt <= st)
					st = amt;

				amt -= st;

				if (g == 0) {
					if (nul >= 5) {
						tam_lvr += st;
						fprintf(f, "-- %d %d\n", st, nd);
					}
					else {
						tam_ocp += st;
						fprintf(f, "P%d %d %d\n", i, st, nd);
					}
				}
				else if (g == 1) {
					if (nul != 5) {
						tam_lvr += st;
						fprintf(f, "-- %d %d\n", st, nd);
					}
					else {
						tam_ocp += st;
						fprintf(f, "P%d %d %d\n", i, st, nd);
					}
				}
				else if (g == 2) {
					if (nul == 5) {
						tam_lvr += st;
						fprintf(f, "-- %d %d\n", st, nd);
					}
					else {
						tam_ocp += st;
						fprintf(f, "P%d %d %d\n", i, st, nd);
					}
				}
			}

			std::cout << nm << std::endl;
			printf("Tamanho ocupado: %d\n", tam_ocp);
			printf("Tamanho livre: %d\n", tam_lvr);
			printf("Tamanho total: %d\n", tam_ocp + tam_lvr);
			printf("Quantidade arquivos: %d", i);

			fclose(f);
		}
	}
}

