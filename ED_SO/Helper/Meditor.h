#pragma once

#include <iostream>
#include <chrono>

#include <time.h>

class Meditor {
public:
	Meditor() {
		//this->start = std::chrono::steady_clock::now(); // Inicia o cronometro
		this->start = clock();
	}

	long long Fim() {
		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>
		//	(std::chrono::steady_clock::now() - start).count(); // Termina e calcula o tempo gasto
		//return duration;

		clock_t end = clock();
		return ((double)(end - this->start)) / CLOCKS_PER_SEC;
	}

private:
	//std::chrono::time_point<std::chrono::steady_clock> start;
	clock_t start;
};