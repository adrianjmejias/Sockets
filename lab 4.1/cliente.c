#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define IO_SIZE 500

#define perror(msg) printf("%s", msg); exit(-1);

int main (int argc, char* argv[]){

	if(argc != 3){
		printf("Se necesitan solo 2 argumentos, ip");
	}else{
		int socket; // socket descriptor
		int port = 123;;
		int IOLen = 0;
		char *IO[IO_SIZE];
		char *serverAddr, *serverPort;
		struct sockaddr_in server;
		struct hostent *he;
		
		if((he=gethostbyname(argv[1])) == NULL)
			perror("Handlea excepcion");
		
		//POR QUE CO�O EL GUION LO ESCRIBE CON EL CARACTER -
		
		//Conseguir data
		serverAddr = argv[1];
		serverPort = argv[2];
		port = atoi(serverPort);
		
		server.sin_family = AF_INET;
		server.sin_addr = *((struct in_addr *) he->h_addr);//inet_addr(serverAddr);
		server.sin_port = htons(serverPort);

		bzero((&sever.sin_zero), 8);

		//abrir socket
		if((socket = socket(PF_INET, SOCK_STREAM, IPROTO_TCP)) < 0)
			perror("Error al crear socket");
		
		
		connect (socket, (struct sockaddr *) serverAddr, sizeof(serverAddr));
		//hacer lo que voy a hacer
		
		scanf("%s", IO);
		IOLen = strlen(IO);


		if(send(socket, IO, IOLen) != IOLen){
			perror("Error al enviar el mensaje");
			
		}

		IOLen = 0;
		printf("recibimos ");
		int bytesReceived = 0;
		while(IOLen < IO_SIZE - 1){
			if((bytesReceived = recv(socket, IO, IO_SIZE - 1, 0)) <= 0 )
				perror("err en recibir mensaje");

			IOLen += bytesReceived;
			IO[bytesReceived] = '\0';
			printf(IO);	
		}
		printf("\n");
		/*for(;;){
			
		}*/
		
		//cerrar socket
		
		
		close(id)
		exit(0);
		

	
}
