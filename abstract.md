### VexCL: Experiences in Developing a C++ Wrapper Library for OpenCL

VexCL is a C++ vector expression template library for fast GPGPU prototyping
and development. It provides convenient notation for various vector operations,
and generates OpenCL/CUDA kernels on the fly from C++ expressions.

Among the challenges met during the library development were the need to
support multiple backends (OpenCL/CUDA), the fact that the OpenCL compute
kernel language is C99 and thus lacks some conveniences of C++, etc.  The talk
provides brief overview of the library implementation and the C++ techniques
used to overcome the difficulties.
