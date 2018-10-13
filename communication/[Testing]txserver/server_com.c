#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>

#include "server_com.h"

#define LENBUFFER 512


int readSize(int nsd, int *filesize)
{
    int res=0;
    int size;
	int rcvnum;

    if((size = read(nsd, &rcvnum, sizeof(int))) <= 0) {
        printf("readBuff err\n");
        res = -1;
    } else {
		*filesize = rcvnum;
        printf("filesize : %d\n", *filesize);
    } 
	return res;
}
int receive_file2(char *filename,int filesize,int sfd){
    char *filebuf =NULL;
    int datalen;
    int recvlen;
    int remain_data=0;

    filebuf = (char*)malloc(filesize);
    if(!filebuf){
        printf("fail malloc\n");
        return -1;
    }

    FILE *f = fopen("/home/nvidia/project/server/txserver/test.txt","wb");
    if(!f){
        fprintf(stderr,"FIle could not be opened\n");
        return -1;
    }


    remain_data = filesize;
    printf("remain_data : %d \n",remain_data);
    // printf("\n\n===============%d============\n\n", recv(sfd,filebuf,filesize,0));


    while((recvlen= recv(sfd,filebuf,filesize,0))>0){
        printf("========================\n\n");
        fwrite(filebuf,sizeof(char),recvlen,f);
        remain_data-=recvlen;
        if(remain_data<=0){
            break;
        }
        printf("Receive %d bytes and we hope : %d bytes\n",recvlen,remain_data);
    }

    fprintf(stderr,"\t%d data packet(s) received\n",(filesize-remain_data));

    fprintf(stderr,"\t%d bytes written\n",(filesize-remain_data));

    fflush(stderr);
    fclose(f);
    if(filebuf){
        free(filebuf);
        filebuf = NULL;
    }
    return remain_data;
}
void receive_file(char *filename, int filesize, int sfd)
{
	int x;
	int i = 0, j = 0;

	char buffer[LENBUFFER];
	int datalen;

	FILE* f = fopen(filename, "wb");	// Yo!
	if(!f)
	{
		fprintf(stderr, "File could not be opened.\n");
		return;
	}
	if((x = recv(sfd, buffer, LENBUFFER-1, 0)) <= 0) {
		printf("error send() %d", x);
		return;
	}
	datalen = x;
	printf("\trecv()datalen %d", datalen);
	j++;

	while(1)
	{
		i += fwrite(buffer, 1, datalen, f);
		
		if((x = recv(sfd, buffer, LENBUFFER-1, 0)) <= 0)  {
			printf("error recv() %d", x);
			break;
		}
		datalen = x;
		printf("\trecv()datalen %d", datalen);
		j++;
	}
	
	fclose(f);
	fprintf(stderr, "\t%d data packet(s) received.\n", --j);	// j decremented because the last packet is EOT.
	fprintf(stderr, "\t%d byte(s) written.\n", i);
	fflush(stderr);
}
