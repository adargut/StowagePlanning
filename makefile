COMP = g++-8.3.0
OBJS = src/main.o src/AlgorithmError.o src/Container.o src/Error.o src/Instruction.o src/Port.o src/Ship.o src/Simulation.o src/StowageAlgorithm.o src/Utility.o src/WeightBalanceCalculator.o
EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
src/AlgorithmError.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/AlgorithmError.cpp
src/Container.o: 
	$(COMP) $(CPP_COMP_FLAG) -c src/Container.cpp
src/Error.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Error.cpp
src/Instruction.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Instruction.cpp
src/Port.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Port.cpp
src/Ship.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Ship.cpp
src/Simulation.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Simulation.cpp
src/StowageAlgorithm.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/StowageAlgorithm.cpp
src/Utility.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Utility.cpp
src/WeightBalanceCalculator.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/WeightBalanceCalculator.cpp	
src/main.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/main.cpp
clean:
	rm -f $(OBJS) $(EXEC)
