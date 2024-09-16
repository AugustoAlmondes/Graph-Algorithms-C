#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funcoes.h"
#define MAX 81

int encontrarVerticeMinimo(int distancias[], int visitados[], int numVertices)
{
    // Inicializa a variável para armazenar o valor mínimo encontrado
    int minimo = 999;
    // Variável para armazenar o índice do vértice com o valor mínimo
    int indiceMinimo;

    // Itera sobre todos os vértices no grafo
    for (int v = 0; v < numVertices; v++)
    {
        // Verifica se o vértice ainda não foi visitado e se sua distância é menor ou igual ao mínimo atual
        if (!visitados[v] && distancias[v] <= minimo)
        {
            minimo = distancias[v];
            indiceMinimo = v;
        }
    }

    return indiceMinimo;
}

void dijkstra(Graph *grafo, int origem, int destino, int numVertices)
{
    LARGE_INTEGER start_time, end_time, frequency;
    double elapsed_time_ms;
    // menor distância conhecida de um vértice para a origem
    int *distancias = (int *)malloc(numVertices * sizeof(int));
    // caminho mais curto para cada vértice
    int *caminho = (int *)malloc(numVertices * sizeof(int));
    // quais vértices já foram processados
    int *visitados = (int *)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        distancias[i] = 999;
        caminho[i] = -1;
        visitados[i] = 0;
    }

    // distancia de origem
    distancias[origem] = 0;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);
    for (int i = 0; i < numVertices - 1; i++)
    {
        int menor_dst = encontrarVerticeMinimo(distancias, visitados, numVertices);

        // Marca o vértice como visitado
        visitados[menor_dst] = 1;

        for (int j = 0; j < numVertices; j++)
        {
            if (!visitados[j] && grafo->arestas[menor_dst][j] && distancias[menor_dst] != 999 && distancias[menor_dst] + grafo->arestas[menor_dst][j] < distancias[j])
            {
                distancias[j] = distancias[menor_dst] + grafo->arestas[menor_dst][j];
                caminho[j] = menor_dst;
            }
        }
    }
    QueryPerformanceCounter(&end_time);
    elapsed_time_ms = ((double)(end_time.QuadPart - start_time.QuadPart) * 1000.0) / frequency.QuadPart;

    printf("Tempo decorrido: %.5f ms\n", elapsed_time_ms);

    if (origem == 0 && destino == 65)
    {
        printf("Caminho mais curto de %d para %d: %d", origem, destino, distancias[destino]);
        printf("\nCaminho: ");
    }

    int i = destino;
    printf("%d", i);

    while (caminho[i] != origem)
    {
        printf(" <- %d", caminho[i]);
        i = caminho[i];
    }

    printf(" <- %d", origem);
}

void fordMooreBellman(Graph *grafo, int origem, int numVertices)
{
    LARGE_INTEGER start_time, end_time, frequency;
    double elapsed_time_ms;
    int *distancias = (int *)malloc(numVertices * sizeof(int));
    int *caminho = (int *)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        distancias[i] = 999;
        caminho[i] = -1;
    }

    distancias[origem] = 0;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);
    for (int count = 0; count < numVertices - 1; count++)
    {
        for (int u = 0; u < numVertices; u++)
        {
            for (int v = 0; v < numVertices; v++)
            {
                if (grafo->arestas[u][v] && distancias[u] != 999 && distancias[u] + grafo->arestas[u][v] < distancias[v])
                {
                    distancias[v] = distancias[u] + grafo->arestas[u][v];
                    caminho[v] = u;
                }
            }
        }
    }  
    QueryPerformanceCounter(&end_time);
    
    elapsed_time_ms = ((double)(end_time.QuadPart - start_time.QuadPart) * 1000.0) / frequency.QuadPart;
    printf("Tempo decorrido: %.5f ms\n", elapsed_time_ms);

    printf("Caminhos mais curtos a partir de %d:\n", origem);
    for (int i = 0; i < numVertices; i++)
    {
        if (i == 65)
        {
            printf("Para %d: ", i);
            int j = i;
            while (caminho[j] != -1)
            {
                printf("%d <- ", j);
                j = caminho[j];
            }
            printf("%d Distancia: %d\n", j, distancias[i]);
        }
    }
}

Graph *iniciaGrafo(int n)
{
    Graph *G;

    G = (Graph *)malloc(sizeof(Graph));

    // Alocação de memoria para o vetor de vertices
    G->vertices = (Vertice *)malloc(n * sizeof(Vertice));

    // Alocação de memoria para a matriz de arestas
    G->arestas = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        G->arestas[i] = (int *)calloc(n, sizeof(int));
    }

    return G;
}

void setValorVertice(Graph *G, int i, int vermelho, int amarelo, int verde, int rosa)
{
    G->vertices[i].discos[0] = vermelho;
    G->vertices[i].discos[1] = amarelo;
    G->vertices[i].discos[2] = verde;
    G->vertices[i].discos[3] = rosa;
    // contador_glb += 1;
    // if (contador_glb == 80)
    //     printf("chegou!!!\n"); // verificação (pode relevar isso)
}

void verificar_rosa(Graph *G, int vermelho, int amarelo, int verde, int rosa_pino_2[], int rosa_pino_3[], int i)
{
    int rosa = 1;
    // ROSA
    if (verificar(rosa_pino_2, rosa_pino_3, i) == 3)
    {
        rosa = 3;
        setValorVertice(G, i, vermelho, amarelo, verde, rosa);
    }
    // ROSA
    else if (verificar(rosa_pino_2, rosa_pino_3, i) == 2)
    {
        rosa = 2;
        setValorVertice(G, i, vermelho, amarelo, verde, rosa);
    }
    // ROSA
    else
    {
        setValorVertice(G, i, vermelho, amarelo, verde, rosa);
    }
}

void verificar_verde(Graph *G, int vermelho, int amarelo, int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i)
{
    int verde = 1;
    // VERDE
    if (verificar(verde_pino_2, verde_pino_3, i) == 3)
    {
        verde = 3;
        verificar_rosa(G, vermelho, amarelo, verde, rosa_pino_2, rosa_pino_3, i);
        // printf("        2\n");
    }
    // VERDE
    else if (verificar(verde_pino_2, verde_pino_3, i) == 2)
    {
        verde = 2;
        verificar_rosa(G, vermelho, amarelo, verde, rosa_pino_2, rosa_pino_3, i);
        // printf("    2   \n");
    }
    // VERDE
    else
    {
        verificar_rosa(G, vermelho, amarelo, 1, rosa_pino_2, rosa_pino_3, i);
        // printf("2       \n");
    }
}

void verificar_amarelo(Graph *G, int vermelho, int amarelo_pino_2[], int amarelo_pino_3[], int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i)
{
    int amarelo = 1;
    // AMARELO
    if (verificar(amarelo_pino_2, amarelo_pino_3, i) == 3)
    {
        amarelo = 3;
        verificar_verde(G, vermelho, amarelo, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i);
        // printf("        3\n");
    }
    // AMARELO
    else if (verificar(amarelo_pino_2, amarelo_pino_3, i) == 2)
    {
        amarelo = 2;
        verificar_verde(G, vermelho, amarelo, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i);
        // printf("    3   \n");
    }
    // AMARELO
    else
    {
        verificar_verde(G, vermelho, amarelo, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i);
        // printf("3       \n");
    }
}

