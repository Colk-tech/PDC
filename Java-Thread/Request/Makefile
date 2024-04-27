.PHONY : all run clean

all : Main.class ServerThread.class ClientThread.class Request.class RequestQueue.class

clean :
	rm -f *.class *.log

run : Main.class ServerThread.class ClientThread.class Request.class RequestQueue.class
	java Main

Main.class : Main.java 
	javac -encoding UTF-8 $^

Request.class : Request.java 
	javac -encoding UTF-8 $^

RequestQueue.class : RequestQueue.java 
	javac -encoding UTF-8 $^

ClientThread.class : ClientThread.java 
	javac -encoding UTF-8 $^

ServerThread.class : ServerThread.java 
	javac -encoding UTF-8 $^

