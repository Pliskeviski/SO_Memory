#pragma once

#include <string>

class Processo {
public:
	Processo(const char* nome, bool alocacao = false, double espacoMemoria = 0) : Nome((char*)nome), Alocacao(alocacao), EspacoMemoria(espacoMemoria) {}
	std::string Nome;
	bool Alocacao;
	double EspacoMemoria;
	
	bool operator==(const Processo& p) const {
		return this->Nome == p.Nome;
	}

	friend std::ostream& operator << (std::ostream &out, const Processo &p) {
		out << p.Nome;
		return out;
	}
};