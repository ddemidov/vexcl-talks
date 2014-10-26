#!/usr/bin/python
# coding=utf-8

import numpy as np
from chameleon import *
import sys

if (len(sys.argv[1:]) > 0):
    import matplotlib
    matplotlib.use('Agg')
    outfile = sys.argv[1]
    quiet = True
else:
    quiet = False

from pylab import *

x = np.array([0])
width = 0.5

cublas = np.array([265.31]);
thrust = np.array([168.52]);
vexcl1 = np.array([169.24]);
vexcl2 = np.array([ 14.17]);

rc('font',**{'family':'sans-serif','sans-serif':['Monospace'], 'size':24})
rc('text', usetex=True)
rc('text.latex',unicode=True)
rc('text.latex',preamble=r'\usepackage[utf8]{inputenc}')
rc('text.latex',preamble=r'\usepackage[russian]{babel}')

figure(num=1, figsize=(7,7.5))

barh(x + 0 * width, cublas, 0.5 * width, color=chameleon1)
barh(x + 1 * width, thrust, 0.5 * width, color=chameleon2)
barh(x + 2 * width, vexcl1, 0.5 * width, color=chameleon3)
barh(x + 3 * width, vexcl2, 0.5 * width, color=chameleon4)

text(cublas[0] + 10, (0.25 + 0) * width, u'cuBLAS',           verticalalignment='center')
text(thrust[0] + 10, (0.25 + 1) * width, u'Thrust',           verticalalignment='center')
text(vexcl1[0] + 10, (0.25 + 2) * width, u'VexCL',            verticalalignment='center')
text(vexcl2[0] + 10, (0.25 + 3) * width, u'VexCL (монолитное ядро)', verticalalignment='center')

yticks([])
xticks([0, 100, 200, 300])
xlim([0, 360])
ylim([-0.5 * width, 4 * width])
xlabel(u'Время расчета (сек)')

if quiet: savefig(outfile)
else:     show()

