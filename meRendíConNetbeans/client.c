#include "includes/todos_los_includes.h"
#include "includes/colaT.h"
#include "includes/recorrerArchivos.h"

int accionesMenu(int id, struct sockaddr_in server)
{
    int recibido;
    char opcion[2];
    char bufferRes[200];
    //Opción del menu
    printf("ESCOJA UNA OPCION: ");
    scanf("%s", opcion);

    //Nos conectamos al servidor
    if(connect(id, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1)
    {
         printf("Error en connect()\n");
         exit(-1);
    }

    send(id, opcion, 2, 0);


    if(strcmp(opcion,"1") == 0)
    {
        comp client = recorrerArchivos("client");
        
        //Primer filtro
        
        //Numero de directorios
        sprintf(bufferRes, "%d", client.numDir);        
        send(id, bufferRes, 4, 0);
        
        //Numero de archivos
        sprintf(bufferRes, "%d", client.numArch);        
        send(id, bufferRes, 4, 0);

        //Nombres de archivos
        int cont = (client.nom).tamanio;
        nodo *nodoActual = (client.nom).primero;
        char nombre[200];

        while(cont > 0)
        {
            strcpy(nombre, nodoActual -> path);
            send(id, nombre, 200, 0);

            nodoActual = nodoActual -> siguiente;
            cont--;
            printf("hola\n");
        }
    }    

    if(strcmp(opcion,"4") == 0)
    {
        printf("Se termina el ciclo.\n"); 
        return 1;
    }
    
    if ((recibido = recv(id, bufferRes, 200, 0)) == -1)
    {
         printf("Error en recv() \n");
         exit(-1);
    }
    
    printf("\nRespuesta del servidor: %s\n\n", bufferRes);
    return 0;
}


int main(int argc, char const *argv[])
{
    //cliente
    int id; // el identificador retornado se usa en todas las funciones de los sockets
    
    if(argv[1] == NULL || argv[2] == NULL)
    {
        printf("Error por falta de parámetros\n");
        return 0;/*Se termina el programa*/
    }

    struct sockaddr_in server;
    struct sockaddr *serv_addr;
    struct hostent *he;
    he = gethostbyname(argv[1]);
    if (he==NULL)
    {
        printf("Error de gethostbyname().\n");
        exit(-1);
    }

    int puerto = strtoul(argv[2], NULL, 10);
    //Estructura del servidor
    server.sin_family = AF_INET;
    server.sin_port = htons(puerto);
    server.sin_addr = *((struct in_addr *)he->h_addr); 
    bzero(&(server.sin_zero), 8);

    //Menu 
    printf("MENU\n");
    printf("1) COMPROBAR ARCHIVOS\n");
    printf("2) AGREGAR ARCHIVO\n");
    printf("3) ELIMINAR ARCHIVO\n");
    printf("4) SALIR\n");

    //Socket cliente
    while(1)
    {   
        //Creamos el socket
        id = socket(AF_INET, SOCK_STREAM, 0);

        if(accionesMenu(id, server)) break;
        
    }
    
    close(id);

    return 0;
}