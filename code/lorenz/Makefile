all: vexcl_naive vexcl_generated thrust cublas

vexcl_naive: vexcl_naive.cpp
	g++-4.8.1 -o $@ -O3 -std=c++0x \
	    -I$(HOME)/work/vexcl \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    -lOpenCL -lboost_system \
	    $^

vexcl_generated: vexcl_generated.cpp
	g++-4.8.1 -o $@ -O3 -std=c++0x \
	    -I$(HOME)/work/vexcl \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    -lOpenCL -lboost_system \
	    $^

thrust: thrust.cu
	nvcc -o $@ -O3 -arch=sm_35 \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    $^

cublas: cublas.cu
	nvcc -o $@ -O3 -arch=sm_35 \
	    -I$(HOME)/work/karsten/odeint-v2 \
	    -lcublas \
	    $^

.PHONY: clean

clean:
	@rm -f vexcl_generated vexcl_naive thrust cublas
