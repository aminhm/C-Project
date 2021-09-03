/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("usage: Port Number");
        exit(1);
    }

    int sockfd,newsocketfd, clinetlen,portnumber,n;
    struct sockaddr_in serverAddress, clientAddress;

    // zero out serverAddress
    bzero((char*) &serverAddress, sizeof(serverAddress));
    
    // port number
    portnumber = atoi(argv[1]);

    // setup server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portnumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // create socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    std::cout << serverAddress.sin_addr.s_addr << std::endl;
    // BIND
    int bindStatus = bind(sockfd,(struct sockaddr*) &serverAddress,sizeof(serverAddress));
    if (bindStatus < 0){
        error("Could not bind");
    }
    

    // listen
    
    listen(sockfd,5);   // cannot fail so no error cheking

    // accept client connection
    clinetlen = sizeof(clientAddress);
    newsocketfd = accept(sockfd, 
                 (struct sockaddr *) &clientAddress,(socklen_t *) &clinetlen); 
    if (newsocketfd < 0){
        error("Could not accept clinet socket");
    }

    // Define buffer
    char buffer[256];
    bzero(buffer,sizeof(buffer));

    // get user message
    n = read(newsocketfd,buffer,256);
    if (n < 0)
        error("Could not read from client");

    printf("From clinet: %s", buffer);
    
    // echo back
    char echoString[] = "Got your message";
    n = write(newsocketfd,echoString,strlen(echoString));
    if (n < 0)
        error("Could not echo back to user");
    
    return 0;
}
