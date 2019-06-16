#include "GerarScript.h"

void GerarScript::NovoScript(const char* fileName, unsigned int qtd, unsigned int tam_max) {
	FILE* f = fopen(fileName, "w+");
	
	srand(time(NULL));

	for (int i = qtd; i >= 0; i--) {

        unsigned int op = rand() % 3;
        unsigned int nome = rand() % qtd + 0; // Gera um nome de processo aleatorio
        
        if(op == 1) {
		    fprintf(f, "1 P%d 1\n", nome);
		    fprintf(f, "1 P%d 2\n", nome);
		    fprintf(f, "1 P%d 3\n", nome);
        } else {
            unsigned int tam = rand() % tam_max + 1;

		    fprintf(f, "0 P%d %d 1 1 1 1\n", nome, tam); // FF - Livres Ocupados
		    fprintf(f, "0 P%d %d 1 1 2 1\n", nome, tam); // FF - Livres 
		    fprintf(f, "0 P%d %d 1 1 3 1\n", nome, tam); // FF - Livres Ordenados
            
            fprintf(f, "0 P%d %d 1 2 1 1\n", nome, tam); // BF - Livres Ocupados
		    fprintf(f, "0 P%d %d 1 2 2 1\n", nome, tam); // BF - Livres 
		    fprintf(f, "0 P%d %d 1 2 3 1\n", nome, tam); // BF - Livres Ordenados

            fprintf(f, "0 P%d %d 1 3 1 1\n", nome, tam); // WF - Livres Ocupados
		    fprintf(f, "0 P%d %d 1 3 2 1\n", nome, tam); // WF - Livres 
		    fprintf(f, "0 P%d %d 1 3 3 1\n", nome, tam); // WF - Livres Ordenados
        }
	}
	fclose(f);
}
