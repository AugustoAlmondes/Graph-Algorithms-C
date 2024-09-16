#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
    Graph *G;
    int opc = -1;

    G = iniciaGrafo(81);
    inserirVertices(G);
    inserirArestas(G);
    while (opc != 4)
    {
        linha();
        printf("\t\t\t---OPCOES---\n"
        "\t\t0 - JOGAR\n"
        "\t\t1 - Imprimir Matriz\n"
        "\t\t2 - Dijkstra\n"
        "\t\t3 - Ford-Moore-Bellman\n"
        "\t\t4 - Sair\n"
        "\t\topcao: ");
        scanf(" %d",&opc);
        linha();
        switch (opc)
        {
        case 0:
            jogar(G,0);
            break;
        case 1:
            linha();
            printf("\n\tIMPRIMIR MATRIZ\n");
            imprimirGrafo(G, 81);
            break;
        case 2:
            linha();
            printf("\n");
            dijkstra(G, 0, 65, 81);
            printf("\n");
            break;
        case 3:
            linha();
            printf("\n");
            fordMooreBellman(G, 0, 81);
            printf("\n");
            break;

        default:
            break;
        }
    }
}