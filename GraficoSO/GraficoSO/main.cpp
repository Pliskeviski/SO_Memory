#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>

#include "bmp.h"

struct Operacao {
	int operacao; // Somente inserção
	long tempo; 
	int lista; // 1 Simples, 2 Livre, 3 Livre Ordenada
	int algoritmo; // 1 FF; 2 BF 3; WF
};

struct Cor {
	int r;
	int g;
	int b;
};

std::vector<int> MelhoresTempos;
std::vector<std::vector<int>> Tempos;

int melhorTempo = -1;
int piorTempo = 0;
int width = 300;
int height = 500;
int maior = 0;

void paintPixel(BYTE* buf, int x, int y, Cor color) {
	int c = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (x == i && y == j) {
				buf[c + 0] = (BYTE)color.b; // b
				buf[c + 1] = (BYTE)color.g; // g
				buf[c + 2] = (BYTE)color.r; // r
			}
			c += 3;
		}
	}
}

double normalize(double value, double a, double b) {
	return ((int)(((double)value / b) * a));
}

int normalizeToPos(int value, int width) {
	return ((int)(((double)value / maior) * width));
}

double Interpolate(double d1, double d2, double fraction) {
	return d1 + (d2 - d1) * fraction;
}

Cor Interpolate(Cor color1, Cor color2, double fraction) {
	double r = Interpolate(color1.r, color2.r, fraction);
	double g = Interpolate(color1.g, color2.g, fraction);
	double b = Interpolate(color1.b, color2.b, fraction);
	Cor c;
	c.r = (int)(std::round(r));
	c.g = (int)(std::round(g));
	c.b = (int)(std::round(b));
	return c;
}

void CreateBaseImage(BYTE* buf, int width, int height) {
	std::cout << "Creating base image\n";
	
	int c = 0;

	Cor corTopo;
	corTopo.r = 50;
	corTopo.g = 50;
	corTopo.b = 255;

	Cor corBaixo;
	corBaixo.r = 255;
	corBaixo.g = 255;
	corBaixo.b = 255;

	for (int i = 0; i < height; i++) {
		double a = (double)((double)i / (double)height);

		Cor colorr = Interpolate(corBaixo, corTopo, a);
		
		for (int j = 0; j < width; j++) {
			paintPixel(buf, i, j, colorr);
		}
	}
}


std::vector<std::vector<unsigned int>> LoadMemory() {

	std::vector<std::vector<unsigned int>> t;

	for (int i = 1; i <= 100; i++) {
		std::vector<unsigned int> buracos; // salva a posicao do buraco

		std::string nome_arquivo = "./resultados/arquivo";
		nome_arquivo.append(std::to_string(i));

		std::ifstream memoria(nome_arquivo);

		if (!memoria.is_open()) break;

		int tamanho;
		int dummy;
		char nome[5];

		int bytes = 0;

		for (std::string line; std::getline(memoria, line); ) {
			sscanf(line.c_str(), "%s %d %d", nome, &tamanho, &dummy);
			
			if (nome[0] == '-') {
				buracos.push_back(bytes);
			}

			bytes += tamanho;
		}

		if (buracos.size() > maior) {
			maior = buracos.size();
		}

		//std::cout << buracos.size() << std::endl;

		t.push_back(buracos);
	}

	return t;
}

// Melhores

// 1 = FF + LivresOcupados
// 2 = FF + Livres
// 3 = FF + LivresOrdenados

// 4 = BF + LivresOcupados
// 5 = BF + Livres
// 6 = BF + LivresOrdenados

// 7 = WF + LivresOcupados
// 8 = WF + Livres
// 9 = WF + LivresOrdenados

int CompararAlg(std::vector<Operacao>& operacoes) {
	const int d = 9;
	int tempos[d] = { 0 };

	for (Operacao o : operacoes) {
		if (o.algoritmo == 1) {
			switch (o.lista) {
			case 1:
				tempos[0] += o.tempo;
				break;
			case 2:
				tempos[1] += o.tempo;
				break;
			case 3:
				tempos[2] += o.tempo;
				break;
			default:
				break;
			}
			continue;
		}

		if(o.algoritmo == 2) {
			switch (o.lista) {
			case 1:
				tempos[3] += o.tempo;
				break;
			case 2:
				tempos[4] += o.tempo;
				break;
			case 3:
				tempos[5] += o.tempo;
				break;
			default:
				break;
			}
			continue;
		}

		if(o.algoritmo == 3) {
			switch (o.lista) {
			case 1:
				tempos[6] += o.tempo;
				break;
			case 2:
				tempos[7] += o.tempo;
				break;
			case 3:
				tempos[8] += o.tempo;
				break;
			default:
				break;
			}
			continue;
		}

	}

	int melhorTempo = 0;
	for (int i = 0; i < d; i++) {
		if (tempos[i] < tempos[melhorTempo]) {
			melhorTempo = i;
		}
	}

	return melhorTempo;
}

