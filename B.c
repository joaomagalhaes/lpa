
/* LPA 2012/2013 Problem B  *
 * jdmessias 2009112796     */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char matrix[1024][1025];
short actualSize;

void calc(short n, short r)
{
    if (n == 0)
    {
        actualSize = 1;
        matrix[0][0] = '0';

    }else{
        
        calc(n-1, r);
        short i, j, c, c1;
        
        /* quadrante 1 */
        if( r != 1){
            for(i = 0; i < actualSize; i++)
                memcpy(&matrix[i][actualSize], &matrix[i][0], sizeof(char) * actualSize);
        }else{
            c = 0;
            for(i = 0; i < actualSize; i++){
                for(j = 0; j < actualSize; j++){
                    if(matrix[i][j]== '0')
                        matrix[i][actualSize + c] = '1';
                    else
                        matrix[i][actualSize + c] = '0';
                    c++;
                }
                c = 0;
            }
        }
        
        /* quadrante 3 */
        if ( r!= 3 ){
            for(i = 0; i < actualSize; i++)
                memcpy(&matrix[actualSize+(i*1)][0], &matrix[i][0], sizeof(char) * actualSize);
        }else{
            c = 0;
            for(i = 0; i < actualSize; i++){
                for(j = 0; j < actualSize; j++){
                    if(matrix[i][j] == '0')
                        matrix[actualSize + c][j] = '1';
                    else
                        matrix[actualSize + c][j] = '0';
                }
                c++;
            }
        }

        /* quadrante 4 */
        if ( r != 0 ){
            for(i = 0; i < actualSize; i++)
                memcpy(&matrix[actualSize+(i*1)][actualSize], &matrix[i][0], sizeof(char) * actualSize );
        }else{
            c = 0;
            c1 = 0;
            for(i = 0; i < actualSize; i++){
                for(j = 0; j < actualSize; j++){
                    if(matrix[i][j] == '0')
                        matrix[actualSize + c][actualSize + c1] = '1';
                    else
                        matrix[actualSize + c][actualSize + c1] = '0';
                    c1++;
                }
                c++;
                c1 = 0;
             }
        }
        
        /* quadrante 2*/
        if( r == 2){
            for(i = 0; i < actualSize; i++){
                for(j = 0; j < actualSize; j++){
                    if(matrix[i][j] == '0')
                        matrix[i][j] = '1';
                    else
                        matrix[i][j] = '0';
                }
            }
        }
        actualSize = actualSize * 2;
    }
}

int main(int argc, const char * argv[])
{
    short n, r, i;
    while(scanf("%hd %hd", &n, &r) != EOF)
    {
        r = r % 4;
        calc(n, r);
        for(i = 0; i < actualSize; i++)
        {
            matrix[i][actualSize] = '\0';
            printf("%s\n", matrix[i]);
        }
    }
    return 0;
}
