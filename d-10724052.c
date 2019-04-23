/*Victor Shigueo Okuhama N.USP:10724052*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct prim
{
    int vertices;
    int arestas;
    float **grafo;
    int max_vertices;
    int infinito;
    int custo_minimo;
    int contador;
} PRIM;

void startPrim(PRIM *prim, int qtd_max_vertices, char *entradaArquivo);

/* Aloca o grafo. */
void alocar_grafo(PRIM *prim);

/* Libera o grafo. */
void liberar_grafo(PRIM *prim);

/* Calculo do custo minimo no grafo. */
void calcular_custo_minimo(PRIM *prim, char *arquivoSaida);

/* Verificar se o arquivo ".txt" carregado esta vazio */
int verificar_arquivo_vazio(PRIM *prim, char *entradaArquivo);

/* Valida vertices caso seja negativo ou nao exista*/
void validaVertices(PRIM *prim, int m, int n, int peso);

void startPrim(PRIM *prim, int maxVertices, char *entradaArquivo)
{
    int i, m, n, peso;

    FILE *arquivo;
    arquivo = fopen(entradaArquivo, "r");
    prim->max_vertices = maxVertices;
    prim->infinito = 9999; // valor que significa infinito
    prim->contador = 0;

    if (arquivo == NULL)
    {
        printf("Erro! O arquivo nao foi encontrado!\n");
        exit(0);
    }

    if (verificar_arquivo_vazio(prim, entradaArquivo) == 0)
    {
        printf("Erro! O arquivo %s esta vazio!\n", entradaArquivo);
        exit(0);
    }

    // carrega quantidade de vertices e arestas
    fscanf(arquivo, "%d %d", &(prim->vertices), &(prim->arestas));

    // verifica se existem vertices
    if (prim->vertices == 0)
    {
        printf("Erro! Nao existem vertices!\n");
        exit(0);
    }

    //Aloca o grafo com malloc
    alocar_grafo(prim);

    //Pegando os dados dos vertices e peso
    for (i = 0; i < prim->arestas; i++)
    {
        fscanf(arquivo, "%d %d %d", &m, &n, &peso);

        //Validando Vertices
        validaVertices(prim, m, n, peso);

        //Grafo não direcionado
        prim->grafo[m][n] = peso;
        prim->grafo[n][m] = peso;
    }

    fclose(arquivo);
}

void validaVertices(PRIM *prim, int m, int n, int peso)
{
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
    prim->grafo = malloc(sizeof(float *) * prim->vertices);
    if (prim->grafo == NULL)
    {
        printf("Erro ao alocar grafo! Memoria insuficiente!\n");
        exit(0);
    }

    // alocar colunas
    for (i = 0; i < prim->vertices; i++)
    {
        prim->grafo[i] = malloc(sizeof(float) * prim->vertices);
        if (prim->grafo[i] == NULL)
        {
            printf("Erro ao alocar grafo! Memoria insuficiente!\n");
            exit(0);
        }
    }

    //Setando todos os vertices com valor infinito
    for (i = 0; i < prim->vertices; i++)
    {
        for (j = 0; j < prim->vertices; j++)
        {
            prim->grafo[i][j] = prim->infinito;
        }
    }
}

void calcular_custo_minimo(PRIM *prim, char *arquivoSaida)
{
    int i, j;
    int ordem[prim->vertices * 2];
    int visitados[prim->vertices];
    int minimo = prim->infinito;
    int u = 0, v = 0, total = 0;
    int esta_rodando = 1;
    FILE *arquivo;
    arquivo = fopen(arquivoSaida, "w");

    for (v = 0; v < prim->vertices; v++)
    {
        visitados[v] = -1;
    }

    //Começando pelo primeiro vertice
    visitados[0] = 0;
    while (esta_rodando != 0)
    {
        minimo = prim->infinito;
        //Percorre todos os vertices
        for (i = 0; i < prim->vertices; i++)
        {
            //Percorre todos os vertice que ja foram visitados.
            if (visitados[i] != -1)
            {
                //Percorre todos os vertices que estao ligadas ao vertice i
                //Os vertices sem ligacao tem valor infinito
                for (j = 0; j < prim->vertices; j++)
                {
                    /*Verifica se o vertice adjacente é novo
                    Verifica se o peso do grafo é maior que o atual, sendo atual SEMPRE na primeira vez um numero infinito */

                    printf("Estou no vertice:%d buscando meus vizinhos:\n", i);
                    printf("        J:%d VISITADOS[J]:%d\n", j, visitados[j]);
                    printf("        Prim->Grafo[%d][%d]: %d\n", i, j, prim->grafo[i][j]);
                    if (visitados[j] == -1 && minimo > prim->grafo[i][j])
                    {
                        printf("Vertice menor encontrado: Prim->Grafo[%d][%d]:\n", i, j);
                        minimo = prim->grafo[i][j];
                        printf("        minimo[%d][%d]: %d\n", i, j, minimo);
                        u = i;
                        v = j;
                    }
                }
            }
        }
        
        if (minimo == prim->infinito)
        {
            esta_rodando = 0; // fim do laco
            break;            // sai do laco
        }

        visitados[v] = u;
        ordem[prim->contador] = u;
        ordem[prim->contador + 1] = v;
        prim->contador += 2;
        printf("\n\n\nV:%d VISITADOS[V]:%d\n", v, visitados[v]);
        total += minimo;
    }

    prim->custo_minimo = total;
    
    fprintf(arquivo, "%d\n", prim->custo_minimo);

    for (int i = 0; i < prim->contador; i = i + 2)
    {
        fprintf(arquivo, "%d %d\n", ordem[i], ordem[i + 1]);
    }

    fclose(arquivo);
}

int verificar_arquivo_vazio(PRIM *prim, char *entradaArquivo)
{
    FILE *arquivo = fopen(entradaArquivo, "r");
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

void liberar_grafo(PRIM *prim)
{
    int i;
    if (prim->grafo == NULL)
    {
        printf("Erro! Grafo nao existe!\n");
        exit(0);
    }
    for (i = 0; i < prim->vertices; i++)
    {
        free(prim->grafo[i]);
    }
    free(prim->grafo);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        printf("Necessario a entrada.txt e o nome da saida.txt");

    PRIM prim1;
    // inicializa prim com no maximo 200 vertices
    startPrim(&prim1, 200, argv[1]);

    // calcula o custo minimo
    calcular_custo_minimo(&prim1, argv[2]);

    // libera grafo da memoria
    liberar_grafo(&prim1);

    return 0;
}