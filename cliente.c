#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
    //cliente
    int id,asd; // el identificador retornado se usa en todas las funciones de los sockets
    char buffer[100], bufferRes[100];
    char opcion;
    DIR dir;
    struct dirent* dent;
    if(argv[2] == NULL)
    {
        printf("Error por falta de par�metros\n");
        return 0;/*Se termina el programa*/
    }
	

    struct sockaddr_in server;
    struct sockaddr *serv_addr;
    struct hostent *he;

    if((he = gethostbyname(argv[1])) == NULL)
        DieWithError("Error de gethostbyname().\n");

    int puerto = strtoul(argv[2], NULL, 10);

    //Estructura del servidor
    server.sin_family = AF_INET;
    server.sin_port = htons(puerto);
    server.sin_addr = *((struct in_addr *)he->h_addr);

    bzero(&(server.sin_zero), 8);

	printf("MENU\n");
	printf("1) COMPROBAR ARCHIVOS\n");
	printf("2) AGREGAR ARCHIVO\n");
	printf("3) ELIMINAR ARCHIVO\n");
	printf("4) SALIR\n");
	
	
    //Socket cliente
    while(1)
    {
		printf("ESCOJA UNA OPCION: ")
		scanf("%c", &opcion);
        //Creamos el socket
        id = socket(AF_INET, SOCK_STREAM, 0);
        //scanf("%*c%[^\n]", buffer);
        //Nos conectamos al servidor
        if(connect(id, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) DieWithError("connect() error\n");
        //write(id, buffer, 100);
        send(id, opcion, 1, 0);
        if(strcmp(buffer,"exit") == 0)
        {
            printf("Se termina el ciclo.\n");
            break;
        }
        if ((asd =recv(id, bufferRes, 100, 0)) == -1)
            DieWithError("Error en recv() \n");
       
        printf("\nRespuesta del servidor: %s\n\n", bufferRes);

    }

    close(id);

    return 0;
}

