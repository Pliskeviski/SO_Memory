#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

class GerarArquivo {
public:
	static void NovoArquivo(const char* fileName, unsigned int amount);
	static void NovoArquivoTamMemoria(const char* fileName, unsigned int amount, unsigned int files = 1, std::string prefix = "");
};