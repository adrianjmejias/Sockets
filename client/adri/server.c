#include "util.h"


int main(){

    int mySocket;
    struct sockaddr_in myAddr;
    //Creamos socket
    if((mySocket = socket(PF_INET,SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        DieWithError("socket() error");
    }


    //Comunicamos


    //Cerramos
    if(close(mySocket) == -1)
    {
        DieWithError("Close() error");
    }

    return 0;
}