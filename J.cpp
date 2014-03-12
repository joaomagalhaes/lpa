
/* LPA 2012/2013 Problem J  *
 * jdmessias 2009112796     */

#include <iostream>

int coordenadas[1000][2];

int determinante(int i, int n)
{
    int matriz[3][3];
    matriz[0][0] = matriz[1][0] = matriz[2][0] = 1;
    
    if(i == 0)
    {
        matriz[0][1] = coordenadas[n-1][0];
        matriz[0][2] = coordenadas[n-1][1];
        matriz[2][1] = coordenadas[i+1][0];
        matriz[2][2] = coordenadas[i+1][1];
    }
    
    else if(i == n-1)
    {
        matriz[0][1] = coordenadas[i-1][0];
        matriz[0][2] = coordenadas[i-1][1];
        matriz[2][1] = coordenadas[0][0];
        matriz[2][2] = coordenadas[0][1];
    }
    
    else
    {
        matriz[0][1] = coordenadas[i-1][0];
        matriz[0][2] = coordenadas[i-1][1];
        matriz[2][1] = coordenadas[i+1][0];
        matriz[2][2] = coordenadas[i+1][1];
    }
    
    matriz[1][1] = coordenadas[i][0];
    matriz[1][2] = coordenadas[i][1];
    
    return (matriz[0][0] * matriz[1][1] * matriz[2][2] + matriz[0][1] * matriz[1][2] * matriz[2][0] + matriz[0][2] * matriz[1][0] * matriz[2][1]) - ( matriz[0][2] * matriz[1][1] * matriz[2][0] + matriz[0][0] * matriz[1][2] * matriz[2][1] + matriz[1][0] * matriz[0][1] * matriz[2][2]);
}


// verifica se ponto (ptx, pty) esta contido no triangulo formado por (v1x, v1y) , (v2x, v2y), (v3x, v3y)
bool pontoEmTriangulo(int ptx, int pty, int v1x, int v1y, int v2x, int v2y, int v3x, int v3y)
{
    bool b1, b2, b3;
    b1 = ((ptx - v2x) * (v1y - v2y) - (v1x - v2x) * (pty - v2y) ) < 0.0f;
    b2 = ((ptx - v3x) * (v2y - v3y) - (v2x - v3x) * (pty - v3y) ) < 0.0f;
    b3 = ((ptx - v1x) * (v3y - v1y) - (v3x - v1x) * (pty - v1y) ) < 0.0f;
    return ((b1 == b2) && (b2 == b3));
}

int verificarOrelha(int i, int n)
{
    int j;
    
    for(j = 0; j < n; j ++)
    {
        if(j != i) // evitar ele mesmo
        {
            if(i == 0)
            {
                if(pontoEmTriangulo(coordenadas[j][0], coordenadas[j][1], coordenadas[n-1][0], coordenadas[n-1][1], coordenadas[i][0], coordenadas[i][1], coordenadas[i+1][0], coordenadas[i+1][1]))
                    return 0;
            }
            
            else if(i == n-1)
            {
                if(pontoEmTriangulo(coordenadas[j][0], coordenadas[j][1], coordenadas[i-1][0], coordenadas[i-1][1], coordenadas[i][0], coordenadas[i][1], coordenadas[0][0], coordenadas[0][1]))
                    return 0;
            }
            
            else
            {
                if(pontoEmTriangulo(coordenadas[j][0], coordenadas[j][1], coordenadas[i-1][0], coordenadas[i-1][1], coordenadas[i][0], coordenadas[i][1], coordenadas[i+1][0], coordenadas[i+1][1]))
                    return 0;
            }
        }
    }
    
    return 1; 
}

int main(int argc, const char * argv[])
{
    int n, i, result = 0;
    
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d %d", &coordenadas[i][0], &coordenadas[i][1]);
    
    for(i = 0; i < n; i++)
    {
        // verifica se e candidato a ser orelha (determinante negativo)
        if( determinante(i, n) < 0) 
        {
            // verifica se e orelha, nenhum ponto contido no triangulo formado por ele e adjacentes
            if(verificarOrelha(i, n)) 
                result++;
        }
    }
    
    printf("%d\n", result);
    return 0;
}

