#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include "util.h"
#include "colaT.h"
#define PATHSIZE 250

typedef struct comparaciones{
    Cola nom;
    int numDir;
    int numArch;
} comp;


void mandarCola(int id, Cola *B)
{
    int cont = B->tamanio;
    char* nombreArch;
    Cola_Ordenar(B);

    nodo *nodoActualB = B->primero;

    while(cont > 0)
    {
        nombreArch = nodoActualB->path; 
        send(id,nombreArch,1024,0);
        nodoActualB = nodoActualB->siguiente;
        cont--;
    }
}
   

void mensajesCliente (int id, char opcion[])
{
    int rec;
    char bufferRes[200];
   
    //Manda la opción elegida
    send(id, opcion, 2, 0);
    
    //Dependiendo de esa misma opcion pasarán otras cosas:
    if(strcmp(opcion,"1") == 0) 
    {
        
        comp client = recorrerArchivos("client");
        

        send(id, client.numDir, 10, 0); //Mandamos numero de archivos

        mandarCola(id, &client.nom);
        
    }
    else if(strcmp(opcion,"2") == 0) 
    {
        strcpy(bufferRes,"Esta opción aun no está implementada.\n\n");      
    }
    else if(strcmp(opcion,"3") == 0) 
    {
        strcpy(bufferRes,"Esta opción aun no está implementada.\n\n");
    }

    if ((rec =recv(id, bufferRes, 200, 0)) == -1)
    {
         printf("Error en recv() \n");
         exit(-1);
    }
    
    printf("\nRespuesta del servidor: %s\n\n", bufferRes);

}
      

int main(int argc, char const *argv[])
{
    //cliente
    int id,asd; // el identificador retornado se usa en todas las funciones de los sockets
    char opcion[2], bufferRes[200];
    
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

        //Opción del menu
        printf("ESCOJA UNA OPCION: ");
        scanf("%s", opcion);

        //Nos conectamos al servidor
        if(connect(id, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1)
        {
             printf("Error en connect()\n");
             exit(-1);
        }

        //write(id, opcion, 2);
        mensajesCliente(id, &opcion);
        
        if(strcmp(opcion,"4") == 0)
        {
            printf("Se termina el ciclo.\n"); 
            break;
        }  
    }
    
    close(id);

    return 0;
}
