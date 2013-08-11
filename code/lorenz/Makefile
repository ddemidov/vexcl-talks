all: vexcl_naive vexcl_generated thrust

vexcl_naive: vexcl_naive.cpp
	g++ -o $@ -O3 -std=c++0x \
	    -I$(HOME)/work/vexcl \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    -lOpenCL -lboost_system \
	    $^

vexcl_generated: vexcl_generated.cpp
	g++ -o $@ -O3 -std=c++0x \
	    -I$(HOME)/work/vexcl \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    -lOpenCL -lboost_system \
	    $^

thrust: thrust.cu
	nvcc -o $@ -O3 -arch=sm_35 \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    $^

.PHONY: clean

clean:
	@rm -f vexcl_generated vexcl_naive
