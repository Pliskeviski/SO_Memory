#pragma once

#include <string>

class Processo {
public:
	Processo(const char* nome, bool alocacao, double espacoMemoria) : Nome((char*)nome), Alocacao(alocacao), EspacoMemoria(espacoMemoria) {}
	std::string Nome;
	bool Alocacao;
	double EspacoMemoria;
	
	bool operator==(const Processo& p) const {
		return this->Nome == p.Nome;
	}
};