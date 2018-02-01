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
        'cpu'             : display_params('OpenMP',     'o-', chameleon2, chameleon4),
        'vexcl_naive'     : display_params('VexCL',      'o-', chameleon4, chameleon2),
        }

def get_data(fname):
    tab = np.loadtxt('code/lorenz/' + fname + '.dat',
            delimiter=' ',
            dtype={'names': ('n', 't'), 'formats': ('i4', 'f8')})

    ns = np.array(sorted(set(tab['n'])))
    ts = np.array([np.median( tab[tab['n'] == n]['t'] ) for n in ns])

    return (ns, ts)

ref = get_data('cpu')

devices = ['cpu', 'vexcl_naive']

figure(figsize=(14,7))
for f in devices:
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
ylim([5e-2, 1e4])
legend(loc='upper left', frameon=False)

subplot(122)
xlabel('N')
ylabel('T(OpenMP) / T')
ylim([5e-2, 3e1])

tight_layout()

savefig("{}/perf.pdf".format(outdir))
