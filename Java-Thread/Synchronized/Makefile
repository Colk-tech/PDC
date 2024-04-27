.PHONY : all run clean

all : Main.class ClientThread.class Account.class

clean :
	rm -f *.class *.log

run : Main.class ClientThread.class Account.class
	java Main

Main.class : Main.java 
	javac -encoding UTF-8 $^

Account.class : Account.java 
	javac -encoding UTF-8 $^

ClientThread.class : ClientThread.java 
	javac -encoding UTF-8 $^
