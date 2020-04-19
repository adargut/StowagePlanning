COMP = g++-8.3.0
OBJS = main.o AlgorithmError.o Container.o Error.o Instruction.o Port.o Ship.o Simulation.o StowageAlgorithm.o Utility.o WeightBalanceCalculator.o
EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
AlgorithmError.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/AlgorithmError.cpp
Container.o: 
	$(COMP) $(CPP_COMP_FLAG) -c src/Container.cpp
Error.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Error.cpp
Instruction.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Instruction.cpp
Port.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Port.cpp
Ship.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Ship.cpp
Simulation.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Simulation.cpp
StowageAlgorithm.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/StowageAlgorithm.cpp
Utility.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/Utility.cpp
WeightBalanceCalculator.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/WeightBalanceCalculator.cpp	
main.o:
	$(COMP) $(CPP_COMP_FLAG) -c src/main.cpp
clean:
	rm -f $(OBJS) $(EXEC)
