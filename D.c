
/* LPA 2012/2013 Problem D  *
 * jdmessias 2009112796     */

#include <stdio.h>
#include <stdlib.h>

short solucao[301][30001];
short departamentos;
short ectsTotal;
short cursos_dep;
short satis;
short ects;

int main(int argc, const char * argv[])
{
    short i, j, k;
    scanf("%hd %hd", &departamentos, &ectsTotal);
    for(i = 1; i <= departamentos; i++)
    {
        scanf("%hd", &cursos_dep);
        for(j = 0; j < cursos_dep; j++)
        {
            scanf("%hd %hd", &ects, &satis);
            for(k = 1; k <= ectsTotal; k++)
            {
                if(j == 0)
                {
                    if(ects > k)
                        solucao[i][k] = solucao[i-1][k];
                    else
                    {
                        if( solucao[i-1][k] > solucao[i-1][k-ects] + satis )
                            solucao[i][k] = solucao[i-1][k];
                        else
                            solucao[i][k] = solucao[i-1][k-ects] + satis;
                    }
                }else{
                    if(ects <= k && solucao[i-1][k-ects] + satis > solucao[i][k])
                        solucao[i][k] = solucao[i-1][k-ects] + satis;
                }
            }
        }
    }
    printf("%hd\n", solucao[departamentos][ectsTotal]);
    return 0;
}
