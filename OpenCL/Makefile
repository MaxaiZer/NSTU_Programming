all: build
build:
	g++ -I/usr/local/cuda/include/ -L/usr/local/cuda/lib64/ -lOpenCL --std=c++11 main.cpp -o lab3
	
run: build
	$(EXEC) CUDA_VISIBLE_DEVICES=1 ./lab3 $(args)
