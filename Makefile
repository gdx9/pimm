CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

#library
PIMM_CPU_DIR = pimm_cpu
PIMM_CUDA_DIR = pimm_cuda
INC_DIRS = -I. -I./$(PIMM_CPU_DIR) -I./$(PIMM_CUDA_DIR)
PIMM_UTILS_OBJ = pimm_utils.o
PIMM_LIB_OBJ = pimm.o
LIB_PIMM = libpimm.so

# cpu
PIMM_CPU_MEMORY_MANAGEMENT_OBJ = ./$(PIMM_CPU_DIR)/cpu_memory_management.o
PIMM_CPU_CONVERSIONS_OBJ = ./$(PIMM_CPU_DIR)/cpu_conversions.o
PIMM_CPU_UTILITIES_OBJ = ./$(PIMM_CPU_DIR)/cpu_utilities.o

# cuda
PIMM_CUDA_MEMORY_MANAGEMENT_OBJ = ./$(PIMM_CUDA_DIR)/cuda_memory_management.o
PIMM_CUDA_CONVERSIONS_OBJ = ./$(PIMM_CUDA_DIR)/cuda_conversions.o

all: $(LIB_PIMM)

$(PIMM_UTILS_OBJ): pimm_utils.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@

$(PIMM_LIB_OBJ): pimm.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_DIRS) -o $@ -L/usr/local/cuda/lib64/ -lcudart -lcuda -ldl

$(LIB_PIMM): $(PIMM_UTILS_OBJ) $(PIMM_LIB_OBJ)
	make -C ./$(PIMM_CPU_DIR)
	make -C ./$(PIMM_CUDA_DIR)
	$(CXX) -shared -o $@ $^ $(PIMM_CPU_MEMORY_MANAGEMENT_OBJ) $(PIMM_CPU_CONVERSIONS_OBJ) $(PIMM_CPU_UTILITIES_OBJ) $(PIMM_CUDA_MEMORY_MANAGEMENT_OBJ) $(PIMM_CUDA_CONVERSIONS_OBJ) -L/usr/local/cuda/lib64/ -lcudart

clean:
	make -C ./$(PIMM_CPU_DIR) clean
	make -C ./$(PIMM_CUDA_DIR) clean
	rm -f $(PIMM_UTILS_OBJ) $(PIMM_LIB_OBJ) $(LIB_PIMM)
