#ifndef RECORRERARCHIVOS
#define RECORRERARCHIVOS
#include "todos_los_includes.h"
typedef struct comparaciones{
    Cola nom;
    int numDir;
    int numArch;
} comp;

char* substr(char* cadena, int comienzo, int longitud)
{
    if (longitud == 0) 
        longitud = strlen(cadena) - comienzo;
    
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

#endif