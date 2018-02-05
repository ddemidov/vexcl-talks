#!/bin/bash

for p in lorenz_vexcl_{naive,symb}_{cuda,cl,comp,jit}; do
    mv ${p}_Tesla*.dat ${p}_gpu.dat
    mv ${p}_*CPU*.dat ${p}_cpu.dat
done
