CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

#library
INC_DIRS = -I. -I./..

# cpu
PIMM_CPU_MANAGEMENT_OBJ = cpu_management.o
PIMM_CPU_CONVERSIONS_OBJ = pimm_cpu_conversions.o

all: $(PIMM_CPU_MANAGEMENT_OBJ)

$(PIMM_CPU_MANAGEMENT_OBJ): $(PIMM_CPU_CONVERSIONS_OBJ)
	$(CXX) $(CXXFLAGS) -c cpu_management.cpp $(INC_DIRS) -o $@

$(PIMM_CPU_CONVERSIONS_OBJ): conversions.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@

clean:
	rm -f $(PIMM_CPU_MANAGEMENT_OBJ) $(PIMM_CPU_CONVERSIONS_OBJ)
