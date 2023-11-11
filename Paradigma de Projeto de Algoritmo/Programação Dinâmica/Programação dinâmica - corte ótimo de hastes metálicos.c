/*
Uma empresa compra hastes de aço longas e as corta em pedaços mais curtos para revenda. 
Para cada polegada i de comprimento há um preço Pi. 
Desse modo há uma tabela de preços para hastes de diversos tamanhos em polegadas: i = 1, 2, ..., n. 
Objetivo é maximizar o ganho em cima de uma haste cortada em vários pedaços.

Por exemplo, considere a tabela de preços abaixo:
Comprimento: 1|2|3|4|5 |6 |7 |8 |9 |10
Preço: 1|5|8|9|10|17|17|20|24|30
Para uma haste de tamanho igual a 4, de acordo com a tabela acima, o maior preço que pode ser alcançado é através da sua divisão em duas partes de 2 polegadas, onde o preço total seria 10.
Implemente, utilizando programação dinâmica, a solução para o problema acima.
Essa função deverá retornar o valor máximo que pode ser obtido a partir da divisão de uma haste de x polegadas, que não pode ser maior que o tamanho da tabela 
(por exemplo, se a tabela tem tamanho 10, a haste não pode ter tamanho maior que 10).

Input Format
Na primeira linha, deve ser lido o tamanho da haste a ser cortado.
Na segunda linha deve ser lido um número inteiro representando o tamanho da tabela de preços (n).
Para cada uma das n próximas linhas, deve ser lido um número inteiro: preço do (i + 1)-ésimo corte.
Observação: é importante ressaltar que, na leitura do tamanho da tabela, a ordem de leitura do tamanho dos cortes é crescente e a diferença de tamanho entre os cortes catalogados é um. 
Por exemplo, se a tabela tiver tamanho 5, então haverá preços para tamanhos de cortes de: 1, 2, 3, 4 e 5.

Output Format
Deve ser impresso o valor máximo que pode ser obtido pela divisão de uma haste.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define max(a, b) a > b ? a : b

int maior_preco(int *precos, int tam_haste)
{
    int q; //q: maior valor temporario
    int memoria[tam_haste + 1];
    memoria[0] = 0;
    
    for(int i = 1; i <= tam_haste; i++)
    {
        q = INT_MIN;
        for(int j = 0; j < i; j++)
            q = max(q, precos[j] + memoria[i - j - 1]);
        
        memoria[i] = q;
    }
    
    return memoria[tam_haste];
}

int main(void)
{
    int tam_haste, n;
    int *precos;
    
    scanf("%d %d", &tam_haste, &n);
    
    precos = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++)
        scanf("%d", &precos[i]);
    
    printf("%d", maior_preco(precos, tam_haste));
    
    free(precos);
        
    return 0;
}
