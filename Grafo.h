/*
Denilson Aparecido Gonçalves Junior - 2176481
Thaynara Santos Ramos - 2126966

*/
#include <string>
#ifndef GRAFOS_H
#define GRAFOS_H
using namespace std;


class GrafoSimples{
public:
    GrafoSimples();
    ~GrafoSimples();

private:
    int** matrizDeAdjacencias;
    char *vertices;
    int numDeVertices;
    Vertice root;
    void Limpar(Vertice &raiz);
    void Inserir(Vertice &r, string &chave1, string &chave2, string &chave3, bool &found);
    void Imprimir(Vertice &r, int &Nodes, int &NoSonNodes);
    void ImprimirGrafo(Vertice &r, int spaces);
};
#endif
