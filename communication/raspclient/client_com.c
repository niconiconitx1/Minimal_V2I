#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include "client_com.h"

#define LENBUFFER 512
#define BUFSIZE 1024
//define port and address of your server
#define SERV_TCP_PORT  7002  



int connetcServer(char *ipstr) {
    int sockfd;
    struct sockaddr_in serv_addr;

    bzero((void *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
//1. port setting
    //serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_addr.s_addr = inet_addr(ipstr);
	serv_addr.sin_port = htons(SERV_TCP_PORT);    
    /*2 TCP Socket Open */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        puts( "Client: Cannot open Stream Socket.");
        return -1;
    }
    
//3.connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        puts( "Client: Cannot connect the Server.");
        return -1;
    }
	return sockfd;
}
