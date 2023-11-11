/*
Bilbo teve uma uma missão de levar um anel mágico para ser destruído em um vulcão. Nessa jornada, Bilbo deve percorrer um campo cheio de obstáculos. 
Esse campo pode ser representado por uma matriz de números inteiros (M), onde cada elemento representa um custo para ser acessado a partir dos elementos na vizinhança. 
Por exemplo, se M[3][3] = 5, então o custo para o deslocamento de M[2][3], M[3][4], M[4][3], ou M[3][2] para M[3][3] é 5. O Bilbo mora na posição M[0][0], que tem custo zero, pois é de sua casa que ele iniciará a aventura. 
O vulcão fica em um lugar distante da casa de Bilbo e pelo que se sabe, está localizado na posição M[l - 1][c - 1], onde l é o número de linhas e c é o número de colunas da matriz. 
Bilbo é um cara preguiçoso e a partir do lugar que ele se enconcontra, vai para o lugar menos custoso, mas ele é persistente e não reconsidera a sua decisão. 
Implemente uma função gulosa que calcule o custo do caminho do Bilbo até o vulcão.

Input Format

A primeira linha contém a quantidade de linhas (l) e de colunas (c) da matriz. A partir da próxima linha, deve ser lida uma matriz l x c de números inteiros.

Constraints
Na matriz não deve ser permitido delocamento pela diagonal. Por exemplo, se Bilbo estiver na posição M[3][3], ele não pode ir para M[2][2], M[2][4], M[4][4] ou M[4][2] a partir de M[3][3].
Em outras palavras, apenas é possível deslocar para cima, baixo, esquerda ou direita.

Output Format
O custo total do deslocamento de M[0][0] até M[l - 1][c - 1] utilizando solução gulosa. Caso M[l - 1][c - 1] não seja alcançado, imprimir "sem solucao".
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int moveX[] = {-1, 0, 1, 0};
int moveY[] = {0, -1, 0, 1};

int proximo_passo(int **mat, int l, int c, int *l_proximo, int *c_proximo)
{
    int menor = INT_MAX;
    int l_melhor = *l_proximo; 
    int c_melhor = *c_proximo;
    int l_atual, c_atual;
    
    for(int i = 0; i < 4; i++)
    {
        l_atual = *l_proximo + moveX[i];
        c_atual = *c_proximo + moveY[i];
        
        if((l_atual >= 0) && (l_atual < l) && (c_atual >= 0) && (c_atual < c) && (menor > mat[l_atual][c_atual]))
        {
            l_melhor = l_atual;
            c_melhor = c_atual;
            menor = mat[l_atual][c_atual];
        }
    }
    
    *l_proximo = l_melhor;
    *c_proximo = c_melhor;
    
    return menor;
}

int percurso(int **mat, int l, int c, int l_atual, int c_atual, int custo)
{
    if((l_atual == l - 1) && (c_atual == c - 1))
        return custo;
    else
    {
        mat[l_atual][c_atual] = INT_MAX;
        
        int aux = proximo_passo(mat, l, c, &l_atual, &c_atual);
        
        if(aux < INT_MAX)
            return percurso(mat, l, c, l_atual, c_atual, custo + mat[l_atual][c_atual]);
        else
            return INT_MAX;
    }
}

int main(void)
{
    int **mat, l, c, res;
    
    scanf("%d %d", &l, &c);
    
    mat = (int**)malloc(sizeof(int*) * l);
    
    for(int i = 0; i < l; i++)
    {
        mat[i] = (int*)malloc(sizeof(int) * c);
        
        for(int j = 0; j < c; j++)
            scanf("%d", &mat[i][j]);
    }
    
    res = percurso(mat, l, c, 0, 0, 0);
    
    if(res < INT_MAX)
        printf("%d", res);
    else
        printf("sem solucao");
    
    free(mat);
    
    return 0;
}
