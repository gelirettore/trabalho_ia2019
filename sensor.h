#ifndef SENSOR_H
#define SENSOR_H 
#include "includes.h"

typedef struct sensor_data {
    double value;           // Valor lido pelo sensor
    int classification;    // Classificação: -1=noise, 0=border, >0 core
} sensor_data;

#endif

