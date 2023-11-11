/*
Implemente uma função para verificar se um grafo representado por listas de ajacência é k-regular. 
Se o grafo for k-regular, a função deve retornar o valor de k. Se o grafo não for k-regular, a função deve retornar 0.

Para a implementação, considere o grafo representado por lista de adjacências, conforme as estruturas apresentadas abaixo:

typedef struct {
   int V; // número de vértices
   int A; // número de arestas
   Lista **adj; // lista de adjacências
}GrafoLA;

typedef struct Cell Cell;

struct Cell{
    int key;
    Cell *next;
};


typedef struct{
    Cell *head;
}Lista;

Input Format
A primeira linha contém o número de vértices seguida pela respectiva lista de adjacência. 
Cada uma das seguintes linhas será referente a um vértice v_i, onde os vértices adjacentes devem ser lidos. 
Para cada linha, enquanto o número "-1" (menos um) não for lido, um vértice adjacente deve ser lido. 
Por exemplo, suponha que o i-ésimo vértice seja adjacente aos vértices 2 e 5, então a leitura deve seguir o seguinte formato:

2 5 -1

Caso o vértice não tenha adjacentes, basta ler -1 (menos 1). Exemplo:

-1

Constraints
O não uso do TAD de lista de adjacências acerratará em 75% de desconto da nota, já que a versão com matriz de adjacências é implementada em aula.

Output Format
Imprimir "grafo k-regular com k=valor" caso o grafo seja regular ou imprimir "grafo nao k-regular", caso contrário.
Os TADs disponíveis para a resolução de exercícios são para grafos não direcionados. Nesse caso, basta mudar as funções de inserção e remoção de arestas.
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
        G->mat[v1][v2] = 1;
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

static int soma_linha(int *v, int n)
{
    int aux = 0;
    
    for(int i = 0; i < n; i++)
        aux += v[i];
    
    return aux;
}

int k_regular(GrafoMA *G)
{
    int grau = 0;
    int k_reg = 1;
    
    if(G != NULL)
    {
        grau = soma_linha(G->mat[0], G->V);
        
        for(int i = 0; (i < G->V) && k_reg; i++)
        {
            if(grau != soma_linha(G->mat[i],G->V))
                k_reg = 0;
        }
    }
    
    if((k_reg) && (grau != 0))
    {
        printf("grafo k-regular com k=%d", grau);
        
        return grau;
    }
    else
    {
        printf("grafo nao k-regular");
    }
    
    return 0;
}

int main(void)
{
    int n;
    GrafoMA *G;
    
    scanf("%d", &n);
    
    G = iniciar_grafoMA(n);
    
    for(int i = 0; i < n; i++)
    {
        int v2 = 0;
        
        while(v2 != -1)
        {
            scanf("%d", &v2);
            
            if(v2 != -1)
                inserir_aresta(G, i, v2);
        }
    }
    
    k_regular(G);
      
    return 0;
}
