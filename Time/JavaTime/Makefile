.PHONY : all clean run

all : Main.class

clean :
	rm -f *.class *.log

run : Main.java 
	java Main

Main.class : Main.java
	javac -encoding UTF-8 $^

MyThread.class : MyThread.java
	javac -encoding UTF-8 $^

