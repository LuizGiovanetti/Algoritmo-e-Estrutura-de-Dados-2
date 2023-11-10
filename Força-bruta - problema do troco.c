/*
Implemente a solução do problema do troco (conforme apresentado em sala de aula) utilizando a estratégia de força-bruta.

Input Format
A primeira linha deve conter o valor do troco. A segunda linha deve conter a quantidade de moedas, que representará o tamanho do vetor que deverá ser lido logo em sequência.

Output Format
Sequência de moedas que foram retornados como troco.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) (a < b) ? a : b

static int qnt_troco_fb(int *v, int n, int troco, int valor)
{
    if(valor >= n)
    {
        if(troco == 0)
            return 0;
        else
            return INT_MAX;  
    }
    
    int anterior = qnt_troco_fb(v, n, troco, valor + 1);
    int atual = INT_MAX;
    
    if(troco >= v[valor])
    {
        int t = qnt_troco_fb(v, n, troco - v[valor], valor);
        
        if(t != atual)
            atual = 1 + t;
    }

    return min(anterior, atual);
}

int qnt_troco(int *v, int n, int troco)
{
    return qnt_troco_fb(v, n, troco, 0);
}

int main(void)
{
    int troco, n;
    
    scanf("%d", &troco);
    
    scanf("%d", &n);
    
    int *v = malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    
    printf("%d", qnt_troco(v, n, troco));
    
    free(v);
    
    return 0;
}
