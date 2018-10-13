#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "client_com.h"

#include <wiringPi.h>
#include <softPwm.h>

#define FORWARD 18
#define FORWARD2 23

#define Rlight	19
#define Llight	26


//sensor
#define TRIG 2

#define ECHO 3



int distance=0, Rl, Ll, start_distance=0,end_distance=0;
char cmd;
char temp[100] = {0};
char lane;

int main(int argc, char* argv[] )
{
	int i=0;
	int sockfd;
	int size;
	int cmdnum;
	char temp;
	char request_to_client_command[256]={0,};
	// The variable of has sensing odj front of me and copy to buffer
	char recv_form_server[256];
	time_t curTime;
	int filesize;
	
	pthread_t tSensor;
	pthread_t tMotor;
	

	int pulse = 0;
	int Ll, Rl;
	int status, idx = 0;
	int lane_count=0;
	char *tok_point;
	if (wiringPiSetupGpio() == -1) {
		return -1;
	}
	pinMode(FORWARD, OUTPUT);
	softPwmCreate(FORWARD, 0, 100);

	pinMode(FORWARD2, OUTPUT);
	softPwmCreate(FORWARD2, 0, 100);
	printf("If you want to quit, press the 'q'\n");

	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	pinMode(Rlight, INPUT);
	pinMode(Llight, INPUT);


	if(pthread_create(&tSensor,NULL,live_distance,0)<0){
		perror("live_distance Thread create error: ");
	}
	if(pthread_create(&tMotor,NULL,live_motor,0)<0){
		perror("live_motor Thread create error: ");
	}
	if(argc != 2) {
		fprintf(stderr, "Usage : %s IP_address\n", argv[0]);
		exit(1);
	}
	
	printf("Please where is your line (Left -> l, Right-> r) : ");
	scanf("%c",&lane);
	cmd='u';

	while(1)
	{
		// 바퀴 지름 5.5cm

		//if somthing front of me, has requesting detecting obj to server
		// using "if" syntax 
		
		// printf("server requesting message what is front fo me : %s\n", request_to_client_command);
		if(distance<15){
		printf("distance==>%d\n",distance );
			softPwmWrite(FORWARD, 0);
			softPwmWrite(FORWARD2, 0);
			printf("Somthing there\n");
			printf("Start connetcServe..\n");
			if( (sockfd=connetcServer(argv[1])) < 0) {
				printf("Connect fail.\n");
				break;
			}
			printf("Connetecd.. sockfd : %d\n", sockfd);
			if(lane=='r'){
				request_to_client_command[0]='r';
				request_to_client_command[strlen(request_to_client_command)+1]='\0';
				printf("reqest : %s(Right lane)\n",request_to_client_command );
				send(sockfd, request_to_client_command, strlen(request_to_client_command), 0);
			}
			else if(lane=='l'){
				
				request_to_client_command[0]='l';
				request_to_client_command[strlen(request_to_client_command)+1]='\0';
				printf("reqest : %s(Left lane)\n",request_to_client_command );
				send(sockfd, request_to_client_command, strlen(request_to_client_command), 0);
				
			}
			else{
				cmd ='s';
			}
			// printf("\n@@@@@========================$$$\n");
			memset(request_to_client_command,0,sizeof(request_to_client_command));
			
			//서버로 부터 어디로 움직일지 데이터 받음
			if((size=recv(sockfd,recv_form_server,strlen(recv_form_server),0))>0){
				printf("Receive Success And We will go to [%s]\n",recv_form_server);
				
				// scanf("%s",request_to_client_command);
				tok_point=strtok(recv_form_server," ");
				while(tok_point!=NULL){
					if(*tok_point=='R'){
						cmd='r';
						lane= 'r';
						printf("Now Switch Right lane and go\n");
						break;
					}
					else if(*tok_point=='L'){
						cmd='l';
						lane= 'l';
						printf("Now Switch left lane and go\n");
						break;
					}

					else{

						cmd='s';
					}				
					tok_point=strtok(NULL," ");
					
				}

				printf(">> Complete execution !!!\n");

				memset(request_to_client_command,0,sizeof(request_to_client_command));
			}
			printf("$$$$recv_form_server: \n%s\n",recv_form_server);



		}
		
	}


	
	return 0; 
}



void go() {
	if (Ll == 0 && Rl == 0) {
		softPwmWrite(FORWARD, 40);
		softPwmWrite(FORWARD2, 40);
		delay(100); 
		softPwmWrite(FORWARD, 0);
		softPwmWrite(FORWARD2, 0); 
	}
	else if (Ll == 1 && Rl == 0) {
		softPwmWrite(FORWARD, 40);
		softPwmWrite(FORWARD2, 20);
		// 		delay(300); 
		// softPwmWrite(FORWARD, 0);
		// softPwmWrite(FORWARD2, 0);

		
	}
	else if (Ll == 0 && Rl == 1) {
		softPwmWrite(FORWARD, 20);
		softPwmWrite(FORWARD2, 40);
		// 		delay(300); 
		// softPwmWrite(FORWARD, 0);
		// softPwmWrite(FORWARD2, 0);
		
	}
}

void left() {
	printf("left turn \n");
	softPwmWrite(FORWARD, 0);
	softPwmWrite(FORWARD2, 70);
	delay(700);
	softPwmWrite(FORWARD, 70);
	softPwmWrite(FORWARD2, 70);
	delay(500);
	softPwmWrite(FORWARD, 60);
	softPwmWrite(FORWARD2, 0);
	delay(400);
	softPwmWrite(FORWARD, 60);
	softPwmWrite(FORWARD2, 60);
	delay(250);
}

void right() {

	printf("right turn\n");
	softPwmWrite(FORWARD, 60);
	softPwmWrite(FORWARD2, 0);
	delay(400);
	softPwmWrite(FORWARD, 70);
	softPwmWrite(FORWARD2, 70);
	delay(1250);
	softPwmWrite(FORWARD, 70);
	softPwmWrite(FORWARD2, 0);
	delay(500);
	softPwmWrite(FORWARD, 60);
	softPwmWrite(FORWARD2, 60);
	delay(250);
}

void stop() {
	softPwmWrite(FORWARD, 0);
	softPwmWrite(FORWARD2, 0);
}



void *live_motor(){

	while(1){
		// printf("(Ll : %d)     Distance : %d    (Rl : %d)     cmd : %c \n", Ll,  distance, Rl, cmd);
		if (cmd == 'q' || distance < 15) {
			softPwmWrite(FORWARD, 0);
			softPwmWrite(FORWARD2, 0);
			if (cmd == 'l') {
				left();
				stop();
				cmd = 0;
			}
		}
		else if (cmd == 'l') {
			left();
			stop();
			cmd = 0;
		}
		else if (cmd == 'r') {
			right();
			stop();
			cmd = 0;
		}
		else if (cmd == 'u') {
			go();
		}
		else if (cmd == 's' ) {
			stop();
		}
	}
}
void *live_distance(void *data){
	time_t curTime;

	while(1){
		time(&curTime);
		digitalWrite(TRIG,LOW);
		delay(60);
		digitalWrite(TRIG,HIGH);
		delayMicroseconds(10);

		digitalWrite(TRIG,LOW);

		while(digitalRead(ECHO) == LOW);

		long startTime = micros();

		while(digitalRead(ECHO)==HIGH);

		long travelTime = micros() - startTime;



		distance = (travelTime*0.5*0.034);
		Ll = digitalRead(Llight);
		Rl = digitalRead(Rlight);
	}
}

