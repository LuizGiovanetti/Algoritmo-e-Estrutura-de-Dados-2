/*
Implemente uma função (verificaAdjacencia) para verificar se 2 vértices  e  quaisquer são adjacentes em grafo representado por matriz de adjacência (direcionado ou não-dorecionado).
Para a implementação da solução, considere a estrutura abaixo:

typedef struct GrafoMA GrafoMA;

struct GrafoMA{
   int V; // número de vértices
   int A; // número de arestas
   int **mat;
};

Obs.: para a implementação da solução, pode ser utilizado o código (TAD) apresentado em aula.

Input Format
A primeira linha contém o número de vértices seguido pela respectiva matriz de adjacência. A linha seguinte faz n sucessivas chamadas da função verificaAdjacencia passando como parâmetro os índices de 2 vértices.

Output Format
A saída deve imprimir sim ou não para cada chamada da função verificaAdjacencia
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct GrafoMA GrafoMA;

struct GrafoMA{
   int V, A;
   int **mat;
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

    return G;
}


int aresta_existe(GrafoMA* G, int v1, int v2){
    return (G != NULL) && valida_vertice(G, v1) && valida_vertice(G, v2) && (G->mat[v1][v2] != 0);
}


void inserir_aresta(GrafoMA* G, int v1, int v2){
    if (!aresta_existe(G, v1, v2)){
        G->mat[v1][v2] = 1; //grafo direcionado
        //G->mat[v1][v2] = G->mat[v2][v1] = 1; nao direcionado, relacao simetrica
            
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

void verificar_adjacencia(GrafoMA *G, int v1, int v2)
{
    if(aresta_existe(G, v1, v2))
    {
        printf("sim\n");
    } 
    else
    {
        printf("nao\n");
    }    
}

void ler_grafo(GrafoMA *G)
{
    if(G != NULL)
    {
        int item;
        
        for(int i = 0; i < G->V; i++)
        {
            for(int j = 0; j < G->V; j++)
            {
                scanf("%d", &item);
                
                if(item != 0)
                    inserir_aresta(G, i, j);
            }
        }
    }
}

int main(void)
{
    int n, m, v1, v2;
    GrafoMA *G;
    
    scanf("%d", &n);
    
    G = iniciar_grafoMA(n);
    
    ler_grafo(G);
    
    scanf("%d", &m);
    
    while(m > 0)
    {
        m--;
        scanf("%d %d", &v1, &v2);
        verificar_adjacencia(G, v1, v2);
    }
    
    return 0;
}
