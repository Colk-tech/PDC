.PHONY : all clean

all: nomutex mutex

clean:
	rm -f nomutex mutex

nomutex : nomutex.c
	gcc -Wall -o $@ $^ -pthread
mutex : mutex.c
	gcc -Wall -o $@ $^ -pthread 

