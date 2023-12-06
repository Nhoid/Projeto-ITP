#include "utils.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

void limparTela() { //Preprocessamento que limpa a tela
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void esperarTempo(int tempo){ //Preprocessamento que espera um tempo
    #ifdef _WIN32
    Sleep(tempo * 1000);  // Pausa a execução por 5000 milissegundos (5 segundos)
    #else
    sleep(tempo);     // Pausa a execução por 5 segundos
    #endif
}
