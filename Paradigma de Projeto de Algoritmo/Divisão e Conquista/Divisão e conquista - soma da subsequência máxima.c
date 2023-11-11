/*
Seja um arranjo composto por números inteiros, podendo ser positivos e/ou negativos. A subsequência máxima é aquela que tem o maior valor de soma entre todos os os seus elementos.
Por exemplo, dada a sequência a seguir: [10, -3, -30, 20, -3, -16, -23, 15, 23, -7, 12, -4, -25, 6].
A subsequência máxima é [15, 23, -7, 12], pois, de todas as subsequências possíveis, essa foi a que registrou a maior soma entre os seus elementos (43).
Implemente, utilizando a estratégia divisão-e-conquista, uma função que retorne o somatório da subsequência máxima.

Input Format
Na primeira linha deve ser lido um número inteiro (n).
Na segunda linha deve ser lida um vetor de números inteiros de tamanho n.

Output Format
Somatório da subsequência máxima.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define max(a, b) (a > b) ? a : b

static int maior_soma_sub_dc(int *v, int ini, int fim)
{
    if(ini == fim)
        return v[ini];
    
    int meio = (ini + fim) / 2;

    int esq = INT_MIN;
    int soma = 0;
    
    for(int i = meio; i >= ini; i--)
    {
        soma += v[i];
        
        if(soma > esq)
            esq = soma;
    }

    int dir = INT_MIN;
    soma = 0;
    
    for(int i = meio + 1; i <= fim; i++)
    {
        soma += v[i];
        
        if (soma > dir)
            dir = soma;
    }

    int maxi = max(max(esq, dir), esq + dir);

    int max_esq = maior_soma_sub_dc(v, ini, meio);
    int max_dir = maior_soma_sub_dc(v, meio + 1, fim);

    return max(maxi, max(max_esq, max_dir));
}

int maior_soma_sub(int *v, int n)
{
    return maior_soma_sub_dc(v, 0, n);
}

int main(void)
{
    int n;
    
    scanf("%d", &n);
    
    int *v = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    
    printf("%d", maior_soma_sub(v, n - 1));
       
    return 0;
}
