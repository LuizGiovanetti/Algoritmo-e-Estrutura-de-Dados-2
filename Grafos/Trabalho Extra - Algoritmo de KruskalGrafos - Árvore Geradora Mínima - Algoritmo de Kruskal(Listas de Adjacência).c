/*
Implemente o algoritmo de Kruskal. 
A função deve receber um grafo representado por uma lista de adjacência e construir uma árvore geradora mínima, que deve ser construída a partir do vértice "0".

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

A primeira linha contém o número de vértices. A segunda linha contém a quantidade de arestas (A). 
Para cada uma das "A" próximas linhas devem der lidos dois números inteiros. sendo os 2 primeiros, a aresta, e o último, o peso da aresta.

Constraints
O não uso do TAD de lista de adjacências acerratará em 75% de desconto da nota, já que a versão com matriz de adjacências é implementada em aula.

Output Format
Imprimir a árvore geradora mínima. Cada linha deve ser impressa no seguinte formato: "v_i: pai[v_i]".
Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-" (traço/sinal de menos). 
Como o algoritmo deve ser iniciada a partir do vértice "0", então a primeira linha sempre será "0: -"
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;
typedef struct Cell Cell;
typedef struct FilaE FilaE;

struct Cell{
    int key;
    struct Cell *next;
};


struct FilaE{
    Cell *inicio;
    Cell *fim;
};

Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;

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
        
        item = aux->key;

        free(aux);
    }

    return item;
}

struct Lista{
    struct Cell *head;
};

struct GrafoLA{
    int V;
    int A;
    int *nafila;
    int *pai;
    int *key;
    
    Lista **adj;
    Lista **peso;
};

Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
}

int procurar(int key, Lista *l){
    Cell *aux = NULL;

    if (l != NULL){
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, Lista *l)
{
    Cell *aux, *novo;
    
    if(l == NULL)
    {
        l = criar_lista();
    }
    if(lista_vazia(l))
    {
        aux = criar_celula(key);
        aux->next = l->head;
        l->head = aux;
    }
    else
    {
        aux = l->head;
        while(aux->next != NULL)
        {
            aux = aux->next;
        }
        novo=criar_celula(key);
        aux->next=novo;
    }
}

int remover_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;

    if (!lista_vazia(l)){
        auxA = l->head;

        if(auxA->key == key)
            l->head = l->head->next;
        else{
            auxP = auxA;

            while((auxA != NULL) && (key < auxA->key)){
                auxP = auxA;
                auxA = auxA->next;
            }

            if (auxA->key == key)
                auxP->next = auxA->next;
            else
                auxA = NULL;
        }

        if (auxA != NULL)
            free(auxA);

        return 1;
    }

        return 0;
}

void imprimir(Lista *l){
    Cell *aux;

    if (!lista_vazia(l)){
        aux = l->head;

        while (aux != NULL){
            printf("%d\n", aux->key);

            aux = aux->next;
        }
    }
}


int liberar_lista(Lista *l){
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)){

        while(l->head != NULL){
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

static Lista** iniciar_LA(int n){
    int i;
    Lista **adj = malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}

GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    
    G->key = malloc(sizeof(int) * v);
    G->pai = malloc(sizeof(int) * v);
    G->nafila = calloc(v, sizeof(int));
    
    G->adj = iniciar_LA(G->V);
    G->peso = iniciar_LA(G->V);

    return G;
}

int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso)
{
    if(!aresta_existeLA(G, v1, v2))
    {
        inserir_na_lista(v2, G->adj[v1]);
        inserir_na_lista(peso, G->peso[v1]);
        G->A++;
    }
}

void remover_arestaLA(GrafoLA* G, int v1, int v2){
    if(aresta_existeLA(G, v1, v2)){
        remover_na_lista(v2, G->adj[v1]);
        remover_na_lista(v1, G->adj[v2]);
        G->A--;

    }
}

void imprimir_arestasLA(GrafoLA* G){
    int i;
    Cell *aux;

    if (G != NULL)
        for (i = 0; i < G->V; i++){
            aux = G->adj[i]->head;

            while (aux != NULL){
                printf("(%d, %d)\n", i, aux->key);

                aux = aux->next;
            }

        }
}

void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}

int encontrar_conj(int *pai, int key)
{
    if(pai[key] == -1)
        return key;

    return encontrar_conj(pai, pai[key]);
}

void unir_conj(int *pai, int u, int v)
{
    int raizU = encontrar_conj(pai, u);
    int raizV = encontrar_conj(pai, v);

    pai[raizU] = raizV;
}

void criar_conj(int *pai, int n)
{
    for(int i = 0; i < n; i++)
        pai[i] = -1;
}

void add_arvore(GrafoLA* G)
{
    for(int i = 0; i < G->V; i++) 
    {
        Cell *aux = G->adj[i]->head;

        while(aux != NULL) 
        {
            int u = i;
            int v = aux->key;

            aux = aux->next;

            if(encontrar_conj(G->pai, u) != encontrar_conj(G->pai, v)) 
                unir_conj(G->pai, u, v);
        }
    }
}

void alg_kruskal(GrafoLA *G)
{
    criar_conj(G->pai, G->V);

    add_arvore(G);

    for(int v = 0; v < G->V; v++)
    {
        printf("%d: ", v);
            
        if(G->pai[v] >= 0)
            printf("%d\n", G->pai[v]);
        else
            printf("-\n");
    }
}

int main(void)
{
    int V, A, a1, a2, peso;
    
    scanf("%d", &V);
    scanf("%d", &A);
    
    GrafoLA *G = iniciar_grafoLA(V);
    
    for(int i = 0; i < A; i++)
    {
        scanf("%d %d %d", &a1, &a2, &peso);
        inserir_arestaLA(G, a1, a2, peso);
    }
    
    alg_kruskal(G);
    
    liberarGLA(G);
    
    return 0;
}
