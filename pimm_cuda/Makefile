NVCC = nvcc
NVCCFLAGS = --generate-code arch=compute_52,code=sm_52 --generate-code arch=compute_75,code=sm_75 --compiler-options '-fPIC'

#library
INC_DIRS = -I. -I./..

# cpu
PIMM_CUDA_MEMORY_MANAGEMENT_OBJ = cuda_memory_management.o
PIMM_CUDA_CONVERSIONS_OBJ = cuda_conversions.o
#PIMM_CUDA_UTILITIES_OBJ = cuda_utilities.o

all: $(PIMM_CUDA_MEMORY_MANAGEMENT_OBJ)

$(PIMM_CUDA_MEMORY_MANAGEMENT_OBJ): $(PIMM_CUDA_CONVERSIONS_OBJ)
	#$(PIMM_CUDA_UTILITIES_OBJ)
	$(NVCC) $(NVCCFLAGS) -c cuda_memory_management.cu $(INC_DIRS) -o $@

$(PIMM_CUDA_CONVERSIONS_OBJ): cuda_conversions.cu
	$(NVCC) $(NVCCFLAGS) -c $< $(INC_DIRS) -o $@

#$(PIMM_CUDA_UTILITIES_OBJ): cuda_utilities.cc
#	$(NVCC) $(NVCCFLAGS) -c $< $(INC_DIRS) -o $@

clean:
	rm -f $(PIMM_CUDA_MEMORY_MANAGEMENT_OBJ) $(PIMM_CUDA_CONVERSIONS_OBJ)
	# $(PIMM_CUDA_UTILITIES_OBJ)
