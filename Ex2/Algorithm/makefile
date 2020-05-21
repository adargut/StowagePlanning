COMP = g++
CommonDir = ../Common
OBJS = AlgorithmError.o Container.o DistanceToDestinationComparator.o GeneralUtility.o InputUtility.o Instruction.o ISO_6346.o OutputUtility.o Ship.o Instruction.o GenericAlgorithm.o
RANDOM_OBJS = RandomAlgorithm.o
SIMPLE_OBJS = SimpleAlgorithm.o
SHARED_OBJS = SimpleAlgorithm.so RandomAlgorithm.so
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC -fvisibility=hidden
CPP_LINK_FLAG = -lstdc++fs -shared

all: $(SHARED_OBJS)

SimpleAlgorithm.so: $(OBJS) $(SIMPLE_OBJS)
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^
	
RandomAlgorithm.so: $(OBJS) $(RANDOM_OBJS)
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^

SimpleAlgorithm.o: SimpleAlgorithm.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
RandomAlgorithm.o: RandomAlgorithm.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
GenericAlgorithm.o: GenericAlgorithm.cpp
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
	
Ship.o: $(CommonDir)/Ship.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $(CommonDir)/$*.cpp
	
clean:
	rm -f $(OBJS) $(SHARED_OBJS) $(SIMPLE_OBJS) $(RANDOM_OBJS)
