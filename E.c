
/* LPA 2012/2013 Problem E  *
 * jdmessias 2009112796     */

#include <stdio.h>
#include <stdlib.h>

int eventsInit[150001];
int eventsFinal[150001];

int compare(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main(int argc, const char * argv[])
{
    int n, i, j = 0, salasNecessarias = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d %d", &eventsInit[i], &eventsFinal[i]);
    
    qsort(eventsInit, n, sizeof(int), compare); 
    qsort(eventsFinal, n, sizeof(int), compare); 

    salasNecessarias++;
    
    for(i = 1; i < n; i++)
    {
        if(eventsFinal[j] > eventsInit[i])
            salasNecessarias++;
        else
            j++;
    }
    printf("%d\n", salasNecessarias);
    return 0;
}
