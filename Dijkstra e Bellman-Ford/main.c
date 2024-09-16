#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 10 // Defina o número máximo de vértices

// Estrutura para representar uma aresta
struct Aresta
{
    double confiabilidade; // Probabilidade da aresta não falhar
};

void dijkstra(struct Aresta *arestas[][MAX_VERTICES], int numVertices, int origem, int destino, double confiabilidades[], int visitados[])
{
    for (int i = 0; i < numVertices; i++)
    {
        confiabilidades[i] = 0.0;
        visitados[i] = 0;
    }

    confiabilidades[origem] = 1.0;

    for (int count = 0; count < numVertices - 1; count++)
    {
        int u = -1;
        for (int v = 0; v < numVertices; v++)
        {
            if (!visitados[v] && (u == -1 || confiabilidades[v] > confiabilidades[u]))
            {
                u = v;
            }
        }
        visitados[u] = 1;

        for (int v = 0; v < numVertices; v++)
        {
            if (!visitados[v] && arestas[u][v] != NULL)
            {
                double confiabilidade_atual = confiabilidades[u] * arestas[u][v]->confiabilidade;
                if (confiabilidade_atual > confiabilidades[v])
                {
                    confiabilidades[v] = confiabilidade_atual;
                }
            }
        }
    }

    double confiabilidade_final = confiabilidades[destino];

    printf("A confiabilidade do caminho mais confiavel entre %d e %d eh: %.6lf\n", origem, destino, confiabilidade_final);
}

void preencher(struct Aresta *arestas[][MAX_VERTICES], int numVertices)
{
    // Preencher o grafo automaticamente com confiabilidades aleatórias
    srand(time(NULL));
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (i != j)
            {
                if (rand() % 4 != 0) // Condição para gerar aresta nula
                {
                    arestas[i][j] = (struct Aresta *)malloc(sizeof(struct Aresta));
                    // Conf. aleatória entre 0 e 1
                    arestas[i][j]->confiabilidade = (double)rand() / RAND_MAX;
                }
            }
        }
    }
}

void imprimirGrafo(struct Aresta *arestas[][MAX_VERTICES], int numVertices)
{
    printf("Grafo gerado:\n");

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (arestas[i][j] != NULL)
            {
                printf("Vertice %d -> Vertice %d : Confiabilidade %.6lf\n", i, j, arestas[i][j]->confiabilidade);
            }
        }
    }
}

void imprimirMatrizAdjacente(struct Aresta *arestas[][MAX_VERTICES], int numVertices)
{
    printf("Matriz Adjacente:\n");

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (arestas[i][j] != NULL)
            {
                printf("%.5lf\t", arestas[i][j]->confiabilidade);
            }
            else
            {
                printf("0.00000\t");
            }
        }
        printf("\n");
    }
}

void liberar(struct Aresta *arestas[][MAX_VERTICES], int numVertices, double confiabilidades[], int visitados[])
{ // Libere a memória alocada para as arestas
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (arestas[i][j] != NULL)
            {
                free(arestas[i][j]);
            }
        }
    }

    free(confiabilidades);
    free(visitados);
}

int main()
{
    int numVertices;

    printf("Antes do Menu, informe o numero de vertices que seu Grafo tera: ");
    scanf("%d", &numVertices);

    struct Aresta *arestas[MAX_VERTICES][MAX_VERTICES] = {0};
    double *confiabilidades = (double *)malloc(numVertices * sizeof(double));
    int *visitados = (int *)malloc(numVertices * sizeof(int));
    int opc = -1, opc2;
    int preenchido = 0;
    while (opc != 5)
    {
        printf("Opcoes:\n"
               "0 - preencher aresta\n"
               "1 - Imprimir Grafo\n"
               "2 - Imprimir Matriz\n"
               "3 - Buscar caminho confiavel\n"
               "4 - Liberar Grafo\n"
               "5 - Sair\n"
               "Opcao: ");
        scanf(" %d", &opc);
        switch (opc)
        {
        case 0:
            if (preenchido == 0)
            {
                preencher(arestas, numVertices);
                printf("GRAFO PREENCHIDO\n");
                preenchido +=1;
            }
            else
            {
                printf("Grafo ja preenchido\n");
            }
            break;
        case 1:
            printf("Deseja imprimir o Grafo?\n"
                   "1 - Sim\n"
                   "2 - Nao\n"
                   "Opcao: ");
            scanf(" %d", &opc2);
            if (opc2 == 1)
            {
                imprimirGrafo(arestas, numVertices);
            }
            else
            {
                printf("Voltando ao menu\n");
            }
            break;
        case 2:
            printf("Deseja imprimir a matriz?\n"
                   "1 - Sim\n"
                   "2 - Nao\n"
                   "Opcao: ");
            scanf(" %d", &opc2);
            if (opc2 == 1)
            {
                imprimirMatrizAdjacente(arestas, numVertices);
            }
            else
            {
                printf("Voltando ao menu\n");
            }
            break;
        case 3:
            printf("Deseja buscar o menor caminho?\n"
                   "1 - Sim\n"
                   "2 - Nao\n"
                   "Opcao: ");
            scanf(" %d", &opc2);
            if (opc2 == 1)
            {
                printf("Informe o vertice de origem: ");
                int origem;
                scanf("%d", &origem);

                printf("Informe o vertice de destino: ");
                int destino;
                scanf("%d", &destino);

                dijkstra(arestas, numVertices, origem, destino, confiabilidades, visitados);
            }
            else
            {
                printf("Voltando ao menu\n");
            }
            break;
        case 4:
            printf("Deseja liberar o grafo?\n"
                   "1 - Sim\n"
                   "2 - Nao\n"
                   "Opcao: ");
            scanf(" %d", &opc2);
            if (opc2 == 1)
            {
                if (preenchido == 1)
                {
                    liberar(arestas, numVertices, confiabilidades, visitados);
                    printf("GRAFO LIBERADO\n");
                    preenchido = 0;
                }
                else
                {
                    printf("ESSE GRAFO NAO ESTA PREENCHIDO  \n");
                }
            }
            else
            {
                printf("Voltando ao menu\n");
            }
            break;
        default:
            printf("OPCAO INEXISTENTE!!\n");
            break;
        }
    }
    return 0;
}
