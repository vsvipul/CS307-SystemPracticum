CC=g++
CFLAGS=-pthread

all: main main2 script
     
main: 
	$(CC) $(CFLAGS) -o main main.cpp

main2:	
	$(CC) $(CFLAGS) -o main2 main2.cpp

script: 
	$(CC) -o script script.cpp

clean:
	rm main main2 script