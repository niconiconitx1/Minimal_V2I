#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "server_com.h"

#define SERV_TCP_PORT   7002 /* TCP Server port */

void* client_thread(void* data);
int count;
char filepath[256];
time_t curTime;


int main ( int argc, char* argv[] ) {
    int sockfd, newsockfd;
    struct sockaddr_in  cli_addr;
	struct sockaddr_in  serv_addr;
   	int clilen;
	int val_set;
	pthread_t thread_t;
 
 //1. create tcp socket to get sockfd
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0 ) {
        puts( "Server: Cannot open Stream Socket.");
        exit(1);
    }

    bzero((void *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //2. bind addr
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

	val_set = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &val_set, sizeof(val_set));	
 //3. bind your socket with the address info   
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))< 0) {
        puts( "Server: Cannot bind Local Address.");
        exit(1);
    }
//4. set listen args    
	listen(sockfd, 5);
	
	printf("TxServer started up @Target :%d. Waiting for client(s)...\n\n", SERV_TCP_PORT);
	
    clilen = sizeof( cli_addr );
	while(1) {
//5. call accept	
        newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
        if ( newsockfd < 0 ) {
			puts("Server: accept error!");
			break;
		}
		printf("Communication started with %s:%d\n", inet_ntoa(cli_addr.sin_addr), 
		  ntohs(cli_addr.sin_port));
		count++;
		printf("%dth client entered.\n", count);
		//1. thread create
		if(pthread_create(&thread_t, 0, client_thread, (void*)&newsockfd) < 0) {
			perror("pthread create error");
				exit(0);
		}		
	}
	//2. thread join
	pthread_join(thread_t, NULL);
	//3. close server socket
	close(sockfd);
	return 0;	
}

void* client_thread(void* data) 
{
	//4. assign data value to newsockfd
	int newsockfd = *(int*)data;
	int size;
    int cmd;
	int jpgsize;
	char buff_rcv[265];
	char buff_send[265];
	int somthing_detected=0;
	while(1) {
		// printf("Wait Cmd from client...\n");
		if((size = read(newsockfd, buff_rcv, 265))>0) {
			somthing_detected=1;
		printf(">> read cmd = %s\n", buff_rcv);
		//여기서 자동차가 뭔가에 근접했을때 앞의 물체 인식 요청함 Tx1에
		//TX1 에서 ./darknet 실행함. 그리고 darknet은 디텍팅한 값을 디텍트 로그에 씀
		}

		//Tx1이 요청을 받고 사진을 찍었을때

		if(somthing_detected==1){
			printf("Please seding message\n");
			//TX1이 쓴 로그를 읽어와서 클라이언트에 전송
			scanf("%s",buff_send);
			if((size = send(newsockfd,buff_send,265,0))>0){
				printf("Success sending command\n");
				// 여기에서 클라이언트에 보낸 로그 저장
			}

			//클라이언트가 받은 명령으로 동작후 완료하면 서버로 얼만큼 이동했는지 로그 보냄
			if((size = read(newsockfd, buff_rcv, 265))>0){
				printf("%s\n",buff_rcv );
			}

			somthing_detected=0;
		}

		
	}
	printf("%dth client quited \n", count );
	close(newsockfd);
}
