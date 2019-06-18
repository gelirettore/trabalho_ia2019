#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sensor.h"

int getFileSize(char *filename, FILE *fp);
float getValue(FILE *fp);