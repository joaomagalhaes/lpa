
/* LPA 2012/2013 Problem A - Maze *
 * jdmessias 2009112796           */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char flag; /* se flag = n > nao terminado. se flags = t, terminado. inicia como 'n' */
char maze[101][101]; /* labirinto com o mapa */
short path[10000][2]; /* array com as coordenadas do caminho */
short counter; /* variavel auxiliar, para controlo do array 'path' */
short row; /* numero de linhas */
short column; /* numero de colunas */
char change; /* variavel auxiliar */

/* funcao principal que ira calcular o caminho */
void calc(short i, short j, char lastSymbol)
{
    /* enquanto o caminho nao for encontrado, a flag mantem-se a 'n' e os calculos procedem */
    if(flag == 'n' &&  i >= 0 && i < row && j >= 0 && j < column)
    {
        /* guardar coordenadas atuais no array que vai conter o caminho, mais tarde removidas se nao usadas */
        path[counter][0] = i;
        path[counter][1] = j;
        counter++;
        
        char change = 'n';
        
        /* verificacoes de caminhos, de acordo com o simbolo atual */
        if( lastSymbol == '|'){
            
            if(maze[i+1][j-1] == '/'){
                change = 'c';
                calc(i+1, j-1, maze[i+1][j-1]);
            }
            
            if(maze[i+1][j] == '|'){
                change = 'c';
                calc(i+1, j, maze[i+1][j]);
            }
            
            if(maze[i+1][j+1] == '\\'){
                change = 'c';
                calc(i+1, j+1, maze[i+1][j+1]);
            }
            
        }else if( lastSymbol == '\\') {
            
            if(maze[i+1][j] == '/') {
                change = 'c';
                calc(i+1, j, maze[i+1][j]);
            }
            
            if(maze[i+1][j+1] == '|'){
                change = 'c';
                calc(i+1, j+1, maze[i+1][j+1]);
            }
            
            if(maze[i+1][j+1] == '\\'){
                change = 'c';
                calc(i+1, j+1, maze[i+1][j+1]);
            }
            
            if(maze[i][j-1] == '/' && !(i == path[counter-2][0] && j-1 == path[counter-2][1])){
                change = 'c';
                calc(i, j-1, maze[i][j-1]);
            }

            if(maze[i][j+1] == '/' && !(i == path[counter-2][0] && j+1 == path[counter-2][1])){
                change = 'c';
                calc(i, j+1, maze[i][j+1]);
            }

        }else if( lastSymbol == '/') {
            
            if(maze[i+1][j-1] == '|'){
                change = 'c';
                calc(i+1, j-1, maze[i+1][j-1]);
            }
            
            if(maze[i+1][j-1] == '/') {
                change = 'c';
                calc(i+1, j-1, maze[i+1][j-1]);
            }
            
            if(maze[i+1][j] == '\\') {
                change = 'c';
                calc(i+1, j, maze[i+1][j]);
            }
            
            if(maze[i][j-1] == '\\' && !(i == path[counter-2][0] && j-1 == path[counter-2][1])) {
                change = 'c';
                calc(i, j-1, maze[i][j-1]);
            }

            if(maze[i][j+1] == '\\' && !(i == path[counter-2][0] && j+1 == path[counter-2][1])) {
                change = 'c';
                calc(i, j+1, maze[i][j+1]);
            }
        }
        
        /* caso o i seja igual ao numero de linhas, entao caminho encontrado, imprimir */
        if (i == row-1)
        {
            /* remover se existir mais de 1 coordenada com i = 0 (menor caminho) */
            short init = 0;
            while( path[init][0] == 0){
                init++;
            }
            init--;
            /* imprimir caminho */
            while(init < counter){
                if(init == counter-1){
                    printf("(%d,%d)\n", path[init][0]+1, path[init][1]+1);
                    init++;
                }else{
                    printf("(%d,%d),", path[init][0]+1, path[init][1]+1);
                    init++;
                }
            }
            counter = 0;
            flag = 't';
        
        /* se nao terminou e 'change' nao foi alterado, significa q nao entrou em nenhum 'if', pelo que e um beco sem saida */
        /* remover este caminho, e voltar para tras */
        } else if(change == 'n' && i != 0){
            maze[i][j] = '#';
            counter = counter - 2;
            calc(path[counter][0], path[counter][1], maze[path[counter][0]][path[counter][1]]);
        
        /* se nao terminou, change nao foi alterado e esta na primeira linha, entao termina de procurar o caminho desde este simbolo inicial */
        } else if(change == 'n' && i == 0){
            maze[i][j] = '#';
            counter--;
        }
    }
}

int main(int argc, const char * argv[])
{
    short i, j;
    /* inicio do programa, ler dados e fazer calculos ate ao fim do input */
    while( scanf("%hd %hd", &row, &column) != EOF)
    {
        flag = 'n';
        counter = 0;
        /* preenchimento labirinto */
        for (i = 0; i < row; i++)
            scanf("%s", maze[i]);
        /* inicio calculo, percorre 1a linha a procura de um simbolo */
        for(j = 0; j < column; j++)
        {
            /* se encontrar simbolo */
            if(maze[0][j] == '|' || maze[0][j] == '/' || maze[0][j] == '\\' )
            {
                /* inicia procura de caminho a partir desse simbolo */
                calc(0, j, maze[0][j]);
                /* caso a flag seja alterada para t, na procura de caminho anterior, termina a procura */
                if(flag == 't')
                    break;
            }
        }
        /* se terminou de procurar todos os caminhos e flag continua n, nao existe caminho */
        if(flag == 'n')
            printf("No Path!\n");
    }
    return 0;
}

