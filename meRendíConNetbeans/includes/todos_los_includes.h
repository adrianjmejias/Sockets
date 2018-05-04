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
int MDFile(char* filename, char hashValue[HASH_SIZE]);

#define PACKET_SIZE 1024 //1 MEGAS
#define PATHSIZE PACKET_SIZE // debería tener un _ pero 
#define DeathByError(printfParam) printf(printfParam); exit(-1)
#define COMPROBAR 1
#define AGREGAR 2
#define ELIMINAR 3
#define SALIR 4

Cola *receiveNPackets(int idsocket)
{
    char IO[PACKET_SIZE];
    int tam;
    Cola *out;
    Inicializar(out);
    recv(idsocket, IO, PACKET_SIZE,0);//recibir
    tam = strtoul(IO, NULL, 10);
    send(idsocket, IO, strlen(IO),0);//enviar

    while(tam > 0)
    {
        memcpy(IO, "\0", PACKET_SIZE);
        recv(idsocket, IO, PACKET_SIZE,0);//recibir buffer

        Insertar(out, IO, NULL);

        send(idsocket, IO, strlen(IO),0); //enviar
        tam--;
    }
    return out;
}

void sendNPackets(int idsocket, Cola *in)
{
    char IO[PACKET_SIZE];
    sprintf(IO, "%d", in -> tamanio);
    send(idsocket, IO, strlen(IO),0);//enviar
    recv(idsocket, IO, PACKET_SIZE,0);//recibir
    while(!colaVacia(in))
    {
        memset(IO, '\0', PACKET_SIZE);
        strcpy(IO, Desencolar(in).path);
        send(idsocket, IO, strlen(IO),0);//enviar
        recv(idsocket, IO, PACKET_SIZE,0);//recibir

    }
}

#endif