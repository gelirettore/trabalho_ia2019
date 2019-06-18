#include "alggen.h"

/**
 * Atualiza população, com distancias maiores de EPS, porém próximas
 * dist: distancia adicionada à população
 */
void UpdatePopulation(float dist){
    if( chromossome == -1){
        for (int i=0; i<MAXPOP; i++){
            population[i] = EPS;
        }
        chromossome = 0;
    }else{
        population[chromossome] = dist;

        chromossome++;
    }
    if(chromossome == MAXPOP){
        UpdateEPS();
        chromossome = 0;
    } 
}

/**
 * Seleciona população para cruzamento - escolhe os valores mais próximos ao EPS 
 */
void SelectPopulation(){
    float discart1 = 0, discart2 = 0, duplicate1 = EPS, duplicate2 = EPS, aux;
    int id =0;
    uint32_t val1, val2, mid1, mid2, mid3, mid4;
    float vector[MAXPOP] ;

    for(int i=0; i < MAXPOP; i++){
        aux = population[i];
        if(discart1 == 0){
            discart1 = aux;
        }else if(discart2 == 0){
            discart2 = aux;
        }else if(aux >= discart1){
            if(discart1 > discart2){
                discart2 = discart1;
            }                
            discart1 = aux;
        }
        
        if(duplicate1 == EPS){
            duplicate1 = aux;
        }else if(duplicate2 == EPS){
            duplicate2 = aux;
        }else if(aux <= duplicate1){
            if(duplicate1 < duplicate2){
                duplicate2 = duplicate1;
            }
            duplicate1 = aux;
        }
    }
    id = 0;
    for(int i=0, stop=0; i < MAXPOP; i++){
        if((population[i] == discart1 && stop == 0) || (population[i] == discart2 && stop == 1)){
            stop++;
        }else{
            vector[id] = population[i];
            id++;
        }   
    }

    vector[MAXPOP-2] = duplicate1;
    vector[MAXPOP-1] = duplicate2;

    //Crossover
    for(int i =0; i<MAXPOP - 2; i+=2 ){ 
        val1 = (long) (vector[i] * 100);
        val2 = (long) (vector[i+1] * 100);

        mid1 = val1 >> 4;
        mid1 = mid1 << 4;
        mid2 = val1 << 28;
        mid2 = mid2 >> 28;

        mid3 = val2 >> 4;
        mid3 = mid3 << 4;
        mid4 = val2 << 28;
        mid4 = mid4 >> 28;

        newpopulation[i] = (float) (mid1 + mid4) /100 ;
        newpopulation[i+1] = (float) (mid2 + mid3) /100;
    }

    //Mutação
    val1 = (long) (vector[MAXPOP-2] * 100);
    mid1 = val1 >> 4;
    mid1 = mid1 << 4;
    mid2 = val1 << 28;
    mid2 = mid2 >> 28;
    mid2 = mid2 + 1; //muta um bit
    val1 = mid1 + mid2;
    newpopulation[MAXPOP-2] = (float) (val1) / 100;
    newpopulation[MAXPOP-1] = vector[MAXPOP-1];
}

/**
 * Atualiza valor de EPS para ajustar melhor os dados
 */
void UpdateEPS(){
    float neweps = 0;

    SelectPopulation();
    
    for(int i=0; i<MAXPOP; i++){
        neweps += newpopulation[i];
    }
    EPS = neweps / MAXPOP;
    printf("Ajustando eps para %.2f\n", EPS);
}