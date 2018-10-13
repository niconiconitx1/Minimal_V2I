#ifndef SERVER_COM_H
#define SERVER_COM_H

#define CMD_JPG 200
#define CMD_ACK 1000
#define CMD_ERR -100
#define CMD_CAT 300


int serverStart (void);

int readCmd(int nsd, int *cmdnum);
void receive_file(char *filename, int filesize,int sfd);
void closeSocket(int sfd);
int writeCmd(int sfd, int cmdnum);
#endif //SERVER_COM_H