void inserirVertices(Graph *G)
{
    int rosa_pino_3[27] = {50, 58, 65, 46, 71, 70, 53, 61, 76, 77, 56, 64, 28, 42, 43, 29, 33, 40, 9, 20, 21, 26, 17, 13, 2, 4, 5};
    int rosa_pino_2[27] = {1, 3, 8, 12, 16, 19, 24, 25, 10, 27, 38, 39, 32, 36, 41, 47, 74, 75, 55, 63, 80, 52, 60, 69, 57, 49, 58};

    int verde_pino_3[27] = {57, 65, 66, 46, 51, 52, 62, 75, 76, 63, 77, 78, 28, 31, 32, 34, 39, 40, 9, 11, 12, 18, 25, 26, 3, 5, 6};
    int verde_pino_2[27] = {4, 7, 8, 10, 13, 14, 35, 41, 42, 47, 53, 54, 64, 79, 80, 15, 19, 20, 27, 29, 30, 59, 69, 70, 58, 67, 68};

    int amarelo_pino_2[27] = {9, 11, 12, 15, 16, 19, 20, 21, 22, 27, 29, 30, 33, 34, 37, 38, 39, 40, 48, 55, 56, 63, 64, 77, 78, 79, 80};
    int amarelo_pino_3[27] = {10, 13, 14, 17, 18, 23, 24, 25, 26, 45, 49, 50, 57, 58, 65, 66, 67, 68, 28, 31, 32, 35, 36, 41, 42, 43, 44};

    int vermelho_pino_3[27] = {27, 29, 30, 33, 34, 37, 38, 39, 40, 45, 46, 49, 50, 51, 52, 57, 58, 59, 60, 65, 66, 67, 68, 69, 70, 71, 72};
    int vermelho_pino_2[27] = {28, 31, 32, 35, 36, 41, 42, 43, 44, 47, 48, 53, 54, 55, 56, 61, 62, 63, 64, 73, 74, 75, 76, 77, 78, 79, 80};

    for (int i = 0; i <= 80; i++)
    {
        int vermelho = 1;
        // VERMELHO
        if (i >= 26 && verificar(vermelho_pino_2, vermelho_pino_3, i) == 3)
        {
            vermelho = 3;
            verificar_amarelo(G, vermelho, amarelo_pino_2, amarelo_pino_3, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i);
            // printf("        4\n");
        }
        // VERMELHO
        else if (i >= 26 && verificar(vermelho_pino_2, vermelho_pino_3, i) == 2)
        {
            vermelho = 2;
            verificar_amarelo(G, vermelho, amarelo_pino_2, amarelo_pino_3, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i);
            // printf("    4   \n");
        }
        // VERMELHO
        else
        {
            verificar_amarelo(G, vermelho, amarelo_pino_2, amarelo_pino_3, verde_pino_2, verde_pino_3, rosa_pino_2, rosa_pino_3, i);
            // printf("4       \n");
        }
        // printf("____________\n");
    }
}

void inserirArestas(Graph *G)
{
    FILE *arestas;
    arestas = fopen("arestas.txt", "r");
    int verticeAtual = 0, aresta1, aresta2, aresta3;

    while (fscanf(arestas, "%d %d %d %d", &verticeAtual, &aresta1, &aresta2, &aresta3) != EOF)
    {
        G->arestas[verticeAtual][aresta1] = 1;
        G->arestas[verticeAtual][aresta2] = 1;

        if (aresta3 != 9999)
        {
            G->arestas[verticeAtual][aresta3] = 1;
        }
    }
}


void posicao_aresta(int *vetorVertice, int *vetorResposta, int *cont)
{
    *cont = 0;

    for (int i = 0; i < 81; i++)
    {
        if (vetorVertice[i] == 1)
        {
            if (*cont == 0)
                vetorResposta[0] = i;
            if (*cont == 1)
                vetorResposta[1] = i;
            if (*cont == 2)
                vetorResposta[2] = i;
            *cont += 1;
        }
    }
}

int verificaVitoria(Graph *G, int vertice)
{
    int incremento = 0;
    for (int i = 0; i < 4; i++)
    {
        if (G->vertices[vertice].discos[i] == 3)
        {
            incremento += 1;
        }
    }
    return incremento;
}

void jogar(Graph *G, int vertice)
{
    int vetorResposta[3], cont, flagParada = 1;
    int aux;

    if (G->vertices[vertice].discos[0] == 3 && G->vertices[vertice].discos[1] == 3 &&
        G->vertices[vertice].discos[2] == 3 && G->vertices[vertice].discos[3] == 3)
    {
        printf("\nVertice atual e conteudo.\n ");
        print_confg(G, vertice);
    }
    else
    {
        while ((verificaVitoria(G, vertice) != 4) && (flagParada != 0))
        {

            printf("\n\t  Vertice atual e conteudo.\n\n");
            print_confg(G, vertice);
            linha();
            printf("\t  Possibilidades de para onde pode ir: \n\n");

            zerar_vetor(vetorResposta);

            posicao_aresta(G->arestas[vertice], vetorResposta, &cont);

            print_confg(G, vetorResposta[0]);
            print_confg(G, vetorResposta[1]);

            if (cont == 3)
            {
                print_confg(G, vetorResposta[2]);
            }
            linha();

            aux = vertice;

            printf("\nDigite o indice do vertice que deseja ir: ");
            scanf(" %d", &vertice);
            linha();

            if (verificar_sequencia(G, vertice, vetorResposta, cont) == 0)
            {
                linha();
                printf("\t-------------------------------------------------\n");
                printf("\t---INDICE FORA DE SEQUENCIA, ESCOLHA NOVAMENTE---\n");
                printf("\t--------------------------------------------------\n");
                vertice = aux;
            }
        }
    }
    vitoria();
}

int verificar_sequencia(Graph *G, int vertice, int vetorResposta[], int cont)
{
    int result = 1;
    if (cont == 3)
    {
        if (G->arestas[vertice] != G->arestas[vetorResposta[0]] &&
            G->arestas[vertice] != G->arestas[vetorResposta[1]] &&
            G->arestas[vertice] != G->arestas[vetorResposta[2]])
        {
            // NAO EXISTE NAO SEQUENCIA
            result = 0;
        }
    }
    else
    {
        if (G->arestas[vertice] != G->arestas[vetorResposta[0]] &&
            G->arestas[vertice] != G->arestas[vetorResposta[1]])
        {
            // NAO EXISTE NAO SEQUENCIA
            result = 0;
        }
    }
    return result;
}

int verificar(int pino_2[], int pino_3[], int i)
{
    for (int j = 0; j <= 27; j++)
    {
        if (i == pino_3[j])
        {
            return 3;
        }
        else if (i == pino_2[j])
        {
            return 2;
        }
    }
    return 0;
}

void imprimirGrafo(Graph *G, int n)
{
    printf("Vertices: \n"
           "  ");
    // n = 19;
    for (int i = 0; i < n; i++)
    {
        printf(" %d", i);
    }
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", i);
        for (int j = 0; j < n; j++)
        {
            printf("%d ", G->arestas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_confg(Graph *G, int i)
{
    printf("\t\tVERTICE = %d:\n vermelho = %d, amarelo = %d, verde = %i, rosa = %i\n", i, G->vertices[i].discos[0], G->vertices[i].discos[1], G->vertices[i].discos[2], G->vertices[i].discos[3]);
}

void linha()
{
    printf("\n"
           "_______________________________________________________________"
           "\n");
}

int condicao_vitoria(Graph *G, int i)
{
    int result = 0; // 0 falso -- 1 verdadeiro
    if (G->vertices[i].discos[0] == 3 && G->vertices[i].discos[1] == 3 &&
        G->vertices[i].discos[2] == 3 && G->vertices[i].discos[3] == 3)
    {
        result = 1;
    }
    return result;
}

void zerar_vetor(int *vetorResposta)
{
    for (int i = 0; i < 3; i++)
    {
        free(vetorResposta);
        vetorResposta = (int *)malloc(sizeof(int));
    }
}

void vitoria()
{
        printf("@@@@@@@@@@@:::@@@@@@:::@@::::::::::@@::.@@@@@::@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@:::@@@@@@:::@@::@@@@@:::@@::.@@@@@::@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@::::::::::::@@::@@@@@:::@@::.@@@@@::@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@@@@@::::@@@@@@::@@@@@:::@@::.@@@@@::@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@@@@@::::@@@@@@::@@@@@:::@@::.@@@@@::@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@@@@@::::@@@@@@::@@@@@:::@@::.@@@@@::@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@@@@@::::@@@@@@::::::::::@@@::::::::@@@@@@@@@@@@@@@\n"
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
"@@::::@@@@@@@@@@@@@::::@::::::::::::::::::@:::::@@@@@@@::::@@\n"
"@@::::@@@@@@@@@@@@@::::@@@@@@@@::::@@@@@@@@::::::::.@@@::::@@\n"
"@@::::@@@@@@@@@@@@@::::@@@@@@@@::::@@@@@@@@::::::::::.@::::@@\n"
"@@::::@@@@@:::@@@@@::::@@@@@@@@::::@@@@@@@@::::@@@:::::::::@@\n"
"@@::::@@:::::::::@@::::@@@@@@@@::::@@@@@@@@::::@@@@@:::::::@@\n"
"@@:::::::::@@@:::::::::@@@@@@@@::::@@@@@@@@::::@@@@@@@:::::@@\n"
"@@:::::@@@@@@@@@@@:::::@::::::::::::::::::@::::@@@@@@@@::::@@\n"
    );
}