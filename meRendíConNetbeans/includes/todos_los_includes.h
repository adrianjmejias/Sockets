#ifndef TODOS_LOS_INCLUDES
#define TODOS_LOS_INCLUDES
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
/*funcion del hash modo libreria*/
#define HASH_SIZE 33
//int MDFile(char* filename, char hashValue[HASH_SIZE]);

#define PACKET_SIZE 1024 //1 MEGAS
#define PATHSIZE PACKET_SIZE // debería tener un _ pero 
#define DeathByError(printfParam) printf(printfParam); exit(-1)
#define COMPROBAR 1
#define AGREGAR 2
#define ELIMINAR 3
#define SALIR 4
#include "colaT.h"
#define CLEAN_BUFFER(a,len) memset(a, '\0', len)

    size_t getFileSize(char *path){
        size_t size;
        FILE *file;
        if((file = fopen(path, "rb")) == NULL){
            printf("Error en getFileSize(%s)", path);
            exit(-1);
        }
        fseek(file, 0L, SEEK_END);
        size = ftell(file);

        fseek(file, 0L, SEEK_SET);
        fclose(file);
        return size;
    }

//Done and tested
Cola *receiveNPackets(int idsocket)
{
   printf("entrando receiveNPackets \n");
    
    char IO[PACKET_SIZE];
    int tam;
    Cola *out = malloc(sizeof(Cola));
    Inicializar(out);
    recv(idsocket, IO, PACKET_SIZE, 0);//recibir de verdad
    tam = strtoul(IO, NULL, 10);
    send(idsocket, IO, PACKET_SIZE,0);//enviar inutil

    while(tam--)
    {
        CLEAN_BUFFER(IO, PACKET_SIZE);
        recv(idsocket, IO, PACKET_SIZE,0);//recibir de verdad 
        char *aux = malloc(sizeof(char) * PACKET_SIZE);
        strcpy(aux,IO);
        Insertar(out, aux, NULL);

        send(idsocket, IO, PACKET_SIZE,0); //enviar inutil
    }
    printf("saliendo receiveNPackets \n");
    
    return out;
}

//done and tested
void sendNPackets(int idsocket, Cola *in)
{
    //printf("entrando sendNPackets \n");
    char IO[PACKET_SIZE];
    sprintf(IO, "%d", in -> tamanio);
    send(idsocket, IO, strlen(IO),0);//enviar de verdad 
    recv(idsocket, IO, PACKET_SIZE,0);//recibir inutil
    while(!colaVacia(in))
    {
        CLEAN_BUFFER(IO, PACKET_SIZE);
        strcpy(IO, Desencolar(in).path);
        send(idsocket, IO, strlen(IO),0);//enviar de verdad
        recv(idsocket, IO, PACKET_SIZE,0);//recibir inutil

    }
  //  printf("saliendo sendNPackets \n");
    
}

char* bufferFromFile(char* completePath){
    FILE *file;
    size_t size, ii;
    char *buffer;
    
    size = getFileSize(completePath);
    buffer =  malloc(sizeof(char) * size);
    file = fopen(completePath, "rb");
    
    ii = 0;
    while(size--){

        buffer[ii] = fgetc(file);

        ii++;
    }
    fclose(file);
    return buffer;
}

void fileFromBuffer(char *completePath, char *buffer, size_t size){
    FILE *file;
    size_t ii;

    file = fopen(completePath, "wb");
    
    ii = 0;
    while(size--){

        fputc(buffer[ii], file);

        ii++;
    }
    printf("archivo %s listo\n", completePath);
    fclose(file);
}


void sendFile(int id, char *name, char *path){
    char completePath[PACKET_SIZE] = "";
    char aux[PACKET_SIZE] = "";
    strcat(completePath, name);// esto deberia dar server/ o client/
    strcat(completePath, path);

    size_t size = getFileSize(completePath);
    char *buffer = bufferFromFile(completePath);

    sprintf(aux, "%zu", size);

    send(id, path, strlen(path), 0); // mando path
    send(id, aux, strlen(aux), 0); //mando size
    send(id, buffer, size, 0); // mando archivo

    free(buffer);
}

void receiveFile(int id, char *name){
    char completePath[PACKET_SIZE] = "";
    char aux[PACKET_SIZE] = "";
    char path[PACKET_SIZE];
    char* buffer;
    char buffer
    size_t size;

    recv(id, path, PACKET_SIZE, 0);
    strcat(completePath, name);
    strcat(completePath, path);

    recv(id, aux, PACKET_SIZE, 0);
    size = strtoul(aux, NULL, 0); 
    buffer = malloc(sizeof(char) * size);


    recv(id, buffer, size, 0);

    free(buffer);
}


#endif