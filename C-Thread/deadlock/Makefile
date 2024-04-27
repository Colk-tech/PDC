.PHONY : all clean 

all: deadlock1 deadlock2 recursive

clean:
	rm -f deadlock1 deadlock2  recursive

deadlock1 : deadlock1.c
	gcc -Wall -o $@  $^ -pthread 

deadlock2 : deadlock2.c
	gcc -Wall -o $@  $^ -pthread 

recursive : recursive.c
	gcc -Wall -o $@  $^ -pthread 

