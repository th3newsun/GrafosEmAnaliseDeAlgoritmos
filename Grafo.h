/*
Denilson Aparecido Gonçalves Junior - 2176481
Thaynara Santos Ramos - 2126966

*/
#include <string>
#include <fstream>
#ifndef GRAFOS_H
#define GRAFOS_H
using namespace std;


class GrafoSimples{
public:
    GrafoSimples();
    ~GrafoSimples();
    void Ler(string arquivo);
    void ImprimirLista();
    void ImprimirVetor();
private:
    struct Vertice{
        string indice;
        Vertice *aresta = NULL;
    };
    Vertice vertices[16];
    int numDeVertices;
    void Inserir(ifstream &entrada);
    void Listar(string indiceDoVertice, int i);
    void ImprimirLista(Vertice *vertice);
};

class Digrafo{
public:
    Digrafo();
    ~Digrafo();
    void Ler(string arquivo);
    void ImprimirLista();
    void ImprimirVetor();
    void ImprimirMatriz();
private:
    struct Vertice{
        string indice;
        Vertice *aresta = NULL;
    };
    Vertice vertices[16];
    int matrizDeAdjacencias[8][8];
    int numDeVertices;
    void Inserir(ifstream &entrada);
    void Listar(string indiceDoVertice, int i);
    void ImprimirLista(Vertice *vertice);
};

class GrafoPonderado{
public:
    GrafoPonderado();
    ~GrafoPonderado();
    void Ler(string arquivo);
    void ImprimirLista();
    void ImprimirMatriz();

private:
    struct Vertice{
        string indice;
        Vertice *aresta = NULL;
        string peso = "0";
    };
    Vertice vertices[7];
    int numDeVertices = 7;
    string matrizDeAdjacencias[7][7];
    void Inserir(ifstream &entrada);
    void Listar(string indiceDoVertice, int i, string peso);
    void ImprimirLista(Vertice *vertice);
};

#endif
