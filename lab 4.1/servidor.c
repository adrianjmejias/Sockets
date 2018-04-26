#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXPENDING 5
void DieWithError(char *errorMessage);
void HandleTCPClient(int clntSocket);

/* for atoi() */
/* for memset() */
/* for close() */
/* Maximum outstanding connection requests */
int main(int argc, char *argv[])
{
/* Error handling function */
/* TCP client handling function */
int servSock; /* Socket descriptor for server */
int clntSock; /* Socket descriptor for client */
struct sockaddr_in echoServAddr; /* Local address */
struct sockaddr_in echoClntAddr; /* Client address */
unsigned short echoServPort; /* Server port */
unsigned int clntLen; /* Length of client address data structure */
if (argc != 2) /* Test for correct number of arguments */
{
fprintf(stderr, "Usage: %s <Server Port>\n", argv[O]) ;
exit(l);
}
echoServPort = atoi(argv[l]); /* First arg: local port */
/* Create socket for incoming connections */
if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < O)
DieWithError( "socket () failed") ;
/* Construct local address structure */
memset(&echoServAddr, O, sizeof(echoServAddr)); /* Zero out structure */
echoServAddr.sin_family = AF_INET; /* Internet address family */
echoServAddr.sin_addr.s_addr = htonI(INADDR_ANY); /* Any incoming interface */
echoServAddr.sin_port = htons(echoServPort); /* Local port */
/* Bind to the local address */
if (bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < O)
DieWithError ( "bind () failed");
/* Mark the socket so it will listen for incoming connections */
if (listen(servSock, MAXPENDING) < O)
DieWithError("listen() failed") ;
for (;;) /* Run forever */
{
/* Set the size of the in-out parameter */
clntLen = sizeof(echoClntAddr);
/* Wait for a client to connect */
if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,
&clntLen)) < O)
DieWithError("accept() failed");
/* clntSock is connected to a client! */
printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
HandleTCPClient (clntSock) ;
}
/* NOT REACHED */
}
