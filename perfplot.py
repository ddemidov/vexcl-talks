#!/usr/bin/python

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

rc('font',   size=22)
figure(num=1, figsize=(7,7))

barh(x + 0 * width, cublas, 0.5 * width, color=chameleon1)
barh(x + 1 * width, thrust, 0.5 * width, color=chameleon2)
barh(x + 2 * width, vexcl1, 0.5 * width, color=chameleon3)
barh(x + 3 * width, vexcl2, 0.5 * width, color=chameleon4)

text(cublas[0] + 10, (0.25 + 0) * width, 'cuBLAS',           verticalalignment='center')
text(thrust[0] + 10, (0.25 + 1) * width, 'Thrust',           verticalalignment='center')
text(vexcl1[0] + 10, (0.25 + 2) * width, 'VexCL',            verticalalignment='center')
text(vexcl2[0] + 10, (0.25 + 3) * width, 'VexCL (symbolic)', verticalalignment='center')

yticks([])
xticks([0, 100, 200, 300])
xlim([0, 360])
ylim([-0.5 * width, 4 * width])
xlabel('Compute time (sec)')

if quiet: savefig(outfile)
else:     show()
