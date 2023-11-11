/*
Implemente uma função que receba uma árvore binária de busca. A função deverá trocar a subárvore esquerda pela direita de todos os nós da árvore.
Em seguida, imprima o percurso simétrico (infixo) da árvore.

Input Format
Na primeira linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca. 
Em seguida, em cada linha deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Output Format
Imprimir o valor da chave de cada nó folha em uma única linha.
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


Node* criar(int item){
    Node * tree = (Node *) malloc(sizeof(Node));
    
    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;
        
    return tree;
}


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



Node* inserir(int item, Node* tree){
    if (tree == NULL)
        tree = criar(item);
    else if (item < tree->item)
        tree->left = inserir(item, tree->left);
    else if (item > tree->item)
        tree->right = inserir(item, tree->right);
        
    return tree;
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
        printf("%i ", tree->item);
        imprimirInfix(tree->right);
    }
}


void imprimirPrefix(Node* tree){
    if (tree != NULL){
        printf("\n%i", tree->item);
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

void espelhar(Node *tree)
{
    if(tree != NULL)
    {
        espelhar(tree->left);
        espelhar(tree->right);
        Node *aux = tree->left;
        tree->left = tree->right;
        tree->right = aux;
    }
}

void espelhar2(Node **tree)
{
    if(*tree != NULL)
    {
        espelhar2(&(*tree)->left);
        espelhar2(&(*tree)->right);
        Node *aux = (*tree)->left;
        (*tree)->left = (*tree)->right;
        (*tree)->right = aux;
    }
}

Node *espelhar3(Node *tree)
{
    if(tree != NULL)
    {
        tree->left = espelhar3(tree->left);
        tree->right = espelhar3(tree->right);
        Node *aux = tree->left;
        tree->left = tree->right;
        tree->right = aux;
    }
    
    return tree;
}

void liberar_arvore(Node* tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}

int main(void)
{
    int n, item;
    Node *tree = NULL;
    
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &item);
        tree = inserir(item, tree);
    }
    
    espelhar2(&tree);
    
    imprimirInfix(tree);
    
    liberar_arvore(tree);
    
    return 0;
}
