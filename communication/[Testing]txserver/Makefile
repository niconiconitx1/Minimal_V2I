CC = gcc
CFLAGS = -pthread -g -I./
SRC = .
CATDOORBIN = .

all: server

server: server_main.o server_com.o 
	${CC} ${CFLAGS} $^ -o ${CATDOORBIN}/txServer.out


clean:
	rm -f *.o
	rm -f ${CATDOORBIN}/*.out
