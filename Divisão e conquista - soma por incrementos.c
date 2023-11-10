/*
A soma de dois números inteiros pode ser feita através de sucessivos incrementos, por exemplo, 7 + 4 = (++(++(++(++7)))) = 11. 
Implemente uma função, utilizando a estratégia de divisão e conquista, que calcule a soma entre dois números naturais, através de incrementos, utilizando recursão.

Input Format
Na primeira linha deve ser lido um número inteiro N referente a quantidade de leituras de entradas.
Para cada uma das N próximas linhas, ler dois números inteiros (a e b)

Output Format
Em cada uma das N linhas, imprimir o resultado da soma dos respectivos números inteiros.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

static int soma_inc_dc(int a, int ini, int fim)
{
    if(ini == fim)
        return a;
    
    int meio = (ini + fim) / 2;

    int soma1 = soma_inc_dc(a, ini, meio);
    int soma2 = soma_inc_dc(1, meio + 1, fim);

    return soma1 + soma2;
}

int soma_inc(int a, int b)
{
    if(a == 0)
        return b;
    if(b == 0)
        return a;

    return soma_inc_dc(a, 0, b);
}

int main(void)
{
    int n, a, b;
    
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &a, &b);
        printf("%d\n", soma_inc(a, b));
    }
    
    return 0;
}
