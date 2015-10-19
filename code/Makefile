all: hello-opencl hello-compute hello-vexcl

%: %.cpp
	g++ -o $@ $^ -std=c++11 -Wno-deprecated-declarations \
	    -I/home/demidov/work/compute/include \
	    -I/home/demidov/work/vexcl \
	    -lOpenCL -lboost_system
