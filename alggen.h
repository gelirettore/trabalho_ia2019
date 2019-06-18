#ifndef ALGGEN_H
#define ALGGEN_H
#include "includes.h"

#define MAXPOP  10          //Numero maximo de individuos

float population[MAXPOP];     //Lista de individuos
int chromossome;            //indice do cromossomo
float newpopulation[MAXPOP];   //

void UpdateEPS();                       //Atualiza valor de EPS
void UpdatePopulation(float dist);      //Atualiza população
void SelectPopulation();

#endif