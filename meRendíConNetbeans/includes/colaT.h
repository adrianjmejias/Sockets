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

int sonIguales( Cola * colaA,  Cola * colaB)
{
    if (colaA -> primero == NULL && colaB -> primero == NULL)
    {
        return 1;
    }

    int cont = colaA -> tamanio;
    nodo * nodoActualA = colaA -> primero;
    nodo * nodoActualB = colaB -> primero;

    while (cont--)
    {
        if (strcmp(nodoActualA -> path, nodoActualB -> path)) return 0;
        char hashB[HASH_SIZE];
        //MDFile(nodoActualB->path, hashB);
        //if(strcmp(nodoActualA->hash, hashB)) return 0;
        nodoActualA = nodoActualA -> siguiente;
        nodoActualB = nodoActualB -> siguiente;
    }

    return 1;
}

Cola* CopiarCola(Cola* in){
    int tam = in->tamanio;
    Cola *out = malloc(sizeof(Cola));
    Inicializar(out);
    nodo *aux = in->primero;

    while(tam--){
        Insertar(out, aux->path, NULL);
        aux = aux->siguiente;
    }
    return out;
}

void Nodo_Swap(nodo *nodo_a, nodo *nodo_b)
{
    char *pro_temp = nodo_a->path;
    nodo_a->path = nodo_b->path;
    nodo_b->path = pro_temp;
}


void Cola_Ordenar(Cola *cola)
{
    nodo *nodo_actual;
    int ii, jj, tam_cola = cola->tamanio;

    for (ii = 1; ii < tam_cola; ++ii)
    {
        nodo_actual = cola->primero;
        for (jj = 0; jj < tam_cola - ii; ++jj)
        {
            if (strcmp(nodo_actual->siguiente->path, nodo_actual->path) > 0)
            {
                Nodo_Swap(nodo_actual, nodo_actual->siguiente);
            }
            nodo_actual = nodo_actual->siguiente;
        }

        //Print_Proceso(nodo_actual->path);
        //nodo_actual = nodo_actual->siguiente;
    }
    //return cola;
}

void Delete(char *path, Cola *cola)
{
    nodo ret;

    // printf("D");
    if (cola -> primero != NULL)
    {

        int tam = cola -> tamanio;

        nodo * nodoActual = cola -> primero;
        nodo * nodoAElim = cola -> primero -> siguiente;
        
        while(nodoAElim != NULL && tam > 0)
        {
            printf("%s\n", nodoActual -> path);
            printf("%s\n", nodoAElim -> path);

            if (!strcmp(nodoActual -> path, path))
            {
                
                break;
            }

            nodoActual = nodoActual -> siguiente;
            nodoAElim = nodoAElim -> siguiente;

            tam--;
        }

    }

}
#endif /* COLAT_H */




//~ Formatted by Jindent --- http://www.jindent.com
