#pragma once

#include <iostream>
#include <chrono>

#include <time.h>

class Meditor {
public:
	Meditor() {
		this->start = std::chrono::steady_clock::now(); // Inicia o cronometro
	}

	long long Fim() {
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::steady_clock::now() - start).count(); // Termina e calcula o tempo gasto
		return duration;
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> start;
};