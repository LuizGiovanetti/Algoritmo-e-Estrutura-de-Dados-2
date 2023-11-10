/*
Implemente uma função que receba uma árvore binária de busca e um número p, que representa um valor de profundida. A função deverá imprimir todos os nós de profundidade p.

Input Format
Na primeira linha, deve ser lido um número inteiro p referente a um valor de profundidade.
Na segunda linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca.
Em seguida, em cada linha seguinte deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Output Format
Em uma única linha, devem ser impressos os nós de profundidade p.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node Node;

struct Node{
    int item;
    struct Node *left;
    struct Node *right;
};


Node *criar(int item)
{
    Node *tree = (Node*)malloc(sizeof(Node));
    
    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;
    
    return tree;
}
/*
Node* pesquisar(int item, Node* tree){
    if (tree != NULL){
        if (item == tree->item)
            return tree;
        else if (item < tree->item)
            return pesquisar(item, tree->left);
        else
            return pesquisar(item, tree->right);
    }else
        return NULL;
}


int min(Node* tree){
    Node* aux = tree;
    
    if (aux != NULL){
        while (aux->left != NULL)
            aux = aux->left;
        
        return aux->item;
    }
    
    return INT_MIN;
}


int max(Node* tree){
    Node* aux = tree;
    
    if (aux != NULL){
        while (aux->right != NULL)
            aux = aux->right;
        
        return aux->item;
    }
    
    return INT_MAX;
}

Node* remover(int item, Node* tree){
    Node *aux, *auxP, *auxF;
    
    if (tree != NULL){
        if (item < tree->item)
            tree->left = remover(item, tree->left);
        else if (item > tree->item)
            tree->right = remover(item, tree->right);
        else{
            aux = tree;
            
            if (aux->left == NULL)
                tree = tree->right;
            else if (aux->right == NULL)
                tree = tree->left;
            else{
                auxP = aux->right;
                auxF = auxP;
                
                while (auxF->left != NULL){
                    auxP = auxF;
                    auxF = auxF->left;
                }
                
                if (auxP != auxF){
                    auxP->left = auxF->right;
                    auxF->left = aux->left;
                }
                
                auxF->right = aux->right;
                
                tree = auxF;
            }
            
            free(aux);
        }
    }
    
    return tree;
}


void imprimirInfix(Node* tree){
    if (tree != NULL){
        imprimirInfix(tree->left);
        printf("\n%i", tree->item);
        imprimirInfix(tree->right);
    }
}


void imprimirPrefix(Node* tree){
    if (tree != NULL){
        printf("%i ", tree->item);
        imprimirPrefix(tree->left);
        imprimirPrefix(tree->right);
    }
}


void imprimirPosfix(Node* tree){
    if (tree != NULL){
        imprimirPosfix(tree->left);
        imprimirPosfix(tree->right);
        printf("\n%i", tree->item);
    }
}


void liberar_arvore(Node* tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}*/

Node *inserir(Node *raiz, int item)
{
    if(raiz == NULL)
        return criar(item);

    if(item < raiz->item)
        raiz->left = inserir(raiz->left, item);
    else if(item > raiz->item)
        raiz->right = inserir(raiz->right, item);

    return raiz;
}

void imprimir_no_p(Node *raiz, int nivel, int profundidade)
{
    if(raiz != NULL)
    { 
        if(nivel == profundidade)
            printf("%d ", raiz->item);

        imprimir_no_p(raiz->left, nivel + 1, profundidade);
        imprimir_no_p(raiz->right, nivel + 1, profundidade);
    }
}

int main(void)
{
    int p, no, chave;
    scanf("%d", &p); 
    scanf("%d", &no); 

    Node *raiz = NULL;

    for(int i = 0; i < no; i++)
    {
        scanf("%d", &chave);
        raiz = inserir(raiz, chave);
    }

    imprimir_no_p(raiz, 0, p);

    return 0;
}
