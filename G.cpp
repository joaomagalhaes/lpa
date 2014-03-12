
/* LPA 2012/2013 Problem G  *
 * jdmessias 2009112796     */

#include <iostream>
#include <queue>
using namespace std;

int graph[501][501];
int estado[501];
int n;

// algoritmo procura em largura alterado para respeitar o estado do vertice (comboio ou estacao)
// -1 : nao e nem estacao nem comboio
// 1: comboio
// 0: estacao de comboio
// estado[i] array que indica se vertice i e um comboio ou estacao

bool check(int first)
{
    int v, i;
    
    // todos os vertices inicialmente nao sao nem estacao nem comboio
    for(i = 0; i < n; i++)
        estado[i] = -1;
    
    estado[first] = 1; // 1o vertice - comboio
    
    // criar a queue e inserir 1o vertice
    queue <int> q;
    q.push(first);
    
    // enquanto houver vertices na queue
    while(!q.empty())
    {
        // acessa e apaga o 1o elemento
        int vert_atual = q.front();
        q.pop();
        
        // percorrer todos os vertices para procurar os adjacentes a vert_atual
        for(v = 0; v < n; v++)
        {
            // se o vertice for adjacente e ainda nao tiver seleccionado como comboio ou estacao
            if(graph[vert_atual][v] == 1 && estado[v] == -1)
            {
                // entao o vertice passa a ser o contrario do seu adjacente
                estado[v] = 1 - estado[vert_atual];
                q.push(v);
            
            // se o vertice for adjacente e for da mesmo tipo que o vert_atual, os dados estao corrompidos
            }
            else if(graph[vert_atual][v] == 1 && (estado[vert_atual] == estado[v]))
                return true;
        }
    }
    
    // todos os vertices estao designados como comboio ou estacao e nao ha conflitos
    return false;
}

int main(int argc, const char * argv[])
{
    int m, i, j, a, b;
    
    while(scanf("%d %d", &n, &m) != EOF)
    {
        // reinicializar matriz de adjacencia
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
                graph[i][j] = 0;
        }
        
        for(i = 0; i < m; i++)
        {
            scanf("%d %d", &a, &b);
            graph[a-1][b-1] = graph[b-1][a-1] = 1;
        }
        
        if(check(0))
            cout << "NO\n";
        else
            cout << "NOT SURE\n";
    }
    
    return 0;
}

