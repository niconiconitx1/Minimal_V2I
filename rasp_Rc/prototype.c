#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <stdlib.h>

#define FORWARD 18

#define FORWARD2 23

//sensor
#define TRIG 2

#define ECHO 3

void go();
void left();
int main(){


	int distance=0;
	int pulse=0;


	char temp;
	if(wiringPiSetupGpio()==-1){
		return -1;
	}
	pinMode(FORWARD,OUTPUT);
	softPwmCreate(FORWARD,0,100);

	pinMode(FORWARD2,OUTPUT);
	softPwmCreate(FORWARD2,0,100);
	printf("If you want to quit, press the 'q'\n");

	pinMode(TRIG,OUTPUT);

	pinMode(ECHO,INPUT);




	  
	while((temp=getchar())!=EOF)
	{
		digitalWrite(TRIG,LOW);
		delay(500);
		digitalWrite(TRIG,HIGH);
		delayMicroseconds(10);

		digitalWrite(TRIG,LOW);

		while(digitalRead(ECHO) == LOW);

		long startTime = micros();

		while(digitalRead(ECHO)==HIGH);

		long travelTime = micros() - startTime;



		int distance = travelTime / 58;

		printf("Distance:%dcm\n", distance);
		delay(100);

		if(temp=='q' && distance<20){
		
		softPwmWrite(FORWARD,0);

		softPwmWrite(FORWARD2,0);
		exit(1);
		}
		else if(temp=='l'){
		left();
		}
	
		else if(temp == 'r'){
		
		}
		else if(temp == 'u'){
		go();	
		}
		else if(temp=='d'){
		
		}
		else{
			printf("Please up down left rignt choose one\n");

		}
	}

	return 0;
}


void go(){


	softPwmWrite(FORWARD,70);

	softPwmWrite(FORWARD2,70);
	printf("forward run \n");
	delay(500);

	softPwmWrite(FORWARD,0);

	softPwmWrite(FORWARD2,0);
	printf("------------------------\n");
	delay(200);

}

void left(){

	softPwmWrite(FORWARD,40);

	softPwmWrite(FORWARD2,50);
	printf("forward run \n");
	delay(500);

	softPwmWrite(FORWARD,0);

	softPwmWrite(FORWARD2,0);
	printf("------------------------\n");
	delay(1000);

}
