.PHONY : all clean

all : sample

prof : sample.log

clean :
	rm -f sample sample.log
	rm -f gmon.out

sample : sample.c
	gcc -pg -o $@ $^

sample.log : sample
	./sample
	gprof $< gmon.out > $@
