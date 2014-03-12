
/* LPA 2012/2013 Problem I  *
 * jdmessias 2009112796     */

#include <iostream>
using namespace std;

int eventos[2001][4];    // eventos a percorrer verticalmente
int rec_ativos[1001][2]; // rectangulos ativos
int index_lista;

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void atualizarRectangulosAtivos(int i) // adicionar e remover rectangulos ativos / nao ativos
{
    int j = 0;
    int k, aux1, aux2, aux3, aux4;
    
    if (eventos[i][0] < eventos[i][2]) // inserir rectangulo
    {
        while(rec_ativos[j][0] < eventos[i][1] && j < index_lista)
            j++;
        
        aux1 = rec_ativos[j][0];
        aux2 = rec_ativos[j][1];
        aux3 = 0;
        aux4 = 0;
        
        rec_ativos[j][0] = eventos[i][1];
        rec_ativos[j][1] = eventos[i][3];
        
        k = j + 1;
        
        while(k <= index_lista)
        {
            aux3 = rec_ativos[k][0];
            aux4 = rec_ativos[k][1];
            
            rec_ativos[k][0] = aux1;
            rec_ativos[k][1] = aux2;
            
            aux1 = aux3;
            aux2 = aux4;
            k++;
        }
        
        rec_ativos[k][0] = aux1;
        rec_ativos[k][1] = aux2;
        index_lista ++;
        
    }else // remover rectangulo
    {
        j = 0;
        while(rec_ativos[j][0] != eventos[i][3] && rec_ativos[j][1] != eventos[i][1])
            j++;
        
        while(rec_ativos[j][0] != 0)
        {
            rec_ativos[j][0]=rec_ativos[j+1][0];
            rec_ativos[j][1]=rec_ativos[j+1][1];
            j++;
        }
        index_lista--;
    }
}

int main(int argc, const char * argv[])
{
    int i, j, n, largura = 0, altura_anterior = 0, altura = 0, x_ultimo = 0, area = 0, perimetro = 0, x_atual, aux;

    n = 0;
    while (scanf("%d %d %d %d", &eventos[n][0], &eventos[n][1], &eventos[n][2], &eventos[n][3]) != EOF)
    {
        eventos[n+1][0] = eventos[n][2];
        eventos[n+1][1] = eventos[n][3];
        eventos[n+1][2] = eventos[n][0];
        eventos[n+1][3] = eventos[n][1];
        n += 2;
    }
    
    qsort(eventos, n, 4 * sizeof(int), compare);
    
    for(i = 0; i < n; i++) // sweep line vertical
    {
        if(i == 0)
        {
            x_ultimo = eventos[0][0];
            rec_ativos[0][0] = eventos[0][1];
            rec_ativos[0][1] = eventos[0][3];
            index_lista++;
            continue;
        }
        
        x_atual = eventos[i][0];
        largura = x_atual - x_ultimo;
        if (largura == 0) continue; // linha vertical nao avancou, 2 rectangulos com o mesmo x, passar a frente
        
        aux = 0;
        altura = rec_ativos[0][1] - rec_ativos[0][0];
        for(j = 1; j < index_lista; j++) // 'sweep line horizontal'
        {
            if(rec_ativos[j][0] > rec_ativos[aux][1])
            {
                perimetro += 2 * largura;
                altura += rec_ativos[j][1] - rec_ativos[j][0];
                aux = j;
                
            }else if(rec_ativos[j][0] < rec_ativos[aux][1] && rec_ativos[j][1] > rec_ativos[aux][1])
            {
                altura += rec_ativos[j][1] - rec_ativos[aux][1];
                aux = j;
            }
        }
        
		if(altura_anterior < altura)
            perimetro+= 2 * (altura - altura_anterior);
        
		perimetro += 2 * largura;
        area += altura * largura;
        x_ultimo = x_atual;
        altura_anterior = altura;
        
        atualizarRectangulosAtivos(i);
    }
    
    printf( "%d %d\n", area, perimetro);
    return 0;
}
