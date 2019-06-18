#include "debug.h"


void debug(char text[1024], unsigned int wait){
    if(DEBUG == 1){
        printf("%s\n", text);
        if(wait == 1){
            getc(stdin);
        }
    }
}