/*
Considere n itens a serem levados para uma viagem, dentro de uma mochila de capacidade b. 
Cada item x_j tem um peso a_j e um valor c_j. Implemente uma função, utilizando força-bruta, que calcule o valor máximo de objetos que podem ser carregados dentro da mochila.

Input Format
Na primeira linha deve ser lido um número inteiro que represente a capacidade da mochila.
Na próxima linha, deve ser lido um outro número (N) referente à quantidade de objetos disponíveis.
Em seguida, nas N linhas restantes devem ser lidos o peso e o valor (logo em sequência) de cada objeto.

Output Format
O valor máximo de objetos que a mochila possa carregar.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

static int mochila_fb(int *custo, int *peso, int n, int capacidade, int item, int max)
{
    int c1, c2;
    
    if(item >= n)
    {
        if(capacidade < 0)
            return 0;
        else
            return max;
    }
    else
    {
        c1 = mochila_fb(custo, peso, n, capacidade, item + 1, max);
        c2 = mochila_fb(custo, peso, n, capacidade - peso[item], item + 1, max + custo[item]);
        
        return (c1 > c2) ? c1 : c2;
    }
}

int mochila(int *custo, int *peso, int n, int capacidade)
{
    return mochila_fb(custo, peso, n, capacidade, 0, 0);
}

int main(void)
{
    int n, capacidade;
    int *peso, *custo;
    
    scanf("%d", &capacidade);
    scanf("%d", &n);
    
    custo = (int*)malloc(sizeof(int) * n);
    peso = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &peso[i], &custo[i]);
    }
    
    printf("%d", mochila(custo, peso, n, capacidade));
    
    free(custo);
    free(peso);
      
    return 0;
}
