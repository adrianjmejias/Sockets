#include "includes/todos_los_includes.h"
#include "includes/colaT.h"
#include "includes/recorrerArchivos.h"
#include "includes/segmentFile.h"

/*
61bb7583602fafd989a3fa05b96755b.jpg
*/
#define CARPETA "server"

int filtro3(int id_new, comp server)
{

    int tam;
    char bufferRes[PACKET_SIZE];
    // Comprobar contenido
    recv(id_new, bufferRes, PACKET_SIZE, 0);//de verdad
    tam = strtoul(bufferRes, NULL, 10);
    send(id_new, bufferRes, PACKET_SIZE, 0);//de mentira
    printf("%s\n", bufferRes);
    while(tam--)
    {
        Cola *serverC, *clientC = receiveNPackets(id_new);
        printf("******************\n");                
        printf("cola client \n");
        Leer(clientC);
        char pathsote[PACKET_SIZE];
        strcpy(pathsote, "server");
        strcat(pathsote, Desencolar(&server.nom).path);
        printf("pathsote %s--------------------------\n", pathsote);
        serverC = segmentFile(pathsote);
        printf("cola mia\n");
        Leer(serverC);
        printf("******************\n");
        if(!sonIguales(clientC, serverC))
        {
            strcpy(pathsote, "0");
            printf("las colas no son iguales por contenido\n");
            tam = -1; //salgo del loop
        }else
        {
            printf("las colas son iguales!!\n");
            strcpy(pathsote, "1");
        }
        
        send(id_new, pathsote, PACKET_SIZE, 0);
        if(recv(id_new, pathsote, PACKET_SIZE, 0) == -1) printf("Error.\n");;
        
        if(!strcmp(pathsote, "0")) return 0;
    }
    return 1;
}

int igualesNombre(Cola * cola, int id_new)
{
    int recibido;
    int    cont       = cola -> tamanio;
    nodo * nodoActual = cola -> primero;
    Cola colaC;
    char nombre[PACKET_SIZE], hash[HASH_SIZE];
    Cola_Ordenar(cola);
    Inicializar(&colaC);
    //Leer(cola);
    while (cont > 0)
    {
        if ((recv(id_new, nombre, PACKET_SIZE, 0)) == -1)
        {
            DeathByError("Error en recv() path\n");
        }else{
            send(id_new, "recibido", 8, 0);
            //printf("%s\n", nombre);
        }
        if (strcmp(nombre, (Desencolar(cola)).path) != 0) 
        {
            send(id_new, "Diferente", 9, 0);
            return 0;
        }
        else send(id_new, "Igual", 9, 0);
        cont--;
    }
    Leer(cola);
    return 1;

}

void opcion1(int id_new)
{
    char bufferRes[PACKET_SIZE];
    //comp client = recorrerArchivos("client");
    //Leer(&client.nom);
    comp server = recorrerArchivos(CARPETA);
    //Leer(&server.nom);

    //Primer filtro
    if ((recv(id_new, bufferRes, 4, 0)) == -1)
    {
        printf("Error en recv() 1\n");
        exit(-1);
    }

    int numDirClient = strtoul(bufferRes, NULL, 10);
    
    if ((recv(id_new, bufferRes, 4, 0)) == -1)
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

    else if (!igualesNombre(CopiarCola(&server.nom), id_new))
    {
        printf("No son iguales.\n");
    }
    
    //Tercer filtro
    else if(!filtro3(id_new, server))
    {
        printf("No son iguales.\n");
    }
    else
    {
        printf("Son iguales.\n");
    }
}

void opcion3(int id_new)
{
    char fileName[PACKET_SIZE];
    char pathCompleto[PACKET_SIZE];

    if (recv(id_new, fileName, PACKET_SIZE, 0) == -1)
    {
        printf("Error en recv() \n");
        exit(-1);
    }
    sprintf(pathCompleto, "server/%s", fileName);
    printf("%s\n", pathCompleto);
    if (remove(pathCompleto) == 0)
    {
        printf("El achivo %s fue borrado\n", pathCompleto);
    }else printf("El archivo no existe\n");
}

int accionesServer(int id_new)
{
    int recibido; // el identificador retornado se usa en todas las funciones de los sockets
    char opcion[2];

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
        opcion1(id_new);
    }
    else if(strcmp(opcion,"2") == 0) 
    {
        //strcpy(bufferRes,"Esta opción aun no está implementada.\n");      
    }
    else if(strcmp(opcion,"3") == 0) 
    {
        opcion3(id_new);
    }
    else 
    {
        //strcpy(bufferRes, "Esta opción aun no es válida.\n");
    }
    
    //send(id_new, bufferRes, 200,0);
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