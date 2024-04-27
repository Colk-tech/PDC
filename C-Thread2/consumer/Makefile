.PHONY : all clean;

all: consumer1 consumer2 consumer3

clean:
	rm -f consumer1 consumer2 consumer3

consumer1 : consumer1.c
	gcc -Wall -o $@ $^ -pthread

consumer2 : consumer2.c
	gcc -Wall -o $@ $^ -pthread

consumer3 : consumer3.c
	gcc -Wall -o $@ $^ -pthread
