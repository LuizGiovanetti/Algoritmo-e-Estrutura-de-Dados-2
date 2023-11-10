/*
Considere n itens a serem levados para uma viagem, dentro de uma mochila de capacidade b. 
Cada item x_j tem um peso a_j e um valor c_j. Implemente uma função, utilizando programação dinâmica, que calcule o valor máximo de objetos que podem ser carregados dentro da mochila.

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

#define max(a, b) a > b ? a : b

int mochila_pb(int *peso, int *custo, int qnt_item, int capacidade)
{
    int memoria[capacidade + 1][qnt_item + 1];
    
    for(int i = 0; i <= capacidade; i++)
        memoria[i][0] = 0;
    
    for(int j = 1; j <= qnt_item; j++)
    {
        for(int i = 0; i <= capacidade; i++)
        {
            if(i - peso[j - 1] < 0)
                memoria[i][j] = memoria[i][j - 1];
            else
                memoria[i][j] = max(memoria[i][j - 1], custo[j - 1] + memoria[i - peso[j - 1]][j - 1]);
        }
    }
    return memoria[capacidade][qnt_item];
}

int main(void)
{
    int qnt_item, capacidade;
    int *peso, *custo;
    
    scanf("%d %d", &capacidade, &qnt_item);
    
    peso = (int*)malloc(sizeof(int) * qnt_item);
    custo = (int*)malloc(sizeof(int) * qnt_item);
    
    for(int i = 0; i < qnt_item; i++)
        scanf("%d %d", &peso[i], &custo[i]);
    
    printf("%d", mochila_pb(peso, custo, qnt_item, capacidade));
    
    free(peso);
    free(custo);
       
    return 0;
}
