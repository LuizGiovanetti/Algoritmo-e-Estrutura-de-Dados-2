/*
Em dias de folga, um grupo de treinadores pokemon deixam seus monstrinhos livres de suas pokebolas. 
Em alguns casos, cada pokemon devem retornar a uma pokebola o mais rápido possível, ou seja, eles se deslocam para a pokebola mais próxima. 
Para simplificar a representação desse problema, dados N pokemons e N pokebolas, onde cada pokebola comporta apenas um pokemon. 
Suponha que cada pokemon desloque em linha reta para chegar na pokebola e o deslocamento de uma posição x para x + 1 leva 1 segundo. 
Por exemplo, se um pokemon está na posição 2 e a pokebola na posição 7, então o pokemon precisa de 5 segundos para chegar na pokebola. 
Caso a posição do pokemon e da pokebola sejam iguais, não é necessário fazer o deslocamento. 
Implemente uma função, utilizando a estratégia gulosa, para o retorno dos pokemons às pokebolas de forma em que o tempo para último pokemon entrar na pokebola seja minimizado.

Input Format
Na primeira linha deve ser lido um número inteiro N.
Na segunda linha deve ser lido a posição de cada um dos N pokemons.
Na terceira linha deve ser lido a posição de cada uma das N pokebolas.

Output Format
Imprimir o tempo mínimo para que todos os pokemons estejam na pokebola.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void quicksort(int *v, int esq, int dir)
{
    int i = esq;
    int j = dir;
    int pivo = v[(esq + dir) / 2];
    int aux;
    
    do{
        while(v[i] < pivo)
            i++;
        while(v[j] > pivo)
            j--;
        
        if(i <= j)
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }while(i <= j);
    
    if(j > esq)
        quicksort(v, esq, j);
    
    if(i < dir)
        quicksort(v, i, dir);
}

int min(int *pokemons, int *pokebolas, int n)
{
    quicksort(pokemons, 0, n - 1);
    quicksort(pokebolas, 0, n - 1);

    int max = 0;
    
    for(int i = 0; i < n; i++)
    {
        int distancia = abs(pokemons[i] - pokebolas[i]);
        if(distancia > max)
            max = distancia;
    }

    return max;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    int *pokemon = (int*)malloc(sizeof(int) * n);
    int *pokeball = (int*)malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++)
        scanf("%d", &pokemon[i]);

    for(int i = 0; i < n; i++)
        scanf("%d", &pokeball[i]);

    
    printf("%d\n", min(pokemon, pokeball, n));

    free(pokemon);
    free(pokeball);

    return 0;
}

