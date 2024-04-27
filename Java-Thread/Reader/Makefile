.PHONY : all run clean

all : Main.class Data.class ReadWriteLock.class ReaderThread.class WriterThread.class

clean :
	rm -rf *.class *.log

run : Main.class Data.class ReadWriteLock.class ReaderThread.class WriterThread.class
	java Main

Main.class : Main.java 
	javac -encoding UTF-8 $^

Data.class : Data.java 
	javac -encoding UTF-8 $^

ReadWriteLock.class : ReadWriteLock.java 
	javac -encoding UTF-8 $^

ReaderThread.class : ReaderThread.java 
	javac -encoding UTF-8 $^

WriterThread.class : WriterThread.java 
	javac -encoding UTF-8 $^

