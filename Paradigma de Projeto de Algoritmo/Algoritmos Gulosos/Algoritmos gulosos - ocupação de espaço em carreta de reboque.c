/*
Dada uma carreta de reboque com espaço útil de comprimento l e cargas de comprimento m e n, supondo que todas têm a mesma largura e altura. 
Para o transporte, deve ser minimizada a quantidade de itens, já que os mesmos são pesados. 
Desse modo, primeiramente deve ser colocada uma certa quantia referente ao maior item.
O espaço restante deve ser preenchida com unidades do item menor, caso seja possível. 
Dessa forma, ainda pode haver espaço ocioso. Implemente um algoritmo guloso que determine a quantia de cada um dos itens a serem transportados.

Input Format
Devem ser lidos 3 números inteiros em sequência: l (comprimento da carreta), m (comprimento da carga 1) e n (comprimento da carga 1).

Output Format
Na primeira linha deve ser impressa a quantidade de carga 1 que deve ser colocada na carreta.
Na segunda linha deve ser impressa a quantidade de carga 2 que deve ser colocada na carreta.
Na terceira linha deve ser impresso o espaço que sobrou na carreta.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void qnt_carga(int l, int m, int n)
{
    if(n > m)
    {
        int sobrou = l;
        int carga2 = 0;
        
        for(int i = 0; i < l; i++)
        {
            sobrou -= n;
            carga2++;
            if(sobrou <= n)
                break;
        }
        
        int carga1 = 0;
        
        for(int i = 0; i < l; i++)
        {
            sobrou -= m;
            carga1++;
            if(sobrou <= m)
                break;
        }
        printf("%d\n%d\n%d\n", carga1, carga2, sobrou);
    }
    else
    {
        int carga1 = 0;
        int sobrou = l;

        for(int i = 0; i < l; i++)
        {
            sobrou -= m;
            carga1++;
            if(sobrou <= m)
                break;
        }

        int carga2 = 0;
        
        for(int i = 0; i < l; i++)
        {
            sobrou -= n;
            carga2++;
            if(sobrou <= n)
                break;
        }
        printf("%d\n%d\n%d\n", carga1, carga2, sobrou);
    }
}

int main(void)
{
    int l, m, n;
    
    scanf("%d %d %d", &l, &m, &n);
    
    qnt_carga(l, m, n);

    return 0;
}
