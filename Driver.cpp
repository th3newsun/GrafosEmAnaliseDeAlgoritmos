/*
Denilson Aparecido Gonçalves Junior - 2176481
Thaynara Santos Ramos - 2126966

*/
#include "Grafo.h"
#include <iostream>
#include <string>

int main(){
    GrafoSimples Grafo1;
    Grafo1.Ler("bin/Debug/g1.txt");
    Digrafo Grafo2;
    Grafo2.Ler("bin/Debug/g2.txt");
    GrafoPonderado Grafo3;
    Grafo3.Ler("bin/Debug/g3.txt");
    Grafo3.ImprimirMatriz();


    return 0;
}
