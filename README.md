### Converting generic C++ algorithms to OpenCL with VexCL library

CUDA and OpenCL differ in their handling of compute kernels compilation. In
NVIDIA’s framework the compute kernels are compiled to PTX code together with
the host program. PTX is a pseudo-assembler language which is compiled at
runtime for the specific NVIDIA device the kernel is launched on. Since PTX is
already very low-level, this just-in-time kernel compilation has low overhead.
In OpenCL the compute kernels are compiled at runtime from higher-level C-like
sources, adding an overhead which is particularly noticeable for smaller sized
problems. A portable pre-compilation to some low-level pseudo-code as in CUDA
is not feasible in OpenCL because of hardware agnosticism by design. This
distinction leads to higher initialization overheads of OpenCL programs, but at
the same time it allows to generate better optimized kernels for the problem at
hand. This possibility is explored in this work with help of the
[VexCL](https://github.com/ddemidov/vexcl) – an open source expression template
library designed to ease C++ development of OpenCL applications.

Given at the [4th International Workshop of GPU and MIC Solutions to Multiscale
Problems in Science and Engineering](http://gpu-smp2013.sccas.cn), Changchun,
China, July 30, 2013

Slides: https://speakerdeck.com/ddemidov/converting-generic-c-plus-plus-algorithms-to-opencl-with-vexcl-library
