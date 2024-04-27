.PHONY : all clean;

all: reader1 reader2

clean:
	rm -f reader1 reader2

reader1: reader1.c
	gcc -Wall -o $@ $^ -pthread

reader2: reader2.c
	gcc -Wall -o $@ $^ -pthread
