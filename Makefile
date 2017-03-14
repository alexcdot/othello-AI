CC          = g++
CFLAGS      = -std=c++11 -Wall -pedantic -ggdb
OBJS        = player.o board.o heuristic.o
PLAYERNAME  = 2001

all: $(PLAYERNAME) testgame

$(PLAYERNAME): $(OBJS) wrapper.o
	$(CC) -o $@ $^

testgame: testgame.o
	$(CC) -o $@ $^

testminimax: $(OBJS) testminimax.o
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

java:
	make -C java/

cleanjava:
	make -C java/ clean

testsuite:
	make -C testsuite/

cleantestsuite:
	make -C testsuite/ clean

clean:
	rm -f *.o $(PLAYERNAME) testgame testminimax

.PHONY: java testminimax testsuite
