CC=g++
CFLAGS=-pthread

all: parallel sequential

parallel: 
	$(CC) $(CFLAGS) -o parallel parallel.cpp

sequential:	
	$(CC) $(CFLAGS) -o sequential sequential.cpp

clean:
	rm parallel sequential