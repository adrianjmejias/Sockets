#include "./colaT.h"
#ifndef SEGMENTFILE_H
#define SEGMENTFILE_H

    Cola* segmentFile(char *path){
         FILE file;
        
        if((file = fopen(path, "r")) == NULL)
        {
            DieByError("Error al abrir archivo %s", path);
        }else
        {
            Cola *out = malloc(sizeof(Cola));
            Inicializar(out);
            
            char *buffer = malloc(PACKET_SIZE * sizeof(char));
            char in;
            int numBytes = 0, segmentosActuales = 1;
            
            while((in = fgetc(file)) != EOF){
                numBytes++;
                int segmentosNeeded = ceil(numBytes/PACKET_SIZE);
                
                if(segmentosActuales < segmentosNeeded)
                {
                    Insertar(out, Bbuffer);
                    buffer = malloc(PACKET_SIZE * sizeof(char));
                }
                
                buffer[numBytes % PACKET_SIZE] = in;
                
            }
            fclose(file);
            return out;
            
        }
        
    }

    bool compareFiles(char *buffa, char *buffb){
        
        while( i < SEGMENT_SIZE){
            if(buffa[i] != buffb) return false;
        }
        return true;
    }

#endif