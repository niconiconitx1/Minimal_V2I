#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define FORWARD 18
#define FORWARD2 23

#define Rlight	19
#define Llight	26


//sensor
#define TRIG 2

#define ECHO 3

int Distance();
void *live_distance();
void *live_motor();
void stop();
void right();
void go();
void left();

int distance=0, Rl, Ll;
char cmd;
char temp[100] = {0};

int main() {
	pthread_t tSensor;
	pthread_t tMotor;
	

	int pulse = 0;
	int Ll, Rl;
	int status, idx = 0;


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


	while(1) {
		//pthread_join(t_id,(void **)status);	
		while ((temp[idx] = getchar()) != EOF) {
			cmd = temp[0];	
			if  (idx == 1) {	
				idx = 0;
				break;
			}
			idx++;
		}
	}

	return 0;
}
int Distance() {

	digitalWrite(TRIG, LOW);
	delay(60);

	// Trigger input to generate sonic burst
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);

	// wait for start
	while (digitalRead(ECHO) == LOW);
	long startTime = micros();

	// wait for return signal
	while (digitalRead(ECHO) == HIGH);
	long travelTime = micros() - startTime;

	// dist = speed * time		=> travelTime * 0.0034
	// UltraSonic speed = 340 m/s => 0.034 cm/us
	// time = travelTime
	// but, check time is roundtrip time => ¹Ý¶ò
	return (travelTime / 2) * 0.034;
}

void go() {
	printf("Receive cmd : %c \n forward run \n", cmd);
	if (Ll == 0 && Rl == 0) {
		softPwmWrite(FORWARD, 60);
		softPwmWrite(FORWARD2, 60); 
	}
	else if (Ll == 1 && Rl == 0) {
		softPwmWrite(FORWARD, 55);
		softPwmWrite(FORWARD2, 20);
		//delay(500);
	}
	else if (Ll == 0 && Rl == 1) {
		softPwmWrite(FORWARD, 20);
		softPwmWrite(FORWARD2, 55);
		//delay(500);
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
	delay(700);
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
		printf("(Ll : %d)     Distance : %d    (Rl : %d)     cmd : %c \n", Ll,  distance, Rl, cmd);
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
