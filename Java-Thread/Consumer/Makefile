.PHONY : all clean run

all : Main.class EaterThread.class MakerThread.class Table.class

clean :
	rm -f *.class *.log

run : Main.class EaterThread.class MakerThread.class Table.class
	java Main

Main.class : Main.java
	javac -encoding UTF-8 $^
MakerThread.class : MakerThread.java
	javac -encoding UTF-8 $^
Table.class : Table.java
	javac -encoding UTF-8 $^
EaterThread.class : EaterThread.java
	javac -encoding UTF-8 $^
