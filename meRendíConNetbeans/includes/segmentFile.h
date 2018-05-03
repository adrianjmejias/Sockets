#ifndef SEGMENTFILE_H
#define SEGMENTFILE_H

#include "./colaT.h"
#include "./todos_los_includes.h"

    Cola* segmentFile(char *path){
         FILE *file;
        
        if((file = fopen(path, "r")) == NULL)
        {
            DeathByError("Error al abrir archivo");
        }else
        {
            Cola *out = malloc(sizeof(Cola));
            Inicializar(out);
            
            char *buffer;
            char in;
            int numBytes = 0, segmentosActuales = 1;
            printf("leyendo archivo\n");
            while(1){
                int index = numBytes % PACKET_SIZE; 
                printf("index = %d\n", index);
                in = fgetc(file);
                if(in == EOF){
                    //Si termina el archivo pero hay cosas en el buffer lo encolo poniendole un \0 para saber cuando termina
                    if(index > 0){
                        if(index < PACKET_SIZE) buffer[index] = '\0';
                        Insertar(out, buffer, NULL);
                    }

                    break;
                }

                if(index == 0) buffer = malloc(PACKET_SIZE * sizeof(char));
                
                //esto es lo "unico" importante, el resto lo que hace es evitar que todo explote
                buffer[index] = in;
                

                numBytes++;
                int nextIndex = (numBytes) % PACKET_SIZE;
                if(nextIndex == 0){
                    Insertar(out, buffer, NULL);
                    buffer = malloc(PACKET_SIZE * sizeof(char));
                }
                
            }
            fclose(file);
            return out;
              
        }
        
    }   

    bool compareFiles(char *buffa, char *buffb){
        int i = 0;
        while( i < PACKET_SIZE){
            if(buffa[i] != buffb[i]) return false;
        }
        return true;
    }

#endif