JAVAC     = javac
JAVAFLAGS = -cp .:../OthelloFramework.jar
SOURCES   = $(wildcard *.java)
CLASSES   = $(SOURCES:.java=.class)

all: $(CLASSES) testsuite.jar

testsuite.jar: $(CLASSES)
	jar -cf ../testsuite.jar *.class

%.class: %.java
	$(JAVAC) ${JAVAFLAGS} $<

clean:
	rm -f *.class
