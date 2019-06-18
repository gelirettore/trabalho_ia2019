#include "dbscan.h"


/**
 * Salva resultados do DBSCAN em um arquivo csv
 * DB: tabela do DBSCAN
 * filename: arquivo em que os dados serao salvos
 * clusters: numero de clusters criados
 * size: tamanho da tabela
 **/
void SaveResultsCSV(sensor_data *DB, char *filename, int size){
   FILE *fp;
   fp = fopen(filename, "w");  
   if(fp != NULL){
      fprintf(fp, "value;cluster\n");
      for(int i=0; i<size;i++){
         fprintf (fp, "%3.2f;%d\n", DB[i].value, DB[i].classification);
      }
      fclose(fp);
      printf("Salvando resultados no arquivo %s\n", filename);
   }
}

/**
 * Salva resultados do DBSCAN em um arquivo texto
 * DB: tabela do DBSCAN
 * filename: arquivo em que os dados serao salvos
 * clusters: numero de clusters criados
 * size: tamanho da tabela
 **/
void SaveResultsTXT(sensor_data *DB, char *filename, int clusters, int size){
   FILE *fp;
   int c=0;
   fp = fopen(filename, "w");  
   if(fp != NULL){
      for(int k=-1; k<=clusters; k++){
         if(k==0) k++;
         if(k == -1 ) fprintf(fp, "Outliers:\n");
         else fprintf(fp, "Cluster %d\n", k);
         c=0;
         for(int i=0; i<size; i++){
            if(DB[i].classification == k){
               fprintf (fp, "%3.2f  ", DB[i].value);
               c++;
               if(c==15){
                  fprintf(fp, "\n");
                  c=0;
               }
               
            }
         }
         fprintf(fp, "\n--------------\n");
      }
   }
}

/**
 * Calcula a distância euclidiana entre o ponto e todos os elementos do vetor
 * point: ponto para o qual a distância será calculada
 * D: vetor de distâncias
 * lines: numero de linhas já inseridas no vetor
 * Retorno: distancia euclidina
 */
void Neighbourhood(int point, sensor_data *DB, int lines, int minpts, int cluster){
   for(int count = 0; count < lines; count++){  
      float dist = 0;
      if(DB[count].classification > 0)   continue;
      //calcula a distância euclidiana entre cada elemento de D e o ponto
      dist = sqrt( pow( DB[count].value - DB[point].value, 2)); 
      if(dist <= EPS){
         DB[count].classification = cluster;
         if(isCore(DB[count].value, DB, lines, minpts) == 1 ){
            for(int cc = 0; cc<lines; cc++){
               dist = sqrt( pow( DB[cc].value - DB[count].value, 2)); 
               if(dist <= EPS){
                  if(DB[cc].classification >=0)   continue;
                  DB[cc].classification = cluster;
               }else if(dist <= (EPS + NEIGHBOR)){
                  UpdatePopulation(dist);
               }
            }
         }

      }else if(dist <= (EPS + NEIGHBOR)){
            UpdatePopulation(dist);
         }
   }
      
}


/**
 * Verifica se o ponto é um core
 * point: o ponto atualmente avaliado
 * DB: a tabela contendo todos os elementos da base de dados
 * lines: quantidade de linhas da tabela
 * minpts: numero minimo de vizinhos
 * Retorno: 1=> Core Point, 0 = nao é Core Point
 */
int isCore(float point, sensor_data *DB, int lines, int minpts){
   int n = 0;
   for(int i = 0; i<lines; i++){
         float dist = sqrt(pow( DB[i].value - point, 2)); 
         if(dist <= EPS){
            n++;
         }
         if(n >= minpts) return 1;

   }
   return 0;
}

/**
 * DBSCAN
 * DB: vetor de dados lidos
 * eps: raio que define a vizinhança
 * minpts: numero mínimo de vizinhos para ser um core
 * size: tamanho do vetor
 */
void dbscan(sensor_data *DB, int minpts, int size){
   int cluster = 0;
   printf("DBSCAN (%d)\n", size);
   chromossome = -1;
   for(int i=0; i<size; i++){
      if(DB[i].classification >= -1){
         continue;
      }
      if(isCore(DB[i].value, DB, size, minpts) == 0 ){
         DB[i].classification = -1;
         continue;
      }
      cluster++;
      Neighbourhood(i, DB, size, minpts, cluster); 
   }

   printf("Total de clusters criados: %d\n", cluster);
   SaveResultsCSV(DB, "ad-results.csv", size );
   SaveResultsTXT(DB, "ad-results.txt", cluster, size );
   
}