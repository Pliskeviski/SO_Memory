#include "GerarArquivo.h"

void GerarArquivo::NovoArquivo(const char* fileName, unsigned int amount) {
	FILE* f = fopen(fileName, "w+");
	
	srand(time(NULL));

	for (int i = amount; i >= 0; i--) {

		unsigned int st = rand() % 500 + 1;
		unsigned int nd = rand() % 2 + 0;

		fprintf(f, "P%d %d %d\n", i, st, nd);
	}

	fclose(f);
}
