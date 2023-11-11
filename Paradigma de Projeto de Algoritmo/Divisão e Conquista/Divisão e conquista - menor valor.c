/*
Implemente uma função que procure, utilizando divisão e conquista, o menor elemento em um vetor de números inteiros. A função deverá retornar o menor elemento.

Input Format
Na primeira linha deve ser lido o tamanho do vetor.
Na segunda linha deve ser lido o conteúdo do vetor.

Output Format
Imprimir a posição do menor elemento.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define min(a, b) (a < b) ? a : b;

int menorDQ(int *vet, int ini, int fim)
{
    if(fim - ini <= 1)
    {
        return min(vet[ini], vet[fim]);
    }
    else
    {
        int meio = (ini + fim) / 2;
        int esquerda = menorDQ(vet, ini, meio);
        int direita = menorDQ(vet, meio + 1, fim);
        
        return min(esquerda, direita)
    }
}

int main(void)
{
    int n, *vet;
    
    scanf("%d", &n);
    
    vet = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++)
        scanf("%d", &vet[i]);
    
    printf("%d", menorDQ(vet, 0, n - 1));
    
    free(vet);
    
    return 0;
}
