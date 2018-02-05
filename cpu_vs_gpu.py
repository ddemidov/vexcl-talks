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
        'lorenz_thrust_omp'           : display_params('OpenMP',       'o-', chameleon2, chameleon4),
        'lorenz_vexcl_naive_cuda_gpu' : display_params('VexCL',        'o-', chameleon4, chameleon2),
        'lorenz_vexcl_symb_cuda_gpu'  : display_params('VexCL (symb)', 'o-', chameleon4, chameleon1),
        }

def get_data(fname):
    tab = np.loadtxt('code/lorenz_perf/' + fname + '.dat',
            delimiter='\t',
            dtype={'names': ('n', 'i', 't'), 'formats': ('i4', 'i4', 'f8')})

    ns = np.array(sorted(set(tab['n'])))
    ts = np.array([np.median( tab[tab['n'] == n]['t'] ) for n in ns])

    return (ns, ts)


datasets = [
        ['lorenz_thrust_omp', 'lorenz_vexcl_naive_cuda_gpu'],
        ['lorenz_thrust_omp', 'lorenz_vexcl_naive_cuda_gpu', 'lorenz_vexcl_symb_cuda_gpu']
        ]

for i,d in enumerate(datasets):
    ref = get_data(d[0])

    figure(figsize=(14,7))
    for f in d:
        data = get_data(f)

        subplot(121)
        loglog(data[0], data[1], prm[f].style, label=prm[f].label, ms=8, linewidth=2,
                color=prm[f].color, markeredgecolor=prm[f].color,
                markeredgewidth=2,  markerfacecolor=prm[f].face)

        subplot(122)
        loglog(data[0], ref[1] / data[1], prm[f].style, label=prm[f].label, ms=8, linewidth=2,
                color=prm[f].color, markeredgecolor=prm[f].color,
                markeredgewidth=2,  markerfacecolor=prm[f].face)

    subplot(121)
    xlabel('N')
    ylabel('T(sec)')
    legend(loc='upper left', frameon=False)

    subplot(122)
    xlabel('N')
    ylabel('T(OpenMP) / T')

    tight_layout()

    savefig("{}/cpu_vs_gpu_{}.pdf".format(outdir, i+1))
