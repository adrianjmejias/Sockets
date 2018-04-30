#include "util.h"


int main(int argc, char *argv[]){

    int mySocket;
    struct sockaddr_in serverAddr;
    //Creamos socket
    if((mySocket = socket(PF_INET,SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        DieWithError("socket() error");
    }

    //Seteamos la info del server al que queremos conectarnos
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ;
    serverAddr.sin_addr.s_addr = ;
    memset()
    //Connect
    if((connect(mySocket, (sockaddr *)&serverAddr, sizeof(sockaddr_in))) == -1)
    {
        DieWithError("connect() error");
    }else{
        printf("Conexion con %s", serverAddr.)
    }
    //Comunicamos

    do{


    }

    //Cerramos
    if(close(mySocket) == -1)
    {
        DieWithError("Close() error");
    }

    return 0;
}