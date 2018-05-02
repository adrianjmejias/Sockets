/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   colaT.h
 * Author: FliaMejias
 *
 * Created on April 30, 2018, 1:09 AM
 */

#ifndef COLAT_H
#define COLAT_H

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
#define PATH_SIZE PACKET_SIZE
#define DeathByError(printfParam) printf(printfParam); exit(-1)
#define COMPROBAR 1
#define AGREGAR 2
#define ELIMINAR 3
#define SALIR 4

typedef struct Nodo
{
    char * path, *hash;        // Contenido del nodo
    struct Nodo *siguiente;    // Puntero al siguiente nodo
} nodo;


typedef struct col
{
    nodo * primero;    // Puntero que apunta al primer elemento de la cola
    nodo * ultimo;     // Puntero que apunta al ultimo elemento de la cola
    int    tamanio;    // Tamaño de la cola
} Cola;


/* Funciones con colas: */
void Inicializar(Cola * cola)
{
    cola -> primero = NULL;
    cola -> ultimo  = NULL;
    cola -> tamanio = 0;
}

int colaVacia(const Cola * cola)
{
    int retvar = 0;
        // printf("CV");

    if (cola -> primero == NULL)
    {
        retvar = 1;
    }

    // printf("CV");

    return retvar;
}

void Insertar(Cola * cola,
              char * _path,
              char * _hash)
{
    nodo * nuevoNodo;

    nuevoNodo              = malloc(sizeof(nodo));    // Creamos el nodo
    nuevoNodo -> path      = _path;
    nuevoNodo -> hash      = _hash;
    nuevoNodo -> siguiente = NULL;
    
    // printf("I");
    if (cola -> primero == NULL)
    {
        cola -> primero = nuevoNodo;
    }
    else
    {
        (cola -> ultimo) -> siguiente = nuevoNodo;
    }

    cola -> ultimo = nuevoNodo;

    cola -> tamanio++;

}

void Leer(const Cola * cola)
{
    // printf("L");
    if (cola -> primero == NULL)
    {
        // printf("La cola está vacia\n");
        // printf("L");
        return;
    }

    int    cont       = cola -> tamanio;
    nodo * nodoActual = cola -> primero;

    while (cont > 0)
    {
        printf("%s\n", nodoActual -> path);

        nodoActual = nodoActual -> siguiente;

        cont--;
    }

    // printf("L");
}

nodo Desencolar(Cola * cola)
{
    nodo ret;

    // printf("D");
    if (cola -> primero == NULL)
    {
        // printf("D");
        // printf("No hay cola.\n");
        ret.path = NULL;

        return ret;
    }
    else
    {
        nodo * nodoAux;

        cola -> tamanio--;

        nodoAux         = cola -> primero;
        ret             = *nodoAux;
        cola -> primero = nodoAux -> siguiente;

        if (cola -> primero == NULL)
        {
            cola -> ultimo = NULL;
        }

        // printf("D");

        ret = *nodoAux;

        free(nodoAux);

        return ret;
    }
}

Cola* recorrerArchivos(char * path)
{
    /* ignora esto(?? */
    Cola aVisitar;
    Cola nombres = *((Cola*) malloc(sizeof(nombres)));
    struct dirent *dent;


    DIR * dirp;
    int   contDir  = 0,
          contArch = 0;

    Inicializar(&aVisitar);
    Inicializar(&nombres);
    Insertar(&aVisitar, path, NULL);

    // dirp = opendir(path);
    nodo nodoAVisitar = Desencolar(&aVisitar);

    dirp = opendir(nodoAVisitar.path);

    while (1)
    {
        dent = readdir(dirp);

        if (dent == NULL)
        {
            break;
        }

        char * pathGen = malloc(PATH_SIZE * sizeof(char));

        sprintf(pathGen, "%s/%s", nodoAVisitar.path, dent -> d_name);

        if (dent -> d_type == DT_DIR)
        {
            if ((strcmp(dent -> d_name, ".") != 0) && (strcmp(dent -> d_name, "..") != 0))
            {
                Insertar(&aVisitar, pathGen, NULL);
                contDir++;
            }
        }
        else if (dent -> d_type == DT_REG)
        {
            Insertar(&nombres, pathGen, NULL);
            contArch++;
        }
    }

    Leer(&nombres);
    printf("Cantidad de directorios: %d\n", contDir);
    printf("Cantidad de archivos: %d\n", contArch);
    return(&nombres);
}
#endif /* COLAT_H */


//~ Formatted by Jindent --- http://www.jindent.com
