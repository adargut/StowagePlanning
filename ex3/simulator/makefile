COMP = g++-9.3.0
CommonDir = ../common
OBJS = main.o Simulation.o Error.o AlgorithmError.o Container.o DistanceToDestinationComparator.o GeneralUtility.o InputUtility.o ISO_6346.o OutputUtility.o Port.o Ship.o WeightBalanceCalculator.o AlgorithmManager.o AlgorithmRegistration.o Instruction.o SimulationUtility.o PreProcessingTasksProducer.o SimulationTasksProducer.o TravelData.o
EXEC = simulator
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -pthread
CPP_LINK_FLAG = -lstdc++fs -lpthread -ldl -export-dynamic #(-rdynamic)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@

main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Simulation.o: Simulation.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

Error.o: Error.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

SimulationUtility.o: SimulationUtility.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

AlgorithmRegistration.o: AlgorithmRegistration.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

PreProcessingTasksProducer.o: PreProcessingTasksProducer.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

SimulationTasksProducer.o: SimulationTasksProducer.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

TravelData.o: TravelData.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

AlgorithmError.o: $(CommonDir)/AlgorithmError.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

Container.o: $(CommonDir)/Container.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

DistanceToDestinationComparator.o: $(CommonDir)/DistanceToDestinationComparator.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

GeneralUtility.o: $(CommonDir)/GeneralUtility.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

InputUtility.o: $(CommonDir)/InputUtility.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

ISO_6346.o: $(CommonDir)/ISO_6346.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

Instruction.o: $(CommonDir)/Instruction.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

OutputUtility.o: $(CommonDir)/OutputUtility.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

Port.o: $(CommonDir)/Port.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

Ship.o: $(CommonDir)/Ship.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

WeightBalanceCalculator.o: $(CommonDir)/WeightBalanceCalculator.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

AlgorithmManager.o: $(CommonDir)/AlgorithmManager.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
