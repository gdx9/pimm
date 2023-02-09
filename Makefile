CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

LIB_PIMM = libpimm.so
PIMM_OBJ = pimm.o

# cpu
PIMM_CPU_OBJ=pimm_cpu.o

INC_DIRS = -I./pimm_cpu

all: $(LIB_PIMM)

$(PIMM_CPU_OBJ): ./pimm_cpu/conversions.cpp
	$(CXX) $(CXXFLAGS) -o $(PIMM_CPU_OBJ) -c ./pimm_cpu/conversions.cpp $(INC_DIRS)

$(PIMM_OBJ): $(PIMM_CPU_OBJ)
	$(CXX) $(CXXFLAGS) -o $(PIMM_OBJ) -c pimm.cpp -I. $(INC_DIRS)

$(LIB_PIMM): $(PIMM_OBJ)
	$(CXX) -shared -o $(LIB_PIMM) $(PIMM_OBJ) $(PIMM_CPU_OBJ)

clean:
	rm -f $(LIB_PIMM) $(PIMM_OBJ) $(PIMM_CPU_OBJ)
