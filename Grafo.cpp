/*
Denilson Aparecido Gon�alves Junior - 2176481
Thaynara Santos Ramos - 2126966
Fernando Peres Borin - 2125219
*/
#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
using namespace std;

GrafoSimples::GrafoSimples(){
    numDeVertices = 0;
}
GrafoSimples::~GrafoSimples(){
}
void GrafoSimples::Ler(string arquivo){
    /*
    Pr�-Condi��o: Um objeto GrafoSimples deve ter sido criado e um arquivo de
    entrada deve existir.

    P�s-Condi��o: Se o arquivo for aberto com sucesso, o grafo ser� preenchido
    com os dados do arquivo.

    Descri��o: Este m�todo tenta abrir o arquivo especificado. Se a abertura
    for bem-sucedida, ele chama o m�todo `Inserir` para popular o grafo
    com os dados do arquivo e, em seguida, fecha o arquivo. Caso contr�rio,
    exibe uma mensagem de erro e encerra o programa.
    */
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
    /*
    Pr�-Condi��o: Um arquivo de entrada v�lido e aberto deve ser fornecido.

    P�s-Condi��o: O grafo ser� preenchido com v�rtices e suas respectivas arestas
    com base nos dados lidos do arquivo.

    Descri��o: Este m�todo l� cada linha do arquivo, separando os v�rtices
    conectados por um ponto e v�rgula. Para cada par de v�rtices, ele verifica
    se os v�rtices j� existem no array `vertices`. Se n�o existirem, eles s�o
    adicionados e o contador `numDeVertices` � incrementado. Em seguida, para
    cada v�rtice lido, o m�todo `Listar` � chamado para adicionar a aresta
    correspondente na lista de adjac�ncias.
    */
    string linha, vertice1, vertice2;
    bool existeNoVetor;
    while(getline(entrada, linha)) {
        stringstream ss(linha);
        getline(ss, vertice1, ';');
        getline(ss, vertice2, ';');
        // Verifica se o vertice1 j� existe no vetor
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
        // Verifica se o vertice2 j� existe no vetor
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
    /*
    Pr�-Condi��o: Um �ndice de v�rtice e o �ndice do array de v�rtices devem
    ser fornecidos.

    P�s-Condi��o: Um novo v�rtice adjacente ser� adicionado � lista de arestas
    do v�rtice na posi��o `i` do array `vertices`.

    Descri��o: Este m�todo cria um novo n� de v�rtice e o adiciona como uma aresta
    ao v�rtice principal na posi��o `i`. Se o v�rtice principal ainda n�o tiver
    arestas, o novo n� se torna a primeira aresta. Caso contr�rio, ele percorre
    a lista de arestas at� o final e adiciona o novo n�.
    */
    Vertice* novo = new Vertice;
    novo->indice = indiceDoVertice;
    novo->aresta = NULL;

    if(vertices[i].aresta == NULL){
        vertices[i].aresta = novo;
    }
    else {
        Vertice* atual = vertices[i].aresta;
        while(atual->aresta != NULL){
            atual = atual->aresta;
        }
        atual->aresta = novo;
    }
}
void GrafoSimples::ImprimirLista(){
    /*
    Pr�-Condi��o: Um objeto GrafoSimples deve ter sido criado.

    P�s-Condi��o: A lista de adjac�ncias do grafo ser� impressa no console.

    Descri��o: Este m�todo percorre todos os v�rtices do grafo. Para cada v�rtice,
    ele imprime o �ndice do v�rtice e, se houver arestas, chama o m�todo
    privado `ImprimirLista` para imprimir recursivamente as arestas conectadas.
    */
    for(int i = 0; i < numDeVertices; i++){
        cout << vertices[i].indice;
        if(vertices[i].aresta != NULL){
            cout << " - ";
            ImprimirLista(vertices[i].aresta);
        }
    }
}
void GrafoSimples::ImprimirLista(Vertice *vertice){
    /*
    Pr�-Condi��o: Um ponteiro para um v�rtice (que representa uma aresta) deve
    ser fornecido.

    P�s-Condi��o: As arestas conectadas a partir do v�rtice fornecido ser�o
    impressas no console.

    Descri��o: Este m�todo recursivo imprime o �ndice do v�rtice atual. Se
    houver mais arestas conectadas, ele adiciona " - " e chama a si mesmo
    recursivamente para imprimir a pr�xima aresta. Se for a �ltima aresta,
    ele imprime o �ndice e uma quebra de linha.
    */
    if(vertice->aresta == NULL){
        cout << vertice->indice << "\n";
        return;
    }
    else{
        cout << vertice->indice << " - ";
        ImprimirLista(vertice->aresta);
    }
}

void GrafoSimples::BuscaEmLargura(string inicio){
    /*
    Pr�-Condi��o: Um objeto GrafoSimples deve ter sido criado e o grafo deve
    conter o v�rtice de in�cio especificado.

    P�s-Condi��o: O resultado da busca em largura a partir do v�rtice de in�cio
    ser� impresso no console.

    Descri��o: Este m�todo implementa o algoritmo de Busca em Largura (BFS).
    Ele inicializa um array `visitados` para controlar os v�rtices j� visitados.
    Encontra o �ndice do v�rtice de in�cio. Se o v�rtice de in�cio n�o for
    encontrado, exibe uma mensagem de erro. Utiliza uma fila para gerenciar a
    ordem de visita��o dos v�rtices. Inicia colocando o v�rtice de in�cio na
    fila e marcando-o como visitado. Em seguida, enquanto a fila n�o estiver
    vazia, ele retira um v�rtice da fila, imprime seu �ndice e adiciona todos
    os seus vizinhos n�o visitados � fila, marcando-os como visitados.
    */
    bool visitados[16]; // Considerando um tamanho m�ximo para o array de visitados.
    for(int i = 0; i < 16; i++){
        visitados[i] = false;
    }
    int indiceInicial = -1;
    for(int i = 0; i < numDeVertices; i++){
        if(vertices[i].indice == inicio){
            indiceInicial = i;
            break;
        }
    }
    if(indiceInicial == -1){
        cout << "\nVertice de inicio nao encontrado.";
        return;
    }
    queue<int> fila;
    fila.push(indiceInicial);
    visitados[indiceInicial] = true;
    bool primeiro = true;
    while(!fila.empty()){
        int v = fila.front();
        fila.pop();
        if(primeiro){
            cout << vertices[v].indice;
            primeiro = false;
        }
        else{
            cout << ", " << vertices[v].indice;
        }
        Vertice* adjacente = vertices[v].aresta;
        while(adjacente != NULL){
            for(int i = 0; i < numDeVertices; i++){
                if(vertices[i].indice == adjacente->indice && !visitados[i]){
                    fila.push(i);
                    visitados[i] = true;
                }
            }
            adjacente = adjacente->aresta;
        }
    }
    cout << endl;
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
    /*
    Pr�-Condi��o: Um objeto Digrafo deve ter sido criado e um arquivo de
    entrada deve existir.

    P�s-Condi��o: Se o arquivo for aberto com sucesso, o digrafo ser� preenchido
    com os dados do arquivo.

    Descri��o: Este m�todo tenta abrir o arquivo especificado. Se a abertura
    for bem-sucedida, ele chama o m�todo `Inserir` para popular o digrafo
    com os dados do arquivo e, em seguida, fecha o arquivo. Caso contr�rio,
    exibe uma mensagem de erro e encerra o programa.
    */
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
    /*
    Pr�-Condi��o: Um arquivo de entrada v�lido e aberto deve ser fornecido.

    P�s-Condi��o: O digrafo ser� preenchido com v�rtices e suas respectivas arestas
    (direcionadas) com base nos dados lidos do arquivo.

    Descri��o: Este m�todo l� cada linha do arquivo, separando os v�rtices
    conectados por um ponto e v�rgula. Para cada par de v�rtices, ele verifica
    se os v�rtices j� existem no array `vertices`. Se n�o existirem, eles s�o
    adicionados e o contador `numDeVertices` � incrementado. Em seguida, para
    o primeiro v�rtice lido, o m�todo `Listar` � chamado para adicionar a
    aresta direcionada correspondente na lista de adjac�ncias e na matriz
    de adjac�ncias.
    */
    string linha, vertice1, vertice2;
    bool existeNoVetor;
    while(getline(entrada, linha)) {
        stringstream ss(linha);
        getline(ss, vertice1, ';');
        getline(ss, vertice2, ';');
        // Verifica se o vertice1 j� existe no vetor
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
        // Verifica se o vertice2 j� existe no vetor
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
    /*
    Pr�-Condi��o: Um �ndice de v�rtice e o �ndice do array de v�rtices devem
    ser fornecidos.

    P�s-Condi��o: Um novo v�rtice adjacente ser� adicionado � lista de arestas
    do v�rtice na posi��o `i` do array `vertices` e a matriz de adjac�ncias
    ser� atualizada.

    Descri��o: Este m�todo cria um novo n� de v�rtice e o adiciona como uma aresta
    ao v�rtice principal na posi��o `i`. Al�m disso, ele atualiza a matriz de
    adjac�ncias marcando com '1' a conex�o entre o v�rtice principal e o v�rtice
    adjacente. O novo n� � inserido no in�cio da lista de adjac�ncias.
    */
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
    /*
    Pr�-Condi��o: Um objeto Digrafo deve ter sido criado.

    P�s-Condi��o: A lista de adjac�ncias do digrafo ser� impressa no console.

    Descri��o: Este m�todo percorre todos os v�rtices do digrafo. Para cada v�rtice,
    ele imprime o �ndice do v�rtice e, se houver arestas, chama o m�todo
    privado `ImprimirLista` para imprimir recursivamente as arestas direcionadas
    conectadas, adicionando " -> " entre elas.
    */
    for(int i = 0; i < numDeVertices; i++){
        cout << vertices[i].indice;
        if(vertices[i].aresta != NULL){
            cout << " -> ";
            ImprimirLista(vertices[i].aresta);
        }
        cout <<"\n";
    }
}
void Digrafo::ImprimirLista(Vertice *vertice){
    /*
    Pr�-Condi��o: Um ponteiro para um v�rtice (que representa uma aresta) deve
    ser fornecido.

    P�s-Condi��o: As arestas direcionadas conectadas a partir do v�rtice
    fornecido ser�o impressas no console.

    Descri��o: Este m�todo recursivo imprime o �ndice do v�rtice atual. Se
    houver mais arestas conectadas, ele adiciona " -> " e chama a si mesmo
    recursivamente para imprimir a pr�xima aresta. Se for a �ltima aresta,
    ele apenas imprime o �ndice.
    */
    if(vertice->aresta == NULL){
        cout << vertice->indice;
        return;
    }
    else{
        cout << vertice->indice << " -> ";
        ImprimirLista(vertice->aresta);
    }
}
void Digrafo::ImprimirMatriz(){
    /*
    Pr�-Condi��o: Um objeto Digrafo deve ter sido criado e a matriz de
    adjac�ncias deve ter sido preenchida.

    P�s-Condi��o: A matriz de adjac�ncias do digrafo ser� impressa no console.

    Descri��o: Este m�todo percorre a matriz de adjac�ncias e imprime seus
    elementos. A cada 8 colunas (ou seja, quando `j` � um m�ltiplo de 8),
    uma nova linha � iniciada para formatar a sa�da da matriz.
    */
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j % 8 == 0)
                cout << endl;
            cout << matrizDeAdjacencias[i][j] << " ";
        }
    }
}
void Digrafo::BuscaEmProfundidade(string inicio){
    /*
    Pr�-Condi��o: Um objeto Digrafo deve ter sido criado e o digrafo deve
    conter o v�rtice de in�cio especificado.

    P�s-Condi��o: O resultado da busca em profundidade a partir do v�rtice
    de in�cio ser� impresso no console.

    Descri��o: Este m�todo inicializa um array `visitados` para controlar
    os v�rtices j� visitados. Encontra o �ndice do v�rtice de in�cio. Se
    o v�rtice de in�cio n�o for encontrado, exibe uma mensagem de erro.
    Em seguida, chama o m�todo privado `BuscaEmProfundidade` para iniciar
    a busca recursiva, passando o �ndice do v�rtice de in�cio, o array
    `visitados` e um flag `primeiro` para controlar a formata��o da sa�da.
    */
    bool visitados[8]; // Considerando um tamanho m�ximo para o array de visitados.
    for(int i = 0; i < 8; i++){
        visitados[i] = false;
    }

    int indiceInicial = -1;
    for(int i = 0; i < numDeVertices; i++){
        if(vertices[i].indice == inicio){
            indiceInicial = i;
            break;
        }
    }

    if(indiceInicial == -1){
        cout << "\nVertice de inicio nao encontrado.";
        return;
    }

    bool primeiro = true;
    BuscaEmProfundidade(indiceInicial, visitados, primeiro);
    cout << endl;
}
void Digrafo::BuscaEmProfundidade(int v, bool visitados[], bool &primeiro){
    /*
    Pr�-Condi��o: O �ndice de um v�rtice `v`, um array `visitados` e um
    flag `primeiro` devem ser fornecidos.

    P�s-Condi��o: Os v�rtices visitados durante a busca em profundidade ser�o
    impressos no console.

    Descri��o: Este m�todo recursivo implementa o algoritmo de Busca em
    Profundidade (DFS). Ele marca o v�rtice atual `v` como visitado e o
    imprime. Em seguida, percorre todos os v�rtices adjacentes a `v`. Para
    cada vizinho n�o visitado, ele chama a si mesmo recursivamente para
    continuar a busca em profundidade a partir desse vizinho.
    */
    visitados[v] = true;
    if(primeiro){
        cout << vertices[v].indice;
        primeiro = false;
    }
    else{
        cout << ", " << vertices[v].indice;
    }

    Vertice* adjacente = vertices[v].aresta;
    while(adjacente != NULL){
        for(int i = 0; i < numDeVertices; i++){
            if(vertices[i].indice == adjacente->indice && !visitados[i]){
                BuscaEmProfundidade(i, visitados, primeiro);
            }
        }
        adjacente = adjacente->aresta;
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
    /*
    Pr�-Condi��o: Um objeto GrafoPonderado deve ter sido criado e um arquivo de
    entrada deve existir.

    P�s-Condi��o: Se o arquivo for aberto com sucesso, o grafo ponderado ser�
    preenchido com os dados do arquivo.

    Descri��o: Este m�todo tenta abrir o arquivo especificado. Se a abertura
    for bem-sucedida, ele chama o m�todo `Inserir` para popular o grafo
    com os dados do arquivo e, em seguida, fecha o arquivo. Caso contr�rio,
    exibe uma mensagem de erro e encerra o programa.
    */
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
    /*
    Pr�-Condi��o: Um arquivo de entrada v�lido e aberto deve ser fornecido.

    P�s-Condi��o: O grafo ponderado ser� preenchido com v�rtices e suas
    respectivas arestas com pesos, com base nos dados lidos do arquivo.

    Descri��o: Este m�todo l� cada linha do arquivo, separando os v�rtices
    e o peso da aresta por um ponto e v�rgula. Para cada par de v�rtices,
    ele verifica se os v�rtices j� existem no array `vertices`. Se n�o existirem,
    eles s�o adicionados e o contador `numDeVertices` � incrementado. Em seguida,
    para cada v�rtice lido, o m�todo `Listar` � chamado para adicionar a aresta
    correspondente com seu peso na lista de adjac�ncias e na matriz de adjac�ncias.
    */
    string linha, vertice1, vertice2, peso;
    bool existeNoVetor;
    while(getline(entrada, linha)) {
        stringstream ss(linha);
        getline(ss, vertice1, ';');
        getline(ss, vertice2, ';');
        getline(ss, peso, ';');
        // Verifica se o vertice1 j� existe no vetor*
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
        // Verifica se o vertice2 j� existe no vetor
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
    /*
    Pr�-Condi��o: Um �ndice de v�rtice, o �ndice do array de v�rtices e o peso
    da aresta devem ser fornecidos.

    P�s-Condi��o: Um novo v�rtice adjacente com seu peso ser� adicionado �
    lista de arestas do v�rtice na posi��o `i` do array `vertices` e a matriz
    de adjac�ncias ser� atualizada.

    Descri��o: Este m�todo cria um novo n� de v�rtice, atribui seu �ndice e peso,
    e o adiciona como uma aresta ao v�rtice principal na posi��o `i`. Al�m disso,
    ele atualiza a matriz de adjac�ncias com o peso da conex�o entre o v�rtice
    principal e o v�rtice adjacente. O novo n� � inserido no in�cio da lista
    de adjac�ncias.
    */
    Vertice* novo = new Vertice;
    novo->indice = indiceDoVertice;
    novo->aresta = NULL;
    novo->peso = peso;
    for(int j = 0; j < 8; j++){ // Assumindo tamanho m�ximo para o array de v�rtices
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
    /*
    Pr�-Condi��o: Um objeto GrafoPonderado deve ter sido criado.

    P�s-Condi��o: A lista de adjac�ncias do grafo ponderado ser� impressa no console.

    Descri��o: Este m�todo percorre todos os v�rtices do grafo ponderado. Para cada
    v�rtice, ele imprime o �ndice do v�rtice e, se houver arestas, chama o m�todo
    privado `ImprimirLista` para imprimir recursivamente as arestas conectadas
    juntamente com seus pesos. Uma nova linha � adicionada ap�s a impress�o de
    cada v�rtice e suas arestas.
    */
    for(int i = 0; i < numDeVertices; i++){
        cout << vertices[i].indice;
        if(vertices[i].aresta != NULL){
            cout << " ";
            ImprimirLista(vertices[i].aresta);
        }
        cout << endl;
    }
}

void GrafoPonderado::ImprimirLista(Vertice *vertice){
    /*
    Pr�-Condi��o: Um ponteiro para um v�rtice (que representa uma aresta) deve
    ser fornecido.

    P�s-Condi��o: As arestas conectadas a partir do v�rtice fornecido, juntamente
    com seus pesos, ser�o impressas no console.

    Descri��o: Este m�todo recursivo imprime o peso e o �ndice do v�rtice atual.
    Se houver mais arestas conectadas, ele adiciona um espa�o e chama a si mesmo
    recursivamente para imprimir a pr�xima aresta e seu peso. Se o ponteiro
    do v�rtice for nulo, a fun��o retorna.
    */
    if(vertice == NULL)
        return;
    cout << "-" << vertice->peso << "- " << vertice->indice;
    if(vertice->aresta != NULL){
        cout << " ";
        ImprimirLista(vertice->aresta);
    }
}

void GrafoPonderado::ImprimirMatriz(){
    /*
    Pr�-Condi��o: Um objeto GrafoPonderado deve ter sido criado e a matriz de
    adjac�ncias deve ter sido preenchida.

    P�s-Condi��o: A matriz de adjac�ncias do grafo ponderado ser� impressa no console.

    Descri��o: Este m�todo percorre a matriz de adjac�ncias e imprime seus
    elementos (pesos das arestas). A cada 7 colunas (ou seja, quando `j` � um
    m�ltiplo de 7), uma nova linha � iniciada para formatar a sa�da da matriz.
    Ele tamb�m adiciona um espa�o extra para pesos de um �nico caractere para
    melhor alinhamento.
    */
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
