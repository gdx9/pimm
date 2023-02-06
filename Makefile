CXX = g++
CXXFLAGS = -Wall -fPIC

LIB_PIMM = libpimm.so
PIMM_OBJ = pimm.o

# cpu
PIMM_CPU_OBJ=pimm_cpu.o

INC_DIRS = -I./pimm_cpu

all: $(LIB_PIMM)

$(PIMM_CPU_OBJ): ./pimm_cpu/conversions.cpp
	g++ -std=c++17 -c $(CXXFLAGS) ./pimm_cpu/conversions.cpp $(INC_DIRS) -o $(PIMM_CPU_OBJ)

$(PIMM_OBJ): $(PIMM_CPU_OBJ)
	g++ -std=c++17 -c pimm.cpp $(CXXFLAGS) -I. $(INC_DIRS) -o $(PIMM_OBJ)

$(LIB_PIMM): $(PIMM_OBJ)
	g++ -shared -o $(LIB_PIMM) $(PIMM_OBJ) $(PIMM_CPU_OBJ)

clean:
	rm -f $(LIB_PIMM) $(PIMM_OBJ) $(PIMM_CPU_OBJ)
