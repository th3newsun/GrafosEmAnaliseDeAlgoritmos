/*
Denilson Aparecido Gonçalves Junior - 2176481
Thaynara Santos Ramos - 2126966
Fernando Peres Borin - 2125219
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

    //Exercicio 1
    cout << "#################################### Exercicio 1 \n";
    Grafo1.ImprimirLista();
    cout << endl << endl;
    Grafo2.ImprimirLista();
    cout << endl << endl;
    Grafo3.ImprimirLista();

    //Exercicio 2
    cout << "\n#################################### Exercicio 2 \n";
    Grafo1.BuscaEmLargura("b");

    //Exercicio 3
    cout << "\n#################################### Exercicio 3 \n";
    Grafo2.BuscaEmProfundidade("a");

    return 0;
}
