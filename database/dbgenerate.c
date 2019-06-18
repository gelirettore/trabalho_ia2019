#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    float min =0, max =0, val;
    int qtde = 0, qtde_ruido = 0;
    if(argc < 4 ){
        printf("Usage %s <menor> <maior> <quantidade>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    min = atof(argv[1]);
    max = atof(argv[2]);
    qtde = atoi(argv[3]);
    qtde_ruido = qtde * 1 / 100;

    srand((unsigned int)time(NULL));
printf("NRuidos: %d\n", qtde_ruido);
    for (int i=0;i<qtde;i++)
        if (max == min) printf("%.1f\n", min);
        else if(min < max){
            val = (max - min) * ((float)rand()/(float)(RAND_MAX)) + min;
            printf("%.1f\n", val);
            
            if( qtde_ruido > 0 && ( rand() % 10)  == 3 ){
                if((rand() % 5)  == 1)
                    printf("%.1f\n", (-1) * val );
                else 
                    printf("%.1f\n", (max) * val );
                qtde_ruido--;
            }
        } 
    return 0;
}