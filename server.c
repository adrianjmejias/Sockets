#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[])
{
    int id, id_new, asd; // el identificador retornado se usa en todas las funciones de los sockets
    int tam;
    char buffer[100], bufferRes[100];
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
    bzero(&(server.sin_zero), 8);

    //Socket del servidor
    id = socket(AF_INET, SOCK_STREAM, 0);

    bind(id, (struct sockaddr*)&server, sizeof(struct sockaddr));
    listen(id, 5);

    while(1)
    {
        tam = sizeof(struct sockaddr_in);
        if ((id_new = accept(id,(struct sockaddr *)&client,&tam)) == -1) {
            printf("error en accept()\n");
            exit(-1);
        }
        printf("Se obtuvo una conexión desde %s\n", inet_ntoa(client.sin_addr));
		
		//read(id_new, buffer, 100);
        if ((asd =recv(id_new, opcion, 1, 0)) == -1) {
            printf("Error en recv() \n");
            exit(-1);
		}
		
        if(strcmp(opcion,"4") == 0)
        {
            printf("Se termina el ciclo.\n");
            break;
		}
		printf("Se selecciona %c", opcion);
		
		switch(opcion){
			case '1':
				cosasArrechisimas();
			break;
			case '2':
			break;
			case '3':
			break;
			default:
			break;

		}
        //printf("\nMensaje del cliente: %s\n\n", buffer);


        if(strcmp(buffer,"hola") == 0) strcpy(bufferRes,"vale");
        else if(strcmp(buffer,"epa") == 0) strcpy(bufferRes,"epale");
        else if(strcmp(buffer,"te quiero") == 0) strcpy(bufferRes,"yo no");
		else strcpy(bufferRes, "Mensaje recibido");
		
        send(id_new, bufferRes, 100,0);

        close(id_new);
    }


    close(id);
    return 0;
}

