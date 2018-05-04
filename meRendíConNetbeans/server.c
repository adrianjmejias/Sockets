#include "includes/todos_los_includes.h"
#include "includes/colaT.h"
#include "includes/recorrerArchivos.h"

Cola *receiveNPackets(int idsocket)
{
    char IO[PACKET_SIZE];
    int tam;
    Cola *out;
    Inicializar(out);
    recv(idsocket, IO, PACKET_SIZE,0);
    tam = strtoul(IO, NULL, 10);
    send(idsocket, IO, strlen(IO),0);

    while(tam > 0)
    {
        memcpy(IO, "\0", PACKET_SIZE);
        Insertar(out, IO, NULL);
        tam--;
        recv(idsocket, IO, PACKET_SIZE,0);
        send(idsocket, IO, strlen(IO),0);
    }
    return out;
}

int igualesNombre(Cola * cola, int id_new)
{
    int recibido;
    int    cont       = cola -> tamanio;
    nodo * nodoActual = cola -> primero;
    Cola colaC;
    char nombre[PACKET_SIZE], hash[HASH_SIZE];
    
    Inicializar(&colaC);

    while (cont > 0)
    {

        if ((recibido = recv(id_new, nombre, PACKET_SIZE, 0)) == -1)
        {
            DeathByError("Error en recv() path\n");
        }else{
            send(id_new, "recibido", 8, 0);
            //printf(" hoola vale %s\n", nombre);
        }
        if (strcmp(nombre, (Desencolar(cola)).path) != 0) 
        {
            send(id_new, "Diferente", 9, 0);
            return 0;
        }
        else send(id_new, "Igual", 9, 0);
        cont--;
    }
    //Leer(cola);
    return 1;

}

int accionesServer(int id_new)
{
    int recibido; // el identificador retornado se usa en todas las funciones de los sockets
    char opcion[2], bufferRes[PACKET_SIZE];

    if ((recibido = recv(id_new, opcion, 2, 0)) == -1)
    {
        printf("Error en recv() \n");
        exit(-1);
    }
    
    if(strcmp(opcion,"4") == 0)
    {
        printf("Se termina el ciclo.\n"); 
        return 1;
    }

    printf("\nMensaje del cliente: %s\n", opcion);        
    
    if(strcmp(opcion,"1") == 0) 
    {
        
        //comp client = recorrerArchivos("client");
        //Leer(&client.nom);
        comp server = recorrerArchivos("server");
        //Leer(&server.nom);

        //Primer filtro
        if ((recibido = recv(id_new, bufferRes, 4, 0)) == -1)
        {
            printf("Error en recv() \n");
            exit(-1);
        }

        int numDirClient = strtoul(bufferRes, NULL, 10);
        
        if ((recibido = recv(id_new, bufferRes, 4, 0)) == -1)
        {
            printf("Error en recv() \n");
            exit(-1);
        }
        
        int numArchClient = strtoul(bufferRes, NULL, 10);

        if (numDirClient != server.numDir && numArchClient != server.numArch)
        {
            printf("No son iguales.\n");
        }

        //Segundo filtro

        else if (!igualesNombre(&server.nom, id_new))
        {
            printf("No son iguales.\n");
        }

        //Tercer filtro
        else if (0)
        {
            /* Comprobar contenido*/
        }
        else
        {
            printf("Las carpetas client y server son iguales!!\n");
        }
    }
    else if(strcmp(opcion,"2") == 0) 
    {
        strcpy(bufferRes,"Esta opción aun no está implementada.\n");      
    }
    else if(strcmp(opcion,"3") == 0) 
    {
        strcpy(bufferRes,"Esta opción aun no está implementada.\n");
    }
    else 
    {
        strcpy(bufferRes, "Esta opción aun no es válida.\n");
    }
    
    send(id_new, bufferRes, 200,0);
    if(close(id_new) == -1) printf("Error close\n");

    return 0;

}
    
int main(int argc, char const *argv[])
{
    int id, id_new, recibido; // el identificador retornado se usa en todas las funciones de los sockets
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
        if (accionesServer(id_new)) break;
        
    }
    
    
    if(close(id) == -1)
        printf("Error cerrando socket de server\n");
    return 0;
}