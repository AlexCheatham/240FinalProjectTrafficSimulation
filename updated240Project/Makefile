# C = g++
# OBJS = simulator.o Animator.o VehicleBase.o
# EXECS = simulator

EXECS = simulation
OBJS = simulator.o Animator.o VehicleBase.o


#### use next two lines for mathcs* machines:
CC = g++
CCFLAGS = -std=c++17

all: $(EXECS)

simulator: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)

# all: $(OBJS)

# simulator : $(OBJS)
# 	$(C) -o simulator $(OBJS)

# simulator.o : simulator.cpp
# 	$(C) -c simulator.cpp

# Animator.o : Animator.cpp Animator.h
# 	$(C) -c Animator.cpp

# VehicleBase.o : VehicleBase.cpp VehicleBase.h
# 	$(C) -c VehicleBase.cpp

# clean:
# 	/bin/rm -f a.out $(OBJS)