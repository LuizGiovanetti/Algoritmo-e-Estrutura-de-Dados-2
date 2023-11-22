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

typedef struct Cell{
    int key;
    int peso;
    struct Cell *next;
}Cell;

typedef struct FilaE{
    Cell *inicio;
    Cell *fim;
}FilaE;

Cell *criar_celula(int key, int peso)
{
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;
    c->peso = peso;

    c->next = NULL;

    return c;
}

FilaE *criar_filaE()
{
    FilaE *f = (FilaE*) malloc(sizeof(FilaE));
    
    f->inicio = NULL;
    f->fim = NULL;
    
    return f;
}

int filaE_vazia(FilaE* f)
{
    return (f == NULL) || (f->inicio == NULL);
}

void enfileirar(int key, FilaE* f)
{
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

int desenfileirar(FilaE* f)
{
    Cell *aux;
    int item = INT_MIN;

    if (!filaE_vazia(f))
    {
        aux = f->inicio;

        f->inicio = aux->next;
        
        item = aux->key;

        free(aux);
    }

    return item;
}

void imprimir_fila(FilaE* f)
{
    Cell *aux;

    if (!filaE_vazia(f))
    {
        aux = f->inicio;

        while (aux != NULL)
        {
            printf("%d ", aux->key);
            aux = aux->next;
        }
        
        printf("\n");
    }
}

int liberar_filaE(FilaE* f){
    if (!filaE_vazia(f))
    {
        while (f->inicio != NULL)
            desenfileirar(f);

        free(f);

        return 1;
    }

    return 0;
}

typedef struct Lista{
    struct Cell *head;
}Lista;

typedef struct GrafoLA{
    int V;
    int A;
    int *cor;
    int *pai;
    int *d; //descoberta
    Lista **adj;
}GrafoLA;

// Lista encadeada

Lista *criar_lista()
{
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
}

int lista_vazia(Lista *l)
{
    return (l == NULL) || (l->head == NULL);
}

int procurar(int key, Lista *l)
{
    Cell *aux;

    if (l != NULL)
    {
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, Lista *l, int peso)
{
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l))
    {
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key, peso);
    }
    else
    {
        c = criar_celula(key, peso);

        if (l->head->key >= key)
        {
           c->next = l->head;

           l->head = c;
        }
        else
        {
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->key < key))
            {
                auxA = auxP;
                auxP = auxP->next;
            }

            auxA->next = c;
            c->next = auxP;
        }
    }
}

int remover_na_lista(int key, Lista *l, int peso)
{
    Cell *auxA, *auxP;

    if(!lista_vazia(l))
    {
        auxA = l->head;

        if((auxA->key == key) && (auxA->peso == peso))
        {
            l->head = l->head->next;
            free(auxA);
            
            return 1;
        }
        else
        {
            auxP = auxA;

            while(((auxA != NULL) && (key < auxA->key)) || ((key == auxA->key) && (peso < auxA->peso)))
            {
                auxP = auxA;
                auxA = auxA->next;
            }

            if((auxA != NULL) && (auxA->key == key) && (auxA->peso == peso))
            {
                auxP->next = auxA->next;
                free(auxA);
                
                return 1;
            }    
            else
                auxA = NULL;
        }

        if (auxA != NULL)
            free(auxA);

        return 1;
    }

        return 0;
}

void imprimir(Lista *l)
{
    Cell *aux;

    if (!lista_vazia(l))
    {
        aux = l->head;

        while (aux != NULL)
        {
            printf("%d\n", aux->key);

            aux = aux->next;
        }
    }
}

int liberar_lista(Lista *l)
{
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l))
    {

        while(l->head != NULL)
        {
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

// Grafo

static Lista **iniciar_LA(int n)
{
    int i;
    Lista **adj = (Lista**) malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}

GrafoLA *iniciar_grafoLA(int v)
{
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    
    G->d = (int*)malloc(sizeof(int) * v);
    G->pai = (int*)malloc(sizeof(int) * v);
    G->cor = (int*)calloc(v, sizeof(int));
    
    G->adj = iniciar_LA(G->V);

    return G;
}

static int valida_vertice(GrafoLA* G, int v)
{ 
    return (v >= 0) && (v < G->V);
}

int aresta_existeLA(GrafoLA* G, int v1, int v2)
{
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso)
{
    if (!aresta_existeLA(G, v1, v2))
    {
        inserir_na_lista(v2, G->adj[v1], peso);
        inserir_na_lista(v1, G->adj[v2], peso);
        
        G->A++;
    }
}

void remover_arestaLA(GrafoLA* G, int v1, int v2, int peso)
{
    if (aresta_existeLA(G, v1, v2))
    {
        remover_na_lista(v2, G->adj[v1], peso);
        remover_na_lista(v1, G->adj[v2], peso);
        G->A--;

    }
}

void imprimir_arestasLA(GrafoLA* G)
{
    int i;
    Cell *aux;

    if (G != NULL)
        for (i = 0; i < G->V; i++)
        {
            aux = G->adj[i]->head;

            while (aux != NULL)
            {
                printf("(%d, %d)\n", i, aux->key);

                aux = aux->next;
            }

        }
}

void liberarGLA(GrafoLA* G)
{
    if (G != NULL)
    {
        for (int i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G->adj);
        
        free(G->cor);
        free(G->pai);
        free(G->d);
        
        free(G);
    }
}

void troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void heapify(int *v, int n, int raiz)
{
    int maior = raiz;
    int esquerda = (2 * raiz) + 1;
    int direita = (2 * raiz) + 2;

    if((esquerda < n) && (v[esquerda] > v[maior]))
        maior = esquerda;
    
    if((direita < n) && (v[direita] > v[maior]))
        maior = direita;
    
    if(maior != raiz)
    {
        troca(&v[raiz], &v[maior]);
        heapify(v, n, maior);
    }
}

void heapSort(int *v, int n)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        troca(&v[0], &v[i]);
        heapify(v, i, 0);
    }
}

int main(void)
{
    int V, qntA, a1, a2, peso;
    
    scanf("%d", &V);
    scanf("%d", &qntA); //quantidade de arestas
    
    GrafoLA *G = iniciar_grafoLA(V);

    for(int i = 0; i < V; i++)
    {
        scanf("%d %d %d", &a1, &a2, &peso);
    }
    
    liberarGLA(G);
    
    return 0;
}
