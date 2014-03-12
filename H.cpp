
/* LPA 2012/2013 Problem F  *
 * jdmessias 2009112796     */

#include <iostream>
using namespace std;

int n;
int timeX;
int graph[1000][1000];
int status[1000]; // 1 - not done // 2 - in progress // 3 - done
int bridge[1000]; // 1 - true // 2 - false
int d[1000];
int p[1000];
int low[1000];

int roadsToDestroy[1000][2];
int roadAtual;

void DFS_visit(int i)
{
    int v;
    
    d[i] = timeX++;
    low[i] = d[i];
    status[i] = 2;
    
    for(v = 0; v < n; v++)
    {
        if(graph[i][v] == 1)
        {
            if(status[v] == 1)
            {
                p[v] = i;
                DFS_visit(v);
                
                if(low[i] > low[v])
                    low[i] = low[v];
                
                if(low[v] > d[i])
                {
                    bridge[i] = 1;
                    // i - v bridge

                    if(i > v)
                    {
                        roadsToDestroy[roadAtual][0] = v;
                        roadsToDestroy[roadAtual][1] = i;
                    }
                    else
                    {
                        roadsToDestroy[roadAtual][1] = v;
                        roadsToDestroy[roadAtual][0] = i;
                    }
                    
                    roadAtual++;
                }
                
            }
            else if(status[v] == 2 && p[i] != v)
            {
                if(low[i] > d[v])
                    low[i] = d[v];
            }
        }
    }
    status[i] = 3;
}

int cmp( const void* p1, const void* p2 )
{
	int* arr1 = (int*)p1;
	int* arr2 = (int*)p2;
	int diff1 = arr1[0] - arr2[0];
	if (diff1) return diff1;
	return arr1[1] - arr2[1];
}

int main(int argc, const char * argv[])
{
    int m, i, j, a, b;
    
    while(scanf("%d %d", &n, &m) != EOF)
    {
        roadAtual = 0;
        for(i = 0; i < n; i++) { for(j = 0; j < n; j++) graph[i][j] = 0; }
        
        for(i = 0; i < m; i++)
        {
            scanf("%d %d", &a, &b);
            graph[a][b] = graph[b][a] = 1;
        }
                
        for(i = 0; i < n; i++)
        {
            status[i] = 1;
            bridge[i] = 2;
        }
        
        timeX = 0;
        
        for(i = 0; i < n; i++)
        {
            if(status[i] == 1)
                DFS_visit(i);
        }
        
        if(roadAtual != 0)
        {
            qsort (roadsToDestroy, roadAtual, 2 * sizeof(int), cmp);
            for(i = 0; i < roadAtual; i++)
                printf("%d %d\n", roadsToDestroy[i][0], roadsToDestroy[i][1]);
        
        }else
            cout << "No road\n";
    }

    return 0;
}

