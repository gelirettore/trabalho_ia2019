#ifndef DBSCAN_H
#define DBSCAN_H
#include "sensor.h"
#include "includes.h"
#include "alggen.h"


void addVector(float value, int id);
void Neighbourhood(int point, sensor_data *DB, int lines, int minpts, int cluster);
int findNeighbor(float *distances, int lines);
void dbscan(sensor_data *DB, int minpts, int size);
int isCore(float point, sensor_data *DB, int lines, int minpts);

#endif