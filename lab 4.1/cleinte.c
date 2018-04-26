#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define IO_SIZE 500
#define IN_SIZE 500
#define OUT_SIZE 500


int main (int argc, char* argv[]){

	if(argc != 3){
		printf("Se necesitan solo 2 argumentos, ip");
	}else{
		int socket; // socket descriptor
		int port = 123;;
		int msgSize = 0;
		char *IO[IO_SIZE];
		char *serverIP, *serverPort;
		struct sockaddr_in server;
		struct hostent *he;
		
		if((he=gethostbyname(argv[1])) == NULL){
			printf("Handlea excepcion");
			exit(-1);
		}
		
		//POR QUE COÑO EL GUION LO ESCRIBE CON EL CARACTER -
		
		//Conseguir data
		serverIP = argv[1];
		serverPort = argv[2];
		port = atoi(serverPort);
		
		server.sin_family = AF_INET;
		server.sin_addr = *((struct in_addr *) he->h_addr);
		server.sin_port = 
		
		//abrir socket
		if((socket = socket(PF_INET, SOCK_STREAM, IPROTO_TCP)) < 0){
			printf("Error al crear socket");
			exit(-1);
		}
		
		//hacer lo que voy a hacer
		
		for(;;){
			
		}
		
		//cerrar socket
		
		
		close(id)
		
		ser
		
	}
	
}
