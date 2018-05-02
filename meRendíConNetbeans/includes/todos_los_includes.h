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


#define PACKET_SIZE (1024) * 10 //10 MEGAS
#define PATHSIZE PACKET_SIZE
#define DeathByError(printfParam) printf(printfParam); exit(-1)
#define COMPROBAR 1
#define AGREGAR 2
#define ELIMINAR 3
#define SALIR 4

#endif