/*
Implemente o algoritmo de busca em largura para grafos. 
Esse algoritmo deve ter dois parâmetros: um grafo e um número inteiro, sendo este último o vértice raiz da árvore de busca em largura, ou seja, é o vértice a partir de onde deve ser iniciado a exploração do grafo. 
Após, para cada vértice, imprima os respectivos pai e distância.

Input Format
A primeira linha contém o número de vértices seguido pela respectiva matriz de adjacência.
Na última linha deve ser lido um número inteiro que representa um vértice do grafo para iniciar a aplicação do algoritmo de busca em largura.

Constraints
Deve utilizada a estrutura de dados apresentada em sala de aula para matriz de adjacência.

Output Format
Na primeira linha deve ser impressa a seguinte sequência de caracteres: "v d p".
A partir da próxima linha, imprimir o vértice, o pai e a distância.
Para cada vértice que não tem pai, deve ser impresso "-" em sua respectiva linha.
Para cada vértice que não foi possível ser descoberto a partir do "vértice raiz", também deve ser impresso o caractere "-". Por exemplo: se o vértice x não pode ser descoberto, na sua linha deve ser impresso "x - -"
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct Cell Cell;


typedef struct FilaE FilaE;

struct Cell{
    int item;
    Cell *next;
};


struct FilaE{
    Cell *inicio;
    Cell *fim;
};


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->item = key;

    c->next = NULL;

    return c;
}


FilaE* criar_filaE(){
    FilaE *f = (FilaE*) malloc(sizeof(FilaE));
    
    f->inicio = NULL;
    f->fim = NULL;
    
    return f;
}


int filaE_vazia(FilaE* f){
    return (f == NULL) || (f->inicio == NULL);
}


void enfileirar(int key, FilaE* f){
    Cell *aux;

    if (f == NULL)
        f = criar_filaE();

    aux = criar_celula(key);

    if (f->inicio == NULL)
        f->inicio = f->fim = aux;
    else{
        f->fim->next = aux;
        f->fim = f->fim->next;
    }

}


int desenfileirar(FilaE* f){
    Cell *aux;
    int item = INT_MIN;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        f->inicio = aux->next;
        
        item = aux->item;

        free(aux);
    }

    return item;
}


void imprimir_fila(FilaE* f){
    Cell *aux;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        while (aux != NULL){
            printf("%d ", aux->item);
            aux = aux->next;
        }
        
        printf("\n");
    }
}


int liberar_filaE(FilaE* f){
    if (!filaE_vazia(f)){
        while (f->inicio != NULL)
            desenfileirar(f);

        free(f);

        return 1;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct GrafoMA GrafoMA;

struct GrafoMA{
    int V, A;
    int **mat;
    int *cor;
    int *pai;
    int *d;
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
    
    G->d = (int*)malloc(sizeof(int) * v);
    G->pai = (int*)malloc(sizeof(int) * v);
    G->cor = (int*)calloc(v, sizeof(int));
    
    G->mat = iniciar_MA(G->V);

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

void busca_largura(GrafoMA *G, int s)
{
    int u, v;
    
    if(valida_vertice(G, s))
    {
        for(v = 0; v < G->V; v++)
        {
            G->pai[v] = -1;
            G->d[v] = INT_MAX;
        }
        
        G->cor[s] = 1; //cinza
        G->d[s] = 0;
        
        FilaE *f = criar_filaE();
        enfileirar(s, f);
        
        while(!filaE_vazia(f))
        {
            u = desenfileirar(f);
            
            for(v = 0; v < G->V; v++)
            {
                if((G->mat[u][v] != 0) && (G->cor[v] == 0))
                {
                    G->cor[v] = 1;
                    G->pai[v] = u;
                    G->d[v] = G->d[u] + 1;
                    enfileirar(v, f);
                }
            }
            
            G->cor[u] = 2; //preto
        }
        
        printf("v d p\n");
        
        for(v = 0; v < G->V; v++)
        {
            printf("%d ", v);
            
            if(G->d[v] < INT_MAX)
                printf("%d ", G->d[v]);
            else
                printf("- ");
            
            if(G->pai[v] >= 0)
                printf("%d\n", G->pai[v]);
            else
                printf("-\n");
        }
        
        liberar_filaE(f);
    }
}

int main(void)
{
    int V, s;
    
    scanf("%d", &V);
    
    GrafoMA *G = iniciar_grafoMA(V);
    
    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            scanf("%d", &G->mat[i][j]);
        }
    }
    
    scanf("%d", &s);
    
    busca_largura(G, s);
    
    liberarGMA(G);
    
    return 0;
}
