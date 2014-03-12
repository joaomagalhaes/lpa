
/* LPA 2012/2013 Problem C  *
 * jdmessias 2009112796     */

#include <stdio.h>
#include <stdlib.h>

short graph[35][35];
short havePrinter[35];
short best;
short actualPrinters;

/* verifica se e solucao, caso seja devolve 1, caso nao seja devolve 0 */
int isSolution(int n)
{
    int i, j, sum = 0;
    for(i = 0; i < n; i++)
    {
        sum += havePrinter[i];
        for(j = 0; j < n ; j++)
        {
            if(graph[i][j] == 1)
                sum += havePrinter[j];
        }
        if(sum == 0)
            return 0;
        sum = 0;
    }
    return 1;
}

int backtracking(short n, short v, short actualPrinters)
{
    int i;
    
    /* rejection test */
    if ( actualPrinters >= best)
        return 1;
    
    /* base case */
    if (isSolution(n) && actualPrinters < best){
        best = actualPrinters;
        return 1;
    }
        
    for(i = v + 1; i < n; i++)
    {
        havePrinter[i] = 1;                         /* mark as visited */
        backtracking(n, i, actualPrinters + 1);     /* recursive step */
        havePrinter[i] = 0;                         /* mark as unvisited */
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    short n, i, j, l;
    
    for(i = 0; i < 35; i++)
    {
        havePrinter[i] = 0;
        for(j = 0; j < 35; j++)
        {
            graph[i][j] = 0;
        }
    }
    
    scanf("%hd", &n);
    while(scanf("%hd %hd", &j, &l) != EOF)
    {
        graph[j-1][l-1] = 1;
        graph[l-1][j-1] = 1;
    }
        
    best = n;
    actualPrinters = 0;
    backtracking(n, -1, actualPrinters);

    printf("%hd\n", best);
    return 0;
}

