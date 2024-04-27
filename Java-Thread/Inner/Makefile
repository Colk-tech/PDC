.PHONY : all clean run

all : Main.class Host.class Helper.class

clean :
	rm -f *.class *.log

run : Main.class Host.class Helper.class
	java Main

Main.class : Main.java
	javac -encoding UTF-8 $^

Helper.class : Helper.java
	javac -encoding UTF-8 $^

Host.class : Host.java
	javac -encoding UTF-8 $^
