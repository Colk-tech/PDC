.PHONY : all clean run

all : Main.class Printer.class

clean :
	rm -f *.class *.log

run : Main.java Printer.class
	java Main

Main.class : Main.java
	javac -encoding UTF-8 $^

Printer.class : Printer.java
	javac -encoding UTF-8 $^
