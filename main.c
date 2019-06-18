#include "main.h"


int main(int argc, char *argv[]) {
    char *filename;
    FILE *fp;
    int dbrow = 0;
    float value;
    sensor_data *data;
    dbrow = 0;

    if(argc < 5 ){
        printf("Usage %s <database> <minpts> <eps> <neighbor>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    filename = (char *) malloc(sizeof(argv[1])+1);
    EPS = atof(argv[3]);
    MINPTS = atoi(argv[2]);
    NEIGHBOR = atof(argv[4]);

    strcpy(filename, argv[1]);
    debug("Loading data. Please wait...", 0);
    fp = fopen(filename, "r");
    if(fp!=NULL){
        dbrow = getFileSize(filename, fp);
        printf("Total de linhas: %d\n", dbrow);
        data = (sensor_data *) malloc(dbrow * sizeof (sensor_data));
        for(int ln = 0; ln < dbrow; ln++){
            value = getValue(fp); //lê a próxima linha do arquivo
            data[ln].value = value;
            data[ln].classification = -9;
           

        }
        fclose(fp);
        dbscan(data, MINPTS, dbrow);
        free(data);
    }else{
        printf("Cannot open file <%s>\n", filename);
    }
    //TODO: Criar uma heuristica para definir eps utilizando algoritmo genetico
    
    free(filename);
    printf("Terminando\n");
}