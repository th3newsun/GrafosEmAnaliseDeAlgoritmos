/*
Denilson Aparecido Gonçalves Junior - 2176481
Thaynara Santos Ramos - 2126966

*/
#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

GrafoSimples::GrafoSimples(){
    numDeVertices = 0;
}
GrafoSimples::~GrafoSimples(){
}
void GrafoSimples::Ler(string arquivo){
    ifstream entrada(arquivo, ios::in);
    if(entrada.is_open()){
        Inserir(entrada);
        entrada.close();
    }
    else{
        cout << "\nO Arquivo nao pode ser aberto";
        abort();
    }
}
void GrafoSimples::Inserir(ifstream &entrada){
    string linha, vertice1, vertice2;
    bool existeNoVetor;
    while(getline(entrada, linha)) {
        stringstream ss(linha);
        getline(ss, vertice1, ';');
        getline(ss, vertice2, ';');
        // Verifica se o vertice1 já existe no vetor
        existeNoVetor = false;
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice1[0]){
                existeNoVetor = true;
                break;
            }
        }
        if(!existeNoVetor){
            vertices[numDeVertices].indice = vertice1;
            numDeVertices++;
        }
        // Verifica se o vertice2 já existe no vetor
        existeNoVetor = false;
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice2[0]){
                existeNoVetor = true;
                break;
            }
        }
        if(!existeNoVetor){
            vertices[numDeVertices].indice = vertice2;
            numDeVertices++;
        }
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice1[0]){
                Listar(vertice2, i);
            }
            if(vertices[i].indice[0] == vertice2[0]){
                Listar(vertice1, i);
            }
        }
    }
}
void GrafoSimples::Listar(string indiceDoVertice, int i){
    Vertice* novo = new Vertice;
    novo->indice = indiceDoVertice;
    novo->aresta = NULL;
    if (vertices[i].aresta == NULL) {
        vertices[i].aresta = novo;
    }
    else {
        novo->aresta = vertices[i].aresta;
        vertices[i].aresta = novo;
    }
}
void GrafoSimples::ImprimirLista(){
    for(int i = 0; i < numDeVertices; i++){
        cout << vertices[i].indice;
        if(vertices[i].aresta != NULL){
            cout << " -> ";
            ImprimirLista(vertices[i].aresta);
        }
        cout << endl;
    }
}
void GrafoSimples::ImprimirLista(Vertice *vertice){
    if(vertice->aresta == NULL){
        cout << vertice->indice << "\n";
        return;
    }
    else{
        cout << vertice->indice << " -> ";
        ImprimirLista(vertice->aresta);
    }
}



Digrafo::Digrafo(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            matrizDeAdjacencias[i][j] = 0;
        }
    }
    numDeVertices = 0;
}
Digrafo::~Digrafo(){
}
void Digrafo::Ler(string arquivo){
    ifstream entrada(arquivo, ios::in);
    if(entrada.is_open()){
        Inserir(entrada);
        entrada.close();
    }
    else{
        cout << "\nO Arquivo nao pode ser aberto";
        abort();
    }
}
void Digrafo::Inserir(ifstream &entrada){
    string linha, vertice1, vertice2;
    bool existeNoVetor;
    while(getline(entrada, linha)) {
        stringstream ss(linha);
        getline(ss, vertice1, ';');
        getline(ss, vertice2, ';');
        // Verifica se o vertice1 já existe no vetor
        existeNoVetor = false;
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice1[0]){
                existeNoVetor = true;
                break;
            }
        }
        if(!existeNoVetor){
            vertices[numDeVertices].indice = vertice1;
            numDeVertices++;
        }
        // Verifica se o vertice2 já existe no vetor
        existeNoVetor = false;
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice2[0]){
                existeNoVetor = true;
                break;
            }
        }
        if(!existeNoVetor){
            vertices[numDeVertices].indice = vertice2;
            numDeVertices++;
        }
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice1[0])
                Listar(vertice2, i);
            }
        }
    }
void Digrafo::Listar(string indiceDoVertice, int i){
    Vertice* novo = new Vertice;
    novo->indice = indiceDoVertice;
    novo->aresta = NULL;
    for(int j = 0; j < 8; j++){
            if(vertices[j].indice == indiceDoVertice){
                matrizDeAdjacencias[i][j] = 1;
            }
        }
    if (vertices[i].aresta == NULL) {
        vertices[i].aresta = novo;
    }
    else {
        novo->aresta = vertices[i].aresta;
        vertices[i].aresta = novo;
    }
}
void Digrafo::ImprimirLista(){
    for(int i = 0; i < numDeVertices; i++){
        cout << vertices[i].indice;
        if(vertices[i].aresta != NULL){
            cout << " -> ";
            ImprimirLista(vertices[i].aresta);
        }
        cout << endl;
    }
}
void Digrafo::ImprimirLista(Vertice *vertice){
    if(vertice->aresta == NULL){
        cout << vertice->indice << "\n";
        return;
    }
    else{
        cout << vertice->indice << " -> ";
        ImprimirLista(vertice->aresta);
    }
}
void Digrafo::ImprimirMatriz(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j % 8 == 0)
                cout << endl;
            cout << matrizDeAdjacencias[i][j] << " ";
        }
    }
}


GrafoPonderado::GrafoPonderado(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            matrizDeAdjacencias[i][j] = "0";
        }
    }
    numDeVertices = 0;
}
GrafoPonderado::~GrafoPonderado(){
}
void GrafoPonderado::Ler(string arquivo){
    ifstream entrada(arquivo, ios::in);
    if(entrada.is_open()){
        Inserir(entrada);
        entrada.close();
    }
    else{
        cout << "\nO Arquivo nao pode ser aberto";
        abort();
    }
}
void GrafoPonderado::Inserir(ifstream &entrada){
    string linha, vertice1, vertice2, peso;
    bool existeNoVetor;
    while(getline(entrada, linha)) {
        stringstream ss(linha);
        getline(ss, vertice1, ';');
        getline(ss, vertice2, ';');
        getline(ss, peso, ';');
        // Verifica se o vertice1 já existe no vetor*
        existeNoVetor = false;
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice1[0]){
                existeNoVetor = true;
                break;
            }
        }
        if(!existeNoVetor){
            vertices[numDeVertices].indice = vertice1;
            numDeVertices++;
        }
        // Verifica se o vertice2 já existe no vetor
        existeNoVetor = false;
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice2[0]){
                existeNoVetor = true;
                break;
            }
        }
        if(!existeNoVetor){
            vertices[numDeVertices].indice = vertice2;
            numDeVertices++;
        }
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice[0] == vertice1[0]){
                Listar(vertice2, i, peso);
            }
            if(vertices[i].indice[0] == vertice2[0]){
                Listar(vertice1, i, peso);
            }
        }
    }
}
void GrafoPonderado::Listar(string indiceDoVertice, int i, string peso){
    Vertice* novo = new Vertice;
    novo->indice = indiceDoVertice;
    novo->aresta = NULL;
    novo->peso = peso;
    for(int j = 0; j < 8; j++){
            if(vertices[j].indice == indiceDoVertice){
                matrizDeAdjacencias[i][j] = peso;
            }
        }
    if (vertices[i].aresta == NULL) {
        vertices[i].aresta = novo;
    }
    else {
        novo->aresta = vertices[i].aresta;
        vertices[i].aresta = novo;
    }
}
void GrafoPonderado::ImprimirLista(){
    for(int i = 0; i < numDeVertices; i++){
        cout << vertices[i].indice;
        if(vertices[i].aresta != NULL){
            cout << " -> ";
            ImprimirLista(vertices[i].aresta);
        }
        cout << endl;
    }
}
void GrafoPonderado::ImprimirLista(Vertice *vertice){
    if(vertice->aresta == NULL){
        cout << vertice->indice << "\n";
        return;
    }
    else{
        cout << vertice->indice << " -> ";
        ImprimirLista(vertice->aresta);
    }
}
void GrafoPonderado::ImprimirMatriz(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(j % 7 == 0)
                cout << endl;
            if(matrizDeAdjacencias[i][j].length() == 1)
                cout << " ";
            cout << matrizDeAdjacencias[i][j] << " ";
        }
    }
}


