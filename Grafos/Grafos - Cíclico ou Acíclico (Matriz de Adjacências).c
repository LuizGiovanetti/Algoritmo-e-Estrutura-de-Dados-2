/*
Implemente uma função para verificar se um grafo é cíclico ou acíclico

Input Format
A primeira linha contém o número de vértices seguido pela respectiva matriz de adjacência.

Constraints
Deve utilizada a estrutura de dados apresentada em sala de aula para matriz de adjacência.

Output Format
imprimir ciclico ou aciclico.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct GrafoMA GrafoMA;

struct GrafoMA{
    int V, A;
    int **mat;
    int *pai, *cor, *d, *f;
};

static int** iniciar_MA(int n){
    int i;
    int **mat = (int**) malloc(n * sizeof(int*));

    for (i = 0; i < n; i++)
        mat[i] = (int*) calloc(n, sizeof(int));

    return mat;
}


static int valida_vertice(GrafoMA* G, int v){
    return (v >= 0) && (v < G->V);
}


GrafoMA* iniciar_grafoMA(int v){
    GrafoMA* G = (GrafoMA*) malloc(sizeof(GrafoMA));

    G->V = v;
    G->A = 0;
    G->mat = iniciar_MA(G->V);
    
    G->cor = malloc(sizeof(int) * v);
    G->pai = malloc(sizeof(int) * v);
    G->d = malloc(sizeof(int) * v); //descoberta
    G->f = malloc(sizeof(int) * v); //finalizacao
    

    return G;
}


int aresta_existe(GrafoMA* G, int v1, int v2){
    return (G != NULL) && valida_vertice(G, v1) && valida_vertice(G, v2) && (G->mat[v1][v2] != 0);
}


void inserir_aresta(GrafoMA* G, int v1, int v2){
    if (!aresta_existe(G, v1, v2)){
        G->mat[v1][v2] = G->mat[v2][v1] = 1;
        G->A++;
    }
}

void remover_aresta(GrafoMA* G, int v1, int v2){
    if (aresta_existe(G, v1, v2)){
        G->mat[v2][v1] = G->mat[v1][v2] = 0;
        G->A--;
    }
}

void imprimir_arestas(GrafoMA* G){
    int i, j;

    for (i = 1; i < G->V; i++)
        for (j = 0; j < i; j++)
            if (G->mat[i][j] == 1)
                printf("(%d, %d)\n", i, j);
}


void liberarGMA(GrafoMA* G){
    if (G != NULL){
        free(G->mat);
        free(G);
    }
}

int busca_aresta_retorno(GrafoMA *G, int u)
{
    int b = 0; //verificar a aresta de retorno
    
    G->cor[u] = 1; //cinza
    
    for(int v = 0; (v < G->V) && (b == 0); v++)
    {
        if(G->mat[u][v] != 0)
        {
            if(G->cor[v] == 0) //se for branco
            {
                G->pai[v] = u;
                b = busca_aresta_retorno(G, v);
            }
            else if((G->pai[u] != v) && (G->cor[v] == 1))
                b = 1;
        }
    }
    
    G->cor[u] = 2; //preta
    
    return b;
}

int grafo_ciclico(GrafoMA *G)
{
    int b = 0;
    
    for(int u = 0; u < G->V; u++)
    {
        G->cor[u] = 0;
        G->pai[0] = -1;
    }
    
    for(int u = 0; (u < G->V) && (b == 0); u++)
        if(G->cor[u] == 0)
            b = busca_aresta_retorno(G, u);

    return b;
}

int main(void)
{
    int V;
    
    scanf("%d", &V);
    
    GrafoMA *G = iniciar_grafoMA(V);
    
    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            scanf("%d", &G->mat[i][j]);
        }
    }
    
    if(grafo_ciclico(G))
        printf("ciclico");
    else
        printf("aciclico");
    
    return 0;
}
