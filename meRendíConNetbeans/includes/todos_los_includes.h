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

//Done and tested
Cola *receiveNPackets(int idsocket)
{
   // printf("entrando receiveNPackets \n");
    
    char IO[PACKET_SIZE];
    int tam;
    Cola *out = malloc(sizeof(Cola));
    Inicializar(out);
    recv(idsocket, IO, PACKET_SIZE, 0);//recibir de verdad
    tam = strtoul(IO, NULL, 10);
    send(idsocket, IO, strlen(IO),0);//enviar inutil

    while(tam--)
    {
        CLEAN_BUFFER(IO, PACKET_SIZE);
        recv(idsocket, IO, PACKET_SIZE,0);//recibir de verdad 
        char *aux = malloc(sizeof(char) * strlen(IO));
        strcpy(aux,IO);
        Insertar(out, aux, NULL);

        send(idsocket, IO, strlen(IO),0); //enviar inutil
    }
    //printf("saliendo receiveNPackets \n");
    
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

#endif