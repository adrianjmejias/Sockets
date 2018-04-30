#include "colaT.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#ifndef SEGMENTFILE
#define SEGMENTFILE

#define MB (1 << 10)
#define SEGMENT_SIZE (MB << 4) //chunks de 16 mbs

    col segmentFile(char *file){
        col *cola = Inicializar(cola);
        File in;

        if((in = fopen(file, "r")) != NULL){
            char c;
            while((c = getc(in)) != EOF){
                
            }
            
            fclose(in);
        }
    }

#endif