/*Victor Shigueo Okuhama N.USP:10724052*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct prim
{
    int vertices;
    int arestas;
    int **grafo; // grafo com ate max_vertices quantidades de vertices
    int max_vertices;
    int infinito;
    int custo_minimo;       // custo minimo do grafo
    int *ordem_vertices;
} PRIM;

void startPrim(PRIM *prim, int qtd_max_vertices);

/* Funcao qual ira alocar o grafo. */
void alocar_grafo(PRIM *prim);

/* Funcao qual ira liberar o grafo. */
void liberar_grafo(PRIM *prim);

/* Funcao qual ira fazer o calculo do custo minimo no grafo. */
void calcular_custo_minimo(PRIM *prim);

/* Funcao qual ira calcuar o custo minimo no grafo de acordo com o
 * algoritmo de Prim. 
 */
void mostrar_custo_minimo(PRIM *prim);

/* Funcao qual ira mostrar a ordem dos vertices, em outras palavras,
 * ira montar a "arvore geradora de custo minimo" mostrando os 
 * conjuntos de vertices. 
 */
void mostrar_ordem_vertices(PRIM *prim);

/* Funcao qual ira salvar no arquivo de texto ".txt" os dados
 * armazenados na struct.
 */
void gerar_saida(PRIM *prim);

/* Funcao qual ira verificar se o arquivo ".txt" carregado esta vazio */
int verificar_arquivo_vazio(PRIM *prim);

void startPrim(PRIM *prim, int maxVertices)
{
    int i, m, n, peso;

    FILE *arquivo;
    arquivo = fopen("grafo01.txt", "r");
    prim->max_vertices = maxVertices;
    prim->infinito = 9999; // valor que significa infinito

    if (arquivo == NULL)
    {
        printf("Erro! O arquivo nao foi encontrado!\n");
        exit(0);
    }

    // verifica se o arquivo esta vazio
    if (verificar_arquivo_vazio(prim) == 0)
    {
        printf("Erro! O arquivo %s esta vazio!\n", "grafo01.txt");
        exit(0);
    }

    // carrega quantidade de vertices e arestas
    for (i = 0; i < 1; i++)
    {
        if (i == 0)
        {
            fscanf(arquivo, "%d %d", &(prim->vertices), &(prim->arestas));
        }
    }

    // verifica se existem vertices
    if (prim->vertices == 0)
    {
        printf("Erro! Nao existem vertices!\n");
        exit(0);
    }

    alocar_grafo(prim);

    for (i = 2; i < (prim->arestas + 2); i++)
    {
        fscanf(arquivo, "%d %d %d", &m, &n, &peso);
        if (peso < 0)
        {
            printf("Erro! Nao pode existem peso negativo!\n");
            exit(0);
        }
        if (m >= prim->vertices || m < 0)
        {
            printf("Erro! O vertice %d nao existe!\n", m);
            exit(0);
        }
        if (n >= prim->vertices || n < 0)
        {
            printf("Erro! O vertice %d nao existe!\n", n);
            exit(0);
        }

        prim->grafo[m][n] = peso;
        prim->grafo[n][m] = peso;
    }

    fclose(arquivo);
}

void alocar_grafo(PRIM *prim)
{
    int i, j;
    if (prim->vertices > prim->max_vertices)
    {
        printf("Erro! Impossivel alocar um grafo com mais de %d vertices!\n", prim->max_vertices);
        exit(0);
    }

    // alocar linhas
    prim->grafo = (int **)malloc(sizeof(int *) * prim->vertices);
    if (prim->grafo == NULL)
    {
        printf("Erro ao alocar grafo! Memoria insuficiente!\n");
        exit(0);
    }

    // alocar colunas
    for (i = 0; i < prim->vertices; i++)
    {
        prim->grafo[i] = (int *)malloc(sizeof(int) * prim->vertices);
        if (prim->grafo[i] == NULL)
        {
            printf("Erro ao alocar grafo! Memoria insuficiente!\n");
            exit(0);
        }
    }

        prim->ordem_vertices = (int *)malloc(sizeof(int) * 20);
        if (prim->ordem_vertices == NULL)
        {
            printf("Erro ao alocar grafo! Memoria insuficiente!\n");
            exit(0);
        }


    for (i = 0; i < prim->vertices; i++)
    {
        for (j = 0; j < prim->vertices; j++)
        {
            prim->grafo[i][j] = prim->infinito;
        }
    }
}

