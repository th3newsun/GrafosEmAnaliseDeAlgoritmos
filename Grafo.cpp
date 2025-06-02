/*
Denilson Aparecido Gonçalves Junior - 2176481
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
    Pré-Condição: Um objeto GrafoSimples deve ter sido criado e um arquivo de
    entrada deve existir.

    Pós-Condição: Se o arquivo for aberto com sucesso, o grafo será preenchido
    com os dados do arquivo.

    Descrição: Este método tenta abrir o arquivo especificado. Se a abertura
    for bem-sucedida, ele chama o método `Inserir` para popular o grafo
    com os dados do arquivo e, em seguida, fecha o arquivo. Caso contrário,
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
    Pré-Condição: Um arquivo de entrada válido e aberto deve ser fornecido.

    Pós-Condição: O grafo será preenchido com vértices e suas respectivas arestas
    com base nos dados lidos do arquivo.

    Descrição: Este método lê cada linha do arquivo, separando os vértices
    conectados por um ponto e vírgula. Para cada par de vértices, ele verifica
    se os vértices já existem no array `vertices`. Se não existirem, eles são
    adicionados e o contador `numDeVertices` é incrementado. Em seguida, para
    cada vértice lido, o método `Listar` é chamado para adicionar a aresta
    correspondente na lista de adjacências.
    */
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
    /*
    Pré-Condição: Um índice de vértice e o índice do array de vértices devem
    ser fornecidos.

    Pós-Condição: Um novo vértice adjacente será adicionado à lista de arestas
    do vértice na posição `i` do array `vertices`.

    Descrição: Este método cria um novo nó de vértice e o adiciona como uma aresta
    ao vértice principal na posição `i`. Se o vértice principal ainda não tiver
    arestas, o novo nó se torna a primeira aresta. Caso contrário, ele percorre
    a lista de arestas até o final e adiciona o novo nó.
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
    Pré-Condição: Um objeto GrafoSimples deve ter sido criado.

    Pós-Condição: A lista de adjacências do grafo será impressa no console.

    Descrição: Este método percorre todos os vértices do grafo. Para cada vértice,
    ele imprime o índice do vértice e, se houver arestas, chama o método
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
    Pré-Condição: Um ponteiro para um vértice (que representa uma aresta) deve
    ser fornecido.

    Pós-Condição: As arestas conectadas a partir do vértice fornecido serão
    impressas no console.

    Descrição: Este método recursivo imprime o índice do vértice atual. Se
    houver mais arestas conectadas, ele adiciona " - " e chama a si mesmo
    recursivamente para imprimir a próxima aresta. Se for a última aresta,
    ele imprime o índice e uma quebra de linha.
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
    Pré-Condição: Um objeto GrafoSimples deve ter sido criado e o grafo deve
    conter o vértice de início especificado.

    Pós-Condição: O resultado da busca em largura a partir do vértice de início
    será impresso no console.

    Descrição: Este método implementa o algoritmo de Busca em Largura (BFS).
    Ele inicializa um array `visitados` para controlar os vértices já visitados.
    Encontra o índice do vértice de início. Se o vértice de início não for
    encontrado, exibe uma mensagem de erro. Utiliza uma fila para gerenciar a
    ordem de visitação dos vértices. Inicia colocando o vértice de início na
    fila e marcando-o como visitado. Em seguida, enquanto a fila não estiver
    vazia, ele retira um vértice da fila, imprime seu índice e adiciona todos
    os seus vizinhos não visitados à fila, marcando-os como visitados.
    */
    bool visitados[16]; // Considerando um tamanho máximo para o array de visitados.
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
    Pré-Condição: Um objeto Digrafo deve ter sido criado e um arquivo de
    entrada deve existir.

    Pós-Condição: Se o arquivo for aberto com sucesso, o digrafo será preenchido
    com os dados do arquivo.

    Descrição: Este método tenta abrir o arquivo especificado. Se a abertura
    for bem-sucedida, ele chama o método `Inserir` para popular o digrafo
    com os dados do arquivo e, em seguida, fecha o arquivo. Caso contrário,
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
    Pré-Condição: Um arquivo de entrada válido e aberto deve ser fornecido.

    Pós-Condição: O digrafo será preenchido com vértices e suas respectivas arestas
    (direcionadas) com base nos dados lidos do arquivo.

    Descrição: Este método lê cada linha do arquivo, separando os vértices
    conectados por um ponto e vírgula. Para cada par de vértices, ele verifica
    se os vértices já existem no array `vertices`. Se não existirem, eles são
    adicionados e o contador `numDeVertices` é incrementado. Em seguida, para
    o primeiro vértice lido, o método `Listar` é chamado para adicionar a
    aresta direcionada correspondente na lista de adjacências e na matriz
    de adjacências.
    */
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
    /*
    Pré-Condição: Um índice de vértice e o índice do array de vértices devem
    ser fornecidos.

    Pós-Condição: Um novo vértice adjacente será adicionado à lista de arestas
    do vértice na posição `i` do array `vertices` e a matriz de adjacências
    será atualizada.

    Descrição: Este método cria um novo nó de vértice e o adiciona como uma aresta
    ao vértice principal na posição `i`. Além disso, ele atualiza a matriz de
    adjacências marcando com '1' a conexão entre o vértice principal e o vértice
    adjacente. O novo nó é inserido no início da lista de adjacências.
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
    Pré-Condição: Um objeto Digrafo deve ter sido criado.

    Pós-Condição: A lista de adjacências do digrafo será impressa no console.

    Descrição: Este método percorre todos os vértices do digrafo. Para cada vértice,
    ele imprime o índice do vértice e, se houver arestas, chama o método
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
    Pré-Condição: Um ponteiro para um vértice (que representa uma aresta) deve
    ser fornecido.

    Pós-Condição: As arestas direcionadas conectadas a partir do vértice
    fornecido serão impressas no console.

    Descrição: Este método recursivo imprime o índice do vértice atual. Se
    houver mais arestas conectadas, ele adiciona " -> " e chama a si mesmo
    recursivamente para imprimir a próxima aresta. Se for a última aresta,
    ele apenas imprime o índice.
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
    Pré-Condição: Um objeto Digrafo deve ter sido criado e a matriz de
    adjacências deve ter sido preenchida.

    Pós-Condição: A matriz de adjacências do digrafo será impressa no console.

    Descrição: Este método percorre a matriz de adjacências e imprime seus
    elementos. A cada 8 colunas (ou seja, quando `j` é um múltiplo de 8),
    uma nova linha é iniciada para formatar a saída da matriz.
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
    Pré-Condição: Um objeto Digrafo deve ter sido criado e o digrafo deve
    conter o vértice de início especificado.

    Pós-Condição: O resultado da busca em profundidade a partir do vértice
    de início será impresso no console.

    Descrição: Este método inicializa um array `visitados` para controlar
    os vértices já visitados. Encontra o índice do vértice de início. Se
    o vértice de início não for encontrado, exibe uma mensagem de erro.
    Em seguida, chama o método privado `BuscaEmProfundidade` para iniciar
    a busca recursiva, passando o índice do vértice de início, o array
    `visitados` e um flag `primeiro` para controlar a formatação da saída.
    */
    bool visitados[8]; // Considerando um tamanho máximo para o array de visitados.
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
    Pré-Condição: O índice de um vértice `v`, um array `visitados` e um
    flag `primeiro` devem ser fornecidos.

    Pós-Condição: Os vértices visitados durante a busca em profundidade serão
    impressos no console.

    Descrição: Este método recursivo implementa o algoritmo de Busca em
    Profundidade (DFS). Ele marca o vértice atual `v` como visitado e o
    imprime. Em seguida, percorre todos os vértices adjacentes a `v`. Para
    cada vizinho não visitado, ele chama a si mesmo recursivamente para
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
    Pré-Condição: Um objeto GrafoPonderado deve ter sido criado e um arquivo de
    entrada deve existir.

    Pós-Condição: Se o arquivo for aberto com sucesso, o grafo ponderado será
    preenchido com os dados do arquivo.

    Descrição: Este método tenta abrir o arquivo especificado. Se a abertura
    for bem-sucedida, ele chama o método `Inserir` para popular o grafo
    com os dados do arquivo e, em seguida, fecha o arquivo. Caso contrário,
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
    Pré-Condição: Um arquivo de entrada válido e aberto deve ser fornecido.

    Pós-Condição: O grafo ponderado será preenchido com vértices e suas
    respectivas arestas com pesos, com base nos dados lidos do arquivo.

    Descrição: Este método lê cada linha do arquivo, separando os vértices
    e o peso da aresta por um ponto e vírgula. Para cada par de vértices,
    ele verifica se os vértices já existem no array `vertices`. Se não existirem,
    eles são adicionados e o contador `numDeVertices` é incrementado. Em seguida,
    para cada vértice lido, o método `Listar` é chamado para adicionar a aresta
    correspondente com seu peso na lista de adjacências e na matriz de adjacências.
    */
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
    /*
    Pré-Condição: Um índice de vértice, o índice do array de vértices e o peso
    da aresta devem ser fornecidos.

    Pós-Condição: Um novo vértice adjacente com seu peso será adicionado à
    lista de arestas do vértice na posição `i` do array `vertices` e a matriz
    de adjacências será atualizada.

    Descrição: Este método cria um novo nó de vértice, atribui seu índice e peso,
    e o adiciona como uma aresta ao vértice principal na posição `i`. Além disso,
    ele atualiza a matriz de adjacências com o peso da conexão entre o vértice
    principal e o vértice adjacente. O novo nó é inserido no início da lista
    de adjacências.
    */
    Vertice* novo = new Vertice;
    novo->indice = indiceDoVertice;
    novo->aresta = NULL;
    novo->peso = peso;
    for(int j = 0; j < 8; j++){ // Assumindo tamanho máximo para o array de vértices
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
    Pré-Condição: Um objeto GrafoPonderado deve ter sido criado.

    Pós-Condição: A lista de adjacências do grafo ponderado será impressa no console.

    Descrição: Este método percorre todos os vértices do grafo ponderado. Para cada
    vértice, ele imprime o índice do vértice e, se houver arestas, chama o método
    privado `ImprimirLista` para imprimir recursivamente as arestas conectadas
    juntamente com seus pesos. Uma nova linha é adicionada após a impressão de
    cada vértice e suas arestas.
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
    Pré-Condição: Um ponteiro para um vértice (que representa uma aresta) deve
    ser fornecido.

    Pós-Condição: As arestas conectadas a partir do vértice fornecido, juntamente
    com seus pesos, serão impressas no console.

    Descrição: Este método recursivo imprime o peso e o índice do vértice atual.
    Se houver mais arestas conectadas, ele adiciona um espaço e chama a si mesmo
    recursivamente para imprimir a próxima aresta e seu peso. Se o ponteiro
    do vértice for nulo, a função retorna.
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
    Pré-Condição: Um objeto GrafoPonderado deve ter sido criado e a matriz de
    adjacências deve ter sido preenchida.

    Pós-Condição: A matriz de adjacências do grafo ponderado será impressa no console.

    Descrição: Este método percorre a matriz de adjacências e imprime seus
    elementos (pesos das arestas). A cada 7 colunas (ou seja, quando `j` é um
    múltiplo de 7), uma nova linha é iniciada para formatar a saída da matriz.
    Ele também adiciona um espaço extra para pesos de um único caractere para
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
