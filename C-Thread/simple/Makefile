.PHONY : all clean 

all: simple1 simple2

clean:
	rm -f simple1 simple2

simple1 : simple1.c
	gcc -Wall -o $@  $^ -pthread 

simple2 : simple2.c
	gcc -Wall -o $@  $^ -pthread 

