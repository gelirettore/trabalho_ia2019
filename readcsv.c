#include "readcsv.h"
/**
 * Lê o tamanho do arquivo
 * filename: caminho para o arquivo
 * Retorno: número de linhas do arquivo
 */
int getFileSize(char *filename, FILE *fp){
    char ln[1024];
    int lines = 0;
    if(fp != NULL){
        while(fgets(ln, 1024, fp)){ //verifica quantas linhas tem o arquivo
            lines++;
        } 
        rewind(fp);
    }
    return lines;
}

float getValue(FILE *fp){
    char ln[1024];    
    float value;
    if(fgets(ln, 1024, fp)){
        value = atof(ln);
        return value;
    }
    return -1;
}