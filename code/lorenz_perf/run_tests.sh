#!/bin/bash
ntry=5

Tesla=( lorenz_thrust_cu lorenz_vexcl_naive_cuda lorenz_vexcl_symb_cl lorenz_vexcl_symb_comp lorenz_vexcl_symb_cuda )
CPU=( lorenz_thrust_omp lorenz_vexcl_symb_cl lorenz_vexcl_symb_comp lorenz_vexcl_symb_jit )

for dev in Tesla CPU; do
    echo --- $dev ---
    export OCL_DEVICE=${dev}
    progs="$dev[*]"
    for p in ${!progs}; do
        echo --- ${p} ---
        for((n=256; n<=4194304; n*=2)); do
            echo "  n = ${n}"
            for k in $(seq ${ntry}); do
                echo "    k = ${k}"
                ./${p} ${n}
            done
        done
    done
done

