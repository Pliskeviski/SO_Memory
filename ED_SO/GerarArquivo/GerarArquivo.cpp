#include "GerarArquivo.h"

#include <ctime>  
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

int get_random(int min, int max) {
	std::chrono::milliseconds dura(200);
    std::this_thread::sleep_for(dura);
	srand(time(0));
	int number = rand() % max + min;
	std::cout << number << std::endl;
	return number;
}

void GerarArquivo::NovoArquivo(const char* fileName, unsigned int amount) {
	FILE* f = fopen(fileName, "w+");
		
	for (int i = amount; i >= 0; i--) {

		unsigned int st = get_random(1, 10);
		
		unsigned int nd = get_random(0, 2);

		unsigned int nul = get_random(0, 7);

		if(nul != 1)
			fprintf(f, "P%d %d %d\n", i, st, nd);
		else
			fprintf(f, "-- %d %d\n", st, nd);
	}

	fclose(f);
}

