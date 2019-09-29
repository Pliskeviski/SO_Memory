#pragma once

#include <string>

class Processo {
public:
	Processo(const char* nome, bool alocacao = false, unsigned int espacoMemoria = 0) : Nome((char*)nome), Alocacao(alocacao), EspacoMemoria(espacoMemoria), _Inserido(false) {}
	std::string Nome;
	bool Alocacao;
	unsigned int EspacoMemoria;
	
	bool operator==(const Processo& p) const {
		return this->Nome == p.Nome;
	}

	friend std::ostream& operator << (std::ostream &out, const Processo &p) {
		out << p.Nome;
		return out;
	}

	bool _Inserido;
};