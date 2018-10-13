CC = gcc
CFLAGS = -lwiringPi -lpthread -g -I./
SRC = .
CATDOORBIN = .

all: client

client: client_main.o client_com.o
	${CC} ${CFLAGS} $^ -o ${CATDOORBIN}/rasClient.out


clean:
	rm -f *.o
	rm -f ${CATDOORBIN}/*.out