void calcular_custo_minimo(PRIM *prim)
{
    mostrar_custo_minimo(prim);
    mostrar_ordem_vertices(prim);
}

void mostrar_custo_minimo(PRIM *prim)
{
    int i, j;
    int visitados[prim->vertices];
    int minimo = prim->infinito;
    int u = 0, v = 0, total = 0;
    int esta_rodando = 1;

    for (v = 0; v < prim->vertices; v++)
        visitados[v] = -1;

    visitados[0] = 0;
    while (esta_rodando != 0)
    {
        minimo = prim->infinito;
        for (i = 0; i < prim->vertices; i++)
            if (visitados[i] != -1)
                for (j = 0; j < prim->vertices; j++)
                    if (visitados[j] == -1 && minimo > prim->grafo[i][j])
                    {
                        minimo = prim->grafo[i][j];
                        u = i;
                        v = j;
                    }

        if (minimo == prim->infinito)
        {
            esta_rodando = 0; // fim do laco
            break;            // sai do laco
        }

        visitados[v] = u;
        total += minimo;
    }
    prim->custo_minimo = total;
    printf("%d\n", prim->custo_minimo);
}

void mostrar_ordem_vertices(PRIM *prim)
{
    int i, j;
    int visitados[prim->vertices];
    int minimo = prim->infinito;
    int u = 0, v = 0, x=0;
    int esta_rodando = 1;

    for (v = 0; v < prim->vertices; v++)
        visitados[v] = -1;

    visitados[0] = 0;
    while (esta_rodando != 0)
    {
        minimo = prim->infinito;
        for (i = 0; i < prim->vertices; i++)
            if (visitados[i] != -1)
                for (j = 0; j < prim->vertices; j++)
                    if (visitados[j] == -1 && minimo > prim->grafo[i][j])
                    {
                        minimo = prim->grafo[i][j];
                        u = i;
                        v = j;
                    }

        if (minimo == prim->infinito)
        {
            esta_rodando = 0; // fim do laco
            break;            // sai do laco
        }

        visitados[v] = u;
        prim->ordem_vertices[x] = u;
        prim->ordem_vertices[x+1] = v;
        x++;
        printf("(%d, %d) ", u, v);
    }
    printf("\n");
}

void gerar_saida(PRIM *prim)
{
    int v;
    FILE *arquivo;
    arquivo = fopen("saidaTeste.txt", "a");
    fprintf(arquivo, "%d\n", prim->custo_minimo); // salva informacoes no arquivo prim->arquivo_saida
    for (v = 0; v < 20; v++)
        fprintf(arquivo, "%d %d\n", prim->ordem_vertices[v], prim->ordem_vertices[v+1]);
    fclose(arquivo);
}

int verificar_arquivo_vazio(PRIM *prim)
{
    FILE *arquivo = fopen("grafo01.txt", "r");
    int c, vazio = 1;
    int qtd = 0;

    while ((c = fgetc(arquivo)) != EOF)
    {
        vazio = 0;
        if (c == '\n')
            qtd++;
    }

    if (vazio == 0)
        qtd++;

    return qtd;
}

void liberar_grafo(PRIM *prim) {
	int i;
	if(prim->grafo == NULL) {
		printf("Erro! Grafo nao existe!\n");
		exit(0);
	}
	for(i = 0; i < prim->vertices; i++) {
		free(prim->grafo[i]);
	}
	free(prim->grafo);
}

int main()
{
    PRIM prim1;
    // inicializa prim com no maximo 200 vertices
	startPrim(&prim1, 200);

	// calcula o custo minimo
	calcular_custo_minimo(&prim1);

	// salva informacoes no arquivo "saida.txt"
	gerar_saida(&prim1);

	// libera grafo da memoria
	liberar_grafo(&prim1);

	return 0;
}