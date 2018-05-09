#include "includes/todos_los_includes.h"
#include "includes/colaT.h"
#include "includes/recorrerArchivos.h"
#include "includes/segmentFile.h"

int filtro3(int id, comp client)
{
    char bufferRes[PACKET_SIZE];

    sprintf(bufferRes, "%d", client.nom.tamanio);
    send(id, bufferRes, strlen(bufferRes), 0);// de verdad
    recv(id, bufferRes, PACKET_SIZE, 0); //de mentira
    int result = 1;
    int tam = client.nom.tamanio;
    while(tam--)
    {    
        char pathsote[PACKET_SIZE];
        CLEAN_BUFFER(pathsote, PACKET_SIZE);
        strcpy(pathsote, "client");
        strcat(pathsote, Desencolar(&client.nom).path);
        
        sendNPackets(id, segmentFile(pathsote));

        CLEAN_BUFFER(pathsote, PACKET_SIZE);

        recv(id, pathsote, PACKET_SIZE, 0);
        send(id, pathsote, strlen(pathsote), 0);

        result = strtoul(pathsote, NULL, 10);  
        if (!result) return result;
    }
    //char *re = (result)? "si": "no"; 
    //printf("las colas %s son iguales", re);
    return result;
}

int mandarNombres(int id, Cola *nombres)
{
    int cont = nombres -> tamanio;
    nodo *nodoActual = nombres -> primero;
    char nombre[PACKET_SIZE];
    char confirmar[10];
    Cola_Ordenar(nombres);
    //Leer(nombres);

    while(cont > 0)
    {
        //printf("hooola\n");
        CLEAN_BUFFER(nombre, PACKET_SIZE);
        strcpy(nombre, nodoActual -> path);
        //printf("%s\n", nombre);
        if (send(id, nombre, strlen(nombre), 0) == -1)
        {
            printf("Error en send() de nombres de archivo\n");
        }
        else
        {
            if (recv(id, confirmar, 8, 0) == -1)
            {
                printf("errooooooooor\n");
            }
            //printf("%s\n", nombre);
        }
        
        if ((recv(id, confirmar, 9, 0)) == -1)
        {
            DeathByError("Error en recv() confirmar si es igual o distinto\n");
        }
        //printf("%s\n", confirmar);
        if (strcmp(confirmar, "Diferente") == 0)
        {
            return 0;
        }

        nodoActual = nodoActual -> siguiente;
        cont--;
    }

    return 1;
}

void opcion1(int id)
{
    char bufferRes[PACKET_SIZE];
    comp client = recorrerArchivos("client");
    //Primer filtro
    
    //Numero de directorios
    sprintf(bufferRes, "%d", client.numDir);        
    send(id, bufferRes, 4, 0);
    
    //Numero de archivos
    sprintf(bufferRes, "%d", client.numArch);        
    send(id, bufferRes, 4, 0);

    //Nombres de archivos
    ////Leer(&client.nom);
    
    if(!mandarNombres(id, CopiarCola(&client.nom)))
    {
        printf("No son iguales\n");
    }
    else if(!filtro3(id, client))
    {
        printf("No son iguales\n");
    }
    else
    {
        printf("Son iguales wooo\n");
    }
    
}

void opcion2(int id)
{
    char fileName[PACKET_SIZE];
    char pathCompleto[PACKET_SIZE];

    printf("INGRESE EL NOMBRE DEL ARCHIVO A AGREGAR:\n");
    scanf("%*c%[^\n]", fileName);
    strcpy(pathCompleto, buscarNombre("client",fileName));
    printf("%s\n", pathCompleto);
    if (!strcmp(pathCompleto, "\0"))
    {
        send(id,"N0_3X1ST3:4rCH1V0", PACKET_SIZE, 0);
        printf("El archivo no existe en la carpeta cliente.\n");
    }
    else
    {
        send(id, fileName, PACKET_SIZE, 0);
        send(id, pathCompleto, PACKET_SIZE, 0);
        //Adri destácate
        //Mandar paquetish
        //printf("%s\n", buscarNombre("client",fileName));
    }
     
}

void opcion3(int id)
{
    char fileName[PACKET_SIZE];
    char pathCompleto[PACKET_SIZE];

    printf("INGRESE EL NOMBRE DEL ARCHIVO A ELIMINAR\n");
    scanf("%*c%[^\n]", fileName);
    
    send(id, fileName, PACKET_SIZE, 0);
    sprintf(pathCompleto, "client/%s", fileName);

    if (remove(pathCompleto) == 0)
    {
        printf("SE HA ELIMINADO %s\n", fileName);
    }else printf("NO SE ENCUENTRA EL ARCHIVO.\n");
}

int accionesMenu(int id, struct sockaddr_in server)
{
    int recibido;
    char opcion[2];
    //Opción del menu
    printf("ESCOJA UNA OPCION: ");
    scanf("%s", opcion);


    send(id, opcion, 2, 0);


    if(strcmp(opcion,"1") == 0)
    {
        opcion1(id);
        
    }
    else if (strcmp(opcion,"2") == 0)
    {
        opcion2(id);
    }
    else if (strcmp(opcion,"3") == 0)
    {
        opcion3(id);
    }    
    else if(strcmp(opcion,"4") == 0)
    {
        printf("Se termina el ciclo.\n"); 
        return 1;
    }
    // if ((recibido = recv(id, bufferRes, PACKET_SIZE, 0)) == -1)
    // {
    //      printf("Error en recv()asd \n");
    //      exit(-1);
    // }
    
    //printf("\nRespuesta del servidor: %s\n", bufferRes);
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