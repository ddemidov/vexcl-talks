#!/bin/bash

export OCL_DEVICE=K20

for run in vexcl_generated vexcl_naive thrust cublas; do
    echo ${run}
    for((n=256; n<=4194304; n*=2)); do
        echo "  $n"
        for((a=1; a<=10; a++)); do
            echo "    $a"
            ./${run} >> ${run}.dat
        done
    done
done
