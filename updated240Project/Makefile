C = g++
OBJS = simulator

all: clean $(OBJS)

simulator : simulator.cpp
	$(C) -o simulator simulator.cpp

clean:
	/bin/rm -f a.out $(OBJS)