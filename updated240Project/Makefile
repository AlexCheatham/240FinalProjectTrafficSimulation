C = g++
OBJS = simulator.o Animator.o VehicleBase.o

all: clean $(OBJS)

simulator : simulator.o Animator.o VehicleBase.o
	$(C) -o simulator $(OBJS)

simulator.o : simulator.cpp
	$(C) -c -g simulator.cpp

Animator.o : Animator.cpp Animator.h
	$(C) -c -g Animator.cpp

VehicleBase.o : VehicleBase.cpp VehicleBase.h
	$(C) -c -g VehicleBase.cpp

clean:
	/bin/rm -f a.out $(OBJS)