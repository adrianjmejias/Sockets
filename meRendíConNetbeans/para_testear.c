#include "includes/todos_los_includes.h"
#include "includes/colaT.h"
#include "includes/segmentFile.h"



int main(){
    Cola *a = segmentFile("includes/segmentFile.h");
    int tam = a->tamanio;
    Leer(a);

    while(!colaVacia(a)){
        printf(Desencolar(a).path);
    }
    printf("\ntamanio %d\n", tam);
}