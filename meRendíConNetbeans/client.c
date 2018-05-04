#include "includes/todos_los_includes.h"
#include "includes/colaT.h"
#include "includes/recorrerArchivos.h"
#include "includes/segmentFile.h"



void mandarNombres(int id, Cola *nombres)
{
    int cont = nombres -> tamanio;
    nodo *nodoActual = nombres -> primero;
    char nombre[PACKET_SIZE];
    char confirmar[10];

    while(cont > 0)
    {
        
        strcpy(nombre, nodoActual -> path);
        if (send(id, nombre, strlen(nombre) + 1, 0) == -1)
        {
            printf("Error en send() de nombres de archivo\n");
        }
        else
        {
            if (recv(id, confirmar, 8, 0) == -1)
            {
                printf("errooooooooor\n");
            }
            printf("%s\n", nombre);
        }
        
        if ((recv(id, confirmar, 9, 0)) == -1)
        {
            DeathByError("Error en recv() confirmar si es igual o distinto\n");
        }
        printf("%s\n", confirmar);
        if (strcmp(confirmar, "Diferente") == 0)
        {
            return;
        }

        nodoActual = nodoActual -> siguiente;
        cont--;
    }
}

int accionesMenu(int id, struct sockaddr_in server)
{
    int recibido;
    char opcion[2];
    char bufferRes[PACKET_SIZE];
    //Opción del menu
    printf("ESCOJA UNA OPCION: ");
    scanf("%s", opcion);


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
        //Leer(&client.nom);
        
        mandarNombres(id, CopiarCola(&client.nom));

        sprintf(bufferRes, "%d", client.nom.tamanio);
        send(id, bufferRes, strlen(bufferRes), 0);// de verdad
        recv(id, bufferRes, PACKET_SIZE, 0); //de mentira

        while(!colaVacia(&client.nom)){
            char pathsote[PACKET_SIZE];
            strcpy(pathsote, "client/");
            strcat(pathsote, Desencolar(&client.nom).path);
            Cola *serverC = segmentFile(pathsote);
            sendNPackets(id, segmentFile(pathsote));

            
        }
    }    
    else if(strcmp(opcion,"4") == 0)
    {
        printf("Se termina el ciclo.\n"); 
        return 1;
    }
    
    if ((recibido = recv(id, bufferRes, PACKET_SIZE, 0)) == -1)
    {
         printf("Error en recv() \n");
         exit(-1);
    }
    
    printf("\nRespuesta del servidor: %s\n", bufferRes);
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
        id = socket(AF_INET, SOCK_STREAM, 0);

        //Nos conectamos al servidor
        if(connect(id, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1)
        {
             printf("Error en connect()\n");
             exit(-1);
        }

        if(accionesMenu(id, server)) break;
        
    }
    
    close(id);

    return 0;
}