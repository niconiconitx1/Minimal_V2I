#ifndef CLIENT_COM_H
#define CLIENT_COM_H

#define CMD_JPG 200
#define CMD_ACK 1000
#define CMD_ERR -100
#define CMD_CAT 300


int connetcServer(char *ip);

void closeSocket(int sfd);
//int writeFileSize(char *filename,int sfd);
int Distance();
void *live_distance();
void *live_motor();
void stop();
void right();
void go();
void left();

#endif //CLIENT_COM_H
