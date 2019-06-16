rm ./a.out
nice -n -18 g++ main.cpp GerarArquivo/GerarArquivo.cpp GerarScript/GerarScript.cpp Helper/MenuMemoria.cpp Memoria/Algoritmo.cpp Memoria/Algoritmos/BestFit.cpp Memoria/Algoritmos/FirstFit.cpp Memoria/Algoritmos/WorstFit.cpp Memoria/Algoritmos/QuickFit.cpp -std=c++14 -w
./a.out