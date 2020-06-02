# Algoritmo de Prim - Estrutura de Dados - EADII-EP1

## Apresentação
O objetivo deste exercício-programa é implementar o algoritmo de Prim para
árvores geradoras mínimas (AGM) em grafos. 
Basicamente, o algoritmo recebe um grafo G = (V, E) e devolve uma árvore T = (S, E0). 

O programa deverá ser desenvolvido em C (compilável no gcc/mingw) e deverá ser executável via linha de comando. 
A chamada do programa será na forma:

prim.exe <arquivografo> <arquivosaida> Exemplo:
Prin.exe grafo01.txt saida01.txt
  
### Implementação:
Para a implementação do algoritmo de Prim, recomenda-se usar como base o
pseudo-código abaixo. Inicialmente S e E
0
estão vazios. Adicionamos um vértice inicial v e vamos acrescentando vértices em T na ordem mais barata possível. A função p(v, u) representa o peso da aresta (v, u).

```
Data: G = (V, E)
1 E
0 = ∅ ;
2 S = ∅ ;
3 foreach vertex v ∈ V do
4 custo[v] = ∞;
5 ant[v] = −1 ;
6 custo[v0] = 0 ;
7 while S¬V do
8 Selecione u em V − S tal que custo[u] é mínimo;
9 Adicione u em S;
10 foreach vizinho w de u do
11 if custo[w]> p(u, w) then
12 custo[w] = p(u, w);
13 ant[w]= u;
```


Formatos dos arquivos:

<arquivografo>: Conterá a representação do grafo, e terá o seguinte formato: a 1a
linha conterá o número de vértices e arestas; as demais linhas conterão as especificações
das arestas. Mais especificamente, o formato do arquivo será: n m o1 d1 custo1 o2 d2
custo2 ... onde: n, m (inteiros): número de vértices e de arestas, respectivamente. oi di
(inteiros): origem e destino da i-ésima aresta (i = 1...m) custoi (float ou double): custo da
da i-ésima aresta (i = 1...m) Observações:
  
1. Os vértices do grafo serão indexados de 0 a n-1. 2. Todos os campos são separados
por espaços.

<arquivosaida>: Conterá os resultados da execução do programa. A 1a linha conterá o custo da árvore geradora mínima (ou seja, a soma dos custos das arestas da árvore). As linhas seguintes conterão as arestas da árvore geradora mínima.
O código-fonte deverá ser compilável no gcc ou no mingw.
