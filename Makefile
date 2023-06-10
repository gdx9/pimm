CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

#library
PIMM_CPU_DIR = pimm_cpu
INC_DIRS = -I. -I./$(PIMM_CPU_DIR)
PIMM_UTILS_OBJ = pimm_utils.o
PIMM_LIB_OBJ = pimm.o
LIB_PIMM = libpimm.so

# cpu
PIMM_CPU_MEMORY_MANAGEMENT_OBJ = ./$(PIMM_CPU_DIR)/cpu_memory_management.o
PIMM_CPU_CONVERSIONS_OBJ = ./$(PIMM_CPU_DIR)/cpu_conversions.o
PIMM_CPU_UTILITIES_OBJ = ./$(PIMM_CPU_DIR)/cpu_utilities.o

all: $(LIB_PIMM)

$(PIMM_UTILS_OBJ): pimm_utils.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@

$(PIMM_LIB_OBJ): pimm.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@

$(LIB_PIMM): $(PIMM_LIB_OBJ) $(PIMM_UTILS_OBJ)
	make -C ./pimm_cpu
	$(CXX) -shared -o $@ $^ $(PIMM_CPU_MEMORY_MANAGEMENT_OBJ) $(PIMM_CPU_CONVERSIONS_OBJ) $(PIMM_CPU_UTILITIES_OBJ)

clean:
	make -C ./$(PIMM_CPU_DIR) clean
	rm -f $(PIMM_UTILS_OBJ) $(PIMM_LIB_OBJ) $(LIB_PIMM)
