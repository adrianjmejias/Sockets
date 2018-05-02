#ifndef INCLUDES
#define INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>

#define PACKET_SIZE 300
#define PATH_SIZE PACKET_SIZE

#define DeathByError(printfParam) printf(printfParam); exit(-1)



#endif