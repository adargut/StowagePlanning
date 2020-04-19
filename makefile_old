COMP = g++-8.3.0
OBJS = src/main.o src/AlgorithmError.o src/Container.o src/Error.o src/Instruction.o src/Port.o src/Ship.o src/Simulation.o src/StowageAlgorithm.o src/Utility.o src/WeightBalanceCalculator.o
EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
