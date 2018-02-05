#!/usr/bin/python

import sys
import numpy as np
from chameleon import *
import matplotlib
matplotlib.use('Agg')
from pylab import *

if (len(sys.argv[1:]) > 0):
    outdir = sys.argv[1]
else:
    outdir = '.'

rc('font',   size=18)

#----------------------------------------------------------------------------
class display_params:
    def __init__(self, label, style, color, face='w'):
        self.label = label
        self.style = style
        self.color = color
        self.face  = face

#----------------------------------------------------------------------------
prm = {
        'lorenz_vexcl_symb_cl_cpu'   : display_params('OpenCL',        'o-', chameleon4, chameleon2),
        'lorenz_vexcl_symb_comp_cpu' : display_params('Boost.Compute', 'o-', chameleon4, chameleon1),
        'lorenz_vexcl_symb_jit_cpu'  : display_params('JIT',           'o-', chameleon2, chameleon4),

        'lorenz_vexcl_symb_cl_gpu'   : display_params('OpenCL',        'o-', chameleon4, chameleon2),
        'lorenz_vexcl_symb_comp_gpu' : display_params('Boost.Compute', 'o-', chameleon4, chameleon1),
        'lorenz_vexcl_symb_cuda_gpu' : display_params('CUDA',          'o-', chameleon2, chameleon4),
        }

cpu_sets = [
        'lorenz_vexcl_symb_cl_cpu',
        'lorenz_vexcl_symb_comp_cpu',
        'lorenz_vexcl_symb_jit_cpu',
        ]

gpu_sets = [
        'lorenz_vexcl_symb_cl_gpu',
        'lorenz_vexcl_symb_comp_gpu',
        'lorenz_vexcl_symb_cuda_gpu',
        ]

def get_data(fname):
    tab = np.loadtxt('code/lorenz_perf/' + fname + '.dat',
            delimiter='\t',
            dtype={'names': ('n', 'i', 't'), 'formats': ('i4', 'i4', 'f8')})

    ns = np.array(sorted(set(tab['n'])))
    ts = np.array([np.median( tab[tab['n'] == n]['t'] ) for n in ns])

    return (ns, ts)

figure(figsize=(14,7))
subplot(121)
for f in cpu_sets:
    data = get_data(f)
    loglog(data[0], data[1], prm[f].style, label=prm[f].label, ms=8, linewidth=2,
            color=prm[f].color, markeredgecolor=prm[f].color,
            markeredgewidth=2,  markerfacecolor=prm[f].face)

xlabel('N')
ylabel('T(sec)')
legend(loc='upper left', frameon=False)
title('Intel Core i7 920 @ 2.67GHz')

subplot(122)
for f in gpu_sets:
    data = get_data(f)
    loglog(data[0], data[1], prm[f].style, label=prm[f].label, ms=8, linewidth=2,
            color=prm[f].color, markeredgecolor=prm[f].color,
            markeredgewidth=2,  markerfacecolor=prm[f].face)

xlabel('N')
ylabel('T(sec)')
legend(loc='upper left', frameon=False)
title('NVIDIA Tesla K40c')

tight_layout()

savefig("{}/backends.pdf".format(outdir))