void CompararAlg2(std::vector<Operacao>& operacoes) {
	

	std::vector<int> tempos;
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	tempos.push_back(0);
	for (Operacao o : operacoes) {

		if (o.algoritmo == 1) {
			switch (o.lista) {
			case 1:
				tempos[0] += o.tempo;
				break;
			case 2:
				tempos[1] += o.tempo;
				break;
			case 3:
				tempos[2] += o.tempo;
				break;
			default:
				break;
			}
			continue;
		}

		if (o.algoritmo == 2) {
			switch (o.lista) {
			case 1:
				tempos[3] += o.tempo;
				break;
			case 2:
				tempos[4] += o.tempo;
				break;
			case 3:
				tempos[5] += o.tempo;
				break;
			default:
				break;
			}
			continue;
		}

		if (o.algoritmo == 3) {
			switch (o.lista) {
			case 1:
				tempos[6] += o.tempo;
				break;
			case 2:
				tempos[7] += o.tempo;
				break;
			case 3:
				tempos[8] += o.tempo;
				break;
			default:
				break;
			}
			continue;
		}
	}
	
	for (int t : tempos) {
		if (t < melhorTempo || melhorTempo == -1) {
			melhorTempo = t;
		}
		if (t > piorTempo) {
			piorTempo = t;
		}
	}

	Tempos.push_back(tempos);
}

std::vector<std::string> csv_string(const char* ss) {
	std::vector<std::string> rett;

	std::istringstream f(ss);
	std::string s;
	while (std::getline(f, s, ';')) {
		rett.push_back(s);
	}

	return rett;
}

int LoadResults() {

	for (int i = 1; i <= 100; i++) {
		std::vector<Operacao> t;
		
		std::string nome_arquivo = "./resultados/arquivo";
		nome_arquivo.append(std::to_string(i));
		nome_arquivo.append(".csv");

		std::ifstream memoria(nome_arquivo);
		if (!memoria.is_open()) break;

		char string[100];

		int bytes = 0;

		for (std::string line; std::getline(memoria, line); ) {

			auto strings = csv_string(line.c_str());

			std::string nome = strings[0];
			std::string operacao = strings[1];
			std::string lista = strings[2];
			int tempo = std::atoi(strings[3].c_str());

			Operacao op;
			op.operacao = 1;
			op.tempo = tempo;

			if (nome == "FirstFit") {
				op.algoritmo = 1;
			}
			else if (nome == "BestFit") {
				op.algoritmo = 2;
			}
			else if (nome == "WorstFit") {
				op.algoritmo = 3;
			}

			if (lista == "Livres Ocupados") {
				op.lista = 1;
			}
			else if (lista == "Livres") {
				op.lista = 2;
			}
			else if (lista == "Livres Ordenados") {
				op.lista = 3;
			}

			t.push_back(op);
		}

		MelhoresTempos.push_back(CompararAlg(t));
		CompararAlg2(t);
	}

	return 0;
}

void paintCircle(BYTE* buf, int x_, int y_, Cor c) {
	float radius = 2.f;

	for (int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if (x*x + y * y <= radius * radius)
				paintPixel(buf, x_ + x, y_ + y, c);
}

int main() {

	BYTE* buf = new BYTE[width * 3 * height];
	
	CreateBaseImage(buf, width, height);

	auto buracos = LoadMemory();
	LoadResults();
	
	int cont = 0;
	
	for (int i = 0; i < buracos.size(); i++) {
	
		int pos = normalizeToPos(buracos[i].size(), height + 10);
	
		Cor red = {
			255, 0, 0
		};
	
		Cor green = {
			0, 255, 0
		};
	
		for (int j = 0; j < Tempos.size(); j++) {
			for (int g = 0; g < Tempos[j].size(); g++) {
				double interp = (double)((-Interpolate((double)(piorTempo / 100), (double)(melhorTempo / 100), (double)(Tempos[j][g] / 100))) / 100);
				Cor c = Interpolate(green, red, interp);
				
				paintCircle(buf, pos - 30, 20 + (g * 20), c);
			}
		}
		
		cont++;
		std::cout << "Done " << cont << "\n";
	}

	SaveBitmapToFile((BYTE*)buf,
		width,
		height,
		24,
		0,
		"image.bmp");


	delete[] buf;
	return 0;
}


