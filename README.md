O projeto visa implementar em C uma solução funcional para testar estruturas de dados do tipo grafo, focando em um código robusto e eficiente. Ele é composto por vértices e arestas, que formam a base dos testes em grafos, permitindo analisar o comportamento dessas estruturas em diferentes cenários e aplicações computacionais. O estudo também inclui algoritmos clássicos, como Dijkstra e Bellman-Ford, aplicados para a busca de menor distância e confiabilidade entre vértices.

## Objetivo:
- Implementar um código em C para testar grafos e validar o comportamento de estruturas de dados em diferentes cenários.
  
## Algoritmos Abordados:
- **Torre de Hanói**: Problema clássico, modelado em grafo com 81 possíveis configurações usando 4 discos e 3 pinos. Diversas funções foram implementadas para gerar o grafo e realizar verificações baseadas nas cores dos discos.
  
- **Dijkstra e Bellman-Ford**: Algoritmos usados para encontrar o caminho mais curto em grafos ponderados. O Dijkstra busca o caminho mais curto entre vértices, enquanto o Bellman-Ford resolve o problema considerando grafos com pesos negativos.

## Funções Implementadas:
- **Geração de grafos**: Funções como `iniciaGrafo`, `inserirVertices`, e `inserirArestas` criam o grafo e definem suas conexões.
- **Jogo da Torre de Hanói**: Simulação de jogadas, verificações de vitórias, e validações de movimentos.
- **Algoritmos de Busca**: O algoritmo de Dijkstra encontra o caminho mais curto, enquanto o Bellman-Ford calcula distâncias mínimas mesmo com pesos negativos.

## Testes e Resultados:
O projeto também avalia o desempenho dos algoritmos em termos de confiabilidade e tempo de execução.
