#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include "colaT.h"
#define PATHSIZE 250

typedef struct comparaciones{
    Cola nom;
    int numDir;
    int numArch;
} comp;

char* substr(char* cadena, int comienzo, int longitud)
{
    if (longitud == 0) 
        longitud = strlen(cadena)-comienzo;
    
    char *nuevo = (char*)malloc(sizeof(char) * (longitud+1));
    nuevo[longitud] = '\0';
    strncpy(nuevo, cadena + comienzo, longitud);
    
    return nuevo;
}

comp recorrerArchivos(char* path)
{
    /*ignora esto(??*/
    comp c;
    Cola aVisitar, nombres;
    struct dirent* dent;
    DIR *dirp;
    int contDir = 0, contArch = 0;

    Inicializar(&aVisitar);
    Inicializar(&nombres);
    Insertar(&aVisitar, path, NULL);

    //dirp = opendir(path);
    //Recorre los directorios
    while(1)
    {   
        nodo nodoAVisitar = Desencolar(&aVisitar);
        dirp = opendir(nodoAVisitar.path);
        
        //Recorre archivos dentro del directorio
        while(1)
        {
            dent = readdir(dirp);
            if (dent == NULL) break;
            char *pathGen= malloc(PATHSIZE* sizeof(char));
            sprintf(pathGen, "%s/%s", nodoAVisitar.path, dent->d_name);

            if (dent->d_type == DT_DIR)
            {
                if(strcmp(dent->d_name,".")!=0 && strcmp(dent->d_name,"..")!=0)
                { 
                    Insertar(&aVisitar, pathGen, NULL);
                    contDir++;
                }   
            }
            else
            {
                char *nombre = substr(pathGen, 6, strlen(pathGen));
                Insertar(&nombres, nombre, NULL);
                contArch++;
            }
        }

        if (colaVacia(&aVisitar)) break;
    }

    c.nom = nombres;
    c.numDir = contDir;
    c.numArch = contArch;/*
    printf("Cantidad de directorios: %d\n", contDir);
    printf("Cantidad de archivos: %d\n", contArch);*/
    return c;
}

int main(int argc, char const *argv[])
{
    int id, id_new, asd; // el identificador retornado se usa en todas las funciones de los sockets
    int tam;
    char opcion[2], bufferRes[200];
    
    if(argv[1] == NULL)
    { 
        printf("Error por falta de parametros.\n");
        return 0;
    }

    int puerto = strtoul(argv[1], NULL, 10);
    struct sockaddr_in server;//Infromacion del servidor
    struct sockaddr_in client;//Infromacion del cliente

    //Estructura server del servidor
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(puerto); // puerto donde escucha
    bzero(&(server.sin_zero),8);

    //Socket del servidor
    id = socket(AF_INET, SOCK_STREAM, 0);

    bind(id, (struct sockaddr*)&server, sizeof(struct sockaddr)); 
    listen(id, 5);

    while(1)
    {
        tam = sizeof(struct sockaddr_in);
    
        if ((id_new = accept(id,(struct sockaddr *)&client,&tam))==-1) 
        {
         printf("error en accept()\n");
         exit(-1);
        }

        printf("Se obtuvo una conexión desde %s\n", inet_ntoa(client.sin_addr));
        //read(id_new, opcion, 2);
        
        if ((asd =recv(id_new, opcion, 2, 0)) == -1)
        {
            printf("Error en recv() \n");
            exit(-1);
        }
        
        if(strcmp(opcion,"4") == 0)
        {
            printf("Se termina el ciclo.\n"); 
            break;
        }

        printf("\nMensaje del cliente: %s\n\n", opcion);        
        
        if(strcmp(opcion,"1") == 0) 
        {
            
            comp client = recorrerArchivos("client");
            //Leer(&client.nom);
            comp server = recorrerArchivos("server");
            //Leer(&server.nom);

            //Primer filtro
            if (client.numDir != server.numDir && client.numArch != server.numArch)
            {
                printf("No son iguales.\n\n");
            }
            //Segundo filto
            else if (!sonIguales(&client.nom, &server.nom))
            {
                printf("No son iguales.\n\n");
            }
            //Tercer filtro
            else if (0)
            {
                /* Comprobar contenido*/
            }
            else
            {
                printf("Las carpetas client y server son iguales!!\n\n");
            }
        }
        else if(strcmp(opcion,"2") == 0) 
        {
            strcpy(bufferRes,"Esta opción aun no está implementada.\n\n");      
        }
        else if(strcmp(opcion,"3") == 0) 
        {
            strcpy(bufferRes,"Esta opción aun no está implementada.\n\n");
        }
        else 
        {
            strcpy(bufferRes, "Esta opción aun no es válida.\n\n");
        }
        
        send(id_new, bufferRes, 200,0);

        close(id_new);
    }
    
    
    close(id);
    return 0;
}
