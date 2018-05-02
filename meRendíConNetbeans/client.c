
#include "includes/colaT.h"
#include "includes/segmentFile.h2"
int main(int        argc,
         char const *argv[])
{
    // cliente
    int  id, asd;    // el identificador retornado se usa en todas las funciones de los sockets
    char opcion[2], bufferRes[2];

    if (argc != 3)
    {
        printf("Error por falta de parÃ¡metros\n");
        return 0;    /* Se termina el programa */
    }

    struct sockaddr_in server;
    struct sockaddr *serv_addr;
    struct hostent *he;

    he = gethostbyname(argv[1]);

    if (he == NULL)
    {
         DeathByError("Error de gethostbyname().\n");
        exit(-1);
    }

    int puerto = strtoul(argv[2], NULL, 10);

    // Estructura del servidor
    server.sin_family = AF_INET;
    server.sin_port   = htons(puerto);
    server.sin_addr   = *((struct in_addr*) he -> h_addr);

    bzero(&(server.sin_zero), 8);

    // Menu
    printf("MENU\n");
    printf("1) COMPROBAR ARCHIVOS\n");
    printf("2) AGREGAR ARCHIVO\n");
    printf("3) ELIMINAR ARCHIVO\n");
    printf("4) SALIR\n");

    // Socket cliente
    while (1)
    {
        // Creamos el socket
        id = socket(AF_INET, SOCK_STREAM, 0);
        


        // Nos conectamos al servidor
        if (connect(id, (struct sockaddr*) &server, sizeof(struct sockaddr)) == -1)
        {
            DeathByError("Error en connect()\n");
        }

        // OpciÃ³n del menu
        printf("ESCOJA UNA OPCION: ");
        scanf("%s", opcion);
        
        send(id, opcion, 2, 0);

        if (strcmp(opcion, "4") == 0)
        {
            printf("Se termina el ciclo.\n");

            break;
        }

        if ((asd = recv(id, bufferRes, 2, 0)) == -1)
        {
            DeathByError("Error en recv() \n");
        }

        printf("\nRespuesta del servidor: %s\n\n", bufferRes);
    }

    close(id);

    return 0;
}


//~ Formatted by Jindent --- http://www.jindent.com
