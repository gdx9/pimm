CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

#library
INC_DIRS = -I. -I./..

# cpu
PIMM_CPU_MEMORY_MANAGEMENT_OBJ = cpu_memory_management.o
PIMM_CPU_CONVERSIONS_OBJ = cpu_conversions.o
PIMM_CPU_UTILITIES_OBJ = cpu_utilities.o

all: $(PIMM_CPU_MEMORY_MANAGEMENT_OBJ)

$(PIMM_CPU_MEMORY_MANAGEMENT_OBJ): $(PIMM_CPU_CONVERSIONS_OBJ) $(PIMM_CPU_UTILITIES_OBJ)
	$(CXX) $(CXXFLAGS) -c cpu_memory_management.cpp $(INC_DIRS) -o $@

$(PIMM_CPU_CONVERSIONS_OBJ): cpu_conversions.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@

$(PIMM_CPU_UTILITIES_OBJ): cpu_utilities.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@

clean:
	rm -f $(PIMM_CPU_MEMORY_MANAGEMENT_OBJ) $(PIMM_CPU_CONVERSIONS_OBJ) $(PIMM_CPU_UTILITIES_OBJ)
