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

#endif