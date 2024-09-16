typedef struct Vertice Vertice;

struct Vertice
{ 
    int discos[4];
};
typedef struct Graph Graph;
struct Graph
{
    Vertice *vertices;
    int **arestas;
};

Graph *iniciaGrafo(int n);
void inserirVertices(Graph *G);
void inserirArestas(Graph *G);
void setValorVertice(Graph *G, int i, int vermelho, int amarelo, int verde, int rosa);

void imprimirGrafo(Graph *G, int n);
void print_confg(Graph *G, int i);
int verificar(int pino_2[], int pino_3[], int i);
void verificar_rosa(Graph *G, int vermelho, int amarelo, int verde, int rosa_pino_2[], int rosa_pino_3[], int i);
void verificar_verde(Graph *G, int vermelho, int amarelo, int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i);
void verificar_amarelo(Graph *G, int vermelho, int amarelo_pino_2[], int amarelo_pino_3[], int verde_pino_2[], int verde_pino_3[], int rosa_pino_2[], int rosa_pino_3[], int i);
int condicao_vitoria(Graph *G, int i);

void dijkstra(Graph *grafo, int origem, int destino, int numVertices);
int encontrarVerticeMinimo(int distancias[], int visitados[], int numVertices);
void fordMooreBellman(Graph *grafo, int origem, int numVertices);

void linha();
void vitoria();

int verificaVitoria(Graph *G, int vertice);
void jogar(Graph *G, int vertice);
void posicao_aresta(int *vetorVertice, int *vetorResposta, int *cont);
void zerar_vetor(int *vetorResposta);
int verificar_sequencia(Graph *G, int vertice, int vetorResposta[], int cont);