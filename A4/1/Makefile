CC=gcc
CPP=g++

all: server client script

server:
	$(CC) server.c -o server
client:
	$(CC) client.c -o client
script:
	$(CPP) script.cpp -o script -std=c++11
clean:
	rm server client script

