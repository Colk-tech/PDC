.PHONY : all clean 

all: time0 time1 time2 time3

clean:
	rm -f time0 time1 time2 time3

time0 : time0.c
	gcc -o $@  $^
time1 : time1.c
	gcc -o $@  $^
time2 : time2.c
	gcc -o $@  $^ -lm
time3 : time3.c
	gcc -o $@  $^ -lm
