
typedef struct Nodo {
   char *path, *hash; //Contenido del nodo
   struct Nodo *siguiente; //Puntero al siguiente nodo
} nodo;

typedef struct col {
   nodo *primero; //Puntero que apunta al primer elemento de la cola
   nodo *ultimo; //Puntero que apunta al ultimo elemento de la cola
   int tamanio; //Tamaño de la cola
} Cola;
  
/* Funciones con colas: */
void Inicializar ( Cola *cola){
  cola->primero = NULL;
  cola->ultimo = NULL;
  cola->tamanio = 0;
}

int colaVacia(const Cola *cola)
{
  int retvar=0;
  ;;
   if(cola->primero == NULL)
    retvar=1;
  ;
  
    return retvar;
}

void Insertar( Cola *cola, char * _path, char *_hash)
{

  nodo *nuevoNodo;
  nuevoNodo = malloc(sizeof(nodo)); //Creamos el nodo

  nuevoNodo->path = _path;
  nuevoNodo->hash = _hash;
  nuevoNodo->siguiente = NULL;
  
  if (cola->primero==NULL){
    cola->primero = nuevoNodo;
  }else{
    (cola->ultimo)->siguiente = nuevoNodo;
  }

  cola->ultimo = nuevoNodo;
  cola->tamanio++;
  
  
}

void Leer(const Cola *cola)
{
  
   if (cola->primero==NULL){
     
      
      
      return;  
   }
    
   int cont = cola->tamanio;
   nodo *nodoActual = cola->primero;

   while(cont > 0)
   {
      printf("%s\n", nodoActual->path);
      nodoActual = nodoActual->siguiente;
      cont--;
    }
    
    
}

nodo Desencolar(Cola *cola)
{
  nodo ret;
  
  if (cola->primero==NULL)
  {
    ret.path= NULL;
    return ret;
  }
  else
  {
    nodo *nodoAux;
    cola->tamanio--;
    nodoAux = cola->primero;
    ret = *nodoAux;
    cola->primero = nodoAux->siguiente;

  if(cola->primero == NULL)
  {
    cola->ultimo = NULL;
  }
  
  
  ret= *nodoAux;
  free(nodoAux);   
  return ret;
  }
   
}


void Nodo_Swap(nodo *nodo_a, nodo *nodo_b)
{
    char *path_temp = nodo_a->path;
    nodo_a->path = nodo_b->path;
    nodo_b->path = path_temp;
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

        //Print_Proceso(nodo_actual->data);
        //nodo_actual = nodo_actual->siguiente;
    }
    //return cola;
}

int sonIguales(Cola *A, Cola *B)
{
    int cont = A->tamanio;
    Cola_Ordenar(A);
    Cola_Ordenar(B);

    nodo *nodoActualA = A->primero;
    nodo *nodoActualB = B->primero;

    while(cont > 0)
    {

        if (strcmp(nodoActualA->path, nodoActualB->path)) return 0;
        nodoActualA = nodoActualA->siguiente;
        nodoActualB = nodoActualB->siguiente;
        cont--;
    }

    return 1;
}
