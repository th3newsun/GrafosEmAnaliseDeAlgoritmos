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
    raiz = NULL;
    GrafoSimples::Vertices[i] = {};
}
GrafoSimples::~GrafoSimples(){
    Limpar(raiz);
}
void GrafoSimples::Limpar(Vertice &raiz){
    if(raiz == NULL)
        return;
    if(raiz->LeftNode != NULL)
        Clear(r->LeftNode);
    if(raiz->RightNode != NULL)
        Clear(r->RightNode);
    TreePointer q = r;
    delete q;
    return;
}
void GrafoSimples::Insert(){
    ifstream arquivo("g1.txt", ios::in);
    if(arquivo.is_open()){
        string linha, vertice, aresta;
        while(getline(arquivo, linha)){
            stringstream Entrada (linha);
            Entrada >> vertice >> aresta;
            for(int i = 0; i < Vertices.length(); i++){
                if(Vertices[i] == vertice)
                Vertices[i] = vertice;
            }
        arquivo.close();
    }
    else{
        cout << "\nO Arquivo nao pode ser aberto";
        abort();
    }
}
void GrafoSimples::Inserir(TreePointer &r, string &chave1, string &chave2, string &chave3, bool &found){
    if(r == NULL){
        r = new TreeNode;
        r->Entry = chave1;
        if(chave2 != "X"){
            r->LeftNode = new TreeNode;
            r->LeftNode->Entry = chave2;
        }
        if(chave3 !=  "X"){
            r->RightNode = new TreeNode;
            r->RightNode->Entry = chave3;
        }
        return;
    }
    else if (chave1 == r->Entry){
        found = true;
        if(chave2 != "X"){
            r->LeftNode = new TreeNode;
            r->LeftNode->Entry = chave2;
            r->LeftNode->LeftNode = NULL;
            r->LeftNode->RightNode = NULL;

        }
        else
            r->LeftNode = NULL;
        if(chave3 != "X"){
            r->RightNode = new TreeNode;
            r->RightNode->Entry = chave3;
            r->RightNode->LeftNode = NULL;
            r->RightNode->RightNode = NULL;
        }
        else
            r->RightNode = NULL;
        return;
    }
    else{
        if(r->LeftNode != NULL){
            Insert(r->LeftNode, chave1, chave2, chave3, found);

            if(found)
                return;
        }
        if(r->RightNode != NULL){
            Insert(r->RightNode, chave1, chave2, chave3, found);
            return;
        }
    }
    return;
}
void GrafoSimples::Imprimir(){
    if
    cout << "G = ";
    for(int i = 0; i < )
}
void GrafoSimples::Imprimir(TreePointer &r, int &Nodes, int &Leaves){
    Nodes++;
    int num = 0;
    string sons;
    if(r->LeftNode != NULL){
        num++;
        sons += "E";
    }
    if(r->RightNode != NULL){
        num++;
        sons += "D";
    }
    if(sons == "")
        cout << r->Entry << " " << num << " F\n";
    else
        cout << r->Entry << " " << num << " " << sons << endl;
    if(r->LeftNode == NULL && r->RightNode == NULL){
        Leaves++;
        return;
    }
    if(r->LeftNode != NULL){
        Print(r->LeftNode, Nodes, Leaves);

    }
    if(r->RightNode != NULL)
        Print(r->RightNode, Nodes, Leaves);
    return;
}
void GrafoSimples::ImprimirGrafo(){

    if(root != NULL){
        int spaces = 0;
        PrintTree( root, spaces);
    }
    else{
        cout << "\nÁrvore vazia\n";
    }
}
void GrafoSimples::ImprimirGrafo(TreePointer &r, int spaces){
    if(r->RightNode == NULL){
        for(int i = 0; i < spaces+1; i++)
            cout << "      ";
        cout << "X" << endl;
    }
    else
        PrintTree(r->RightNode, spaces+1);
    for(int i = 0; i < spaces; i++)
        cout << "      ";
    cout << r->Entry << endl;
    if(r->LeftNode == NULL){
        for(int i = 0; i < spaces+1; i++)
            cout << "      ";
        cout << "X" << endl;
    }
    else
        PrintTree(r->LeftNode, spaces+1);
}

