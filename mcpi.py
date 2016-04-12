#!/usr/bin/python
# coding=utf-8

import sys
import numpy as np
from chameleon import *

if (len(sys.argv[1:]) > 0):
    import matplotlib
    matplotlib.use('Agg')
    outfile = sys.argv[1]
    quiet = True
else:
    quiet = False

from pylab import *
style.use('seaborn-white')

rc('font',   size=22)
figure(figsize=(7,7))

x = np.random.uniform(0, 1, 3000)
y = np.random.uniform(0, 1, 3000)

i = (x * x + y * y) < 1.0

plot(x[i==0], y[i==0], 'o', markersize=3, markeredgecolor=chameleon1, markerfacecolor=chameleon1)
plot(x[i==1], y[i==1], 'o', markersize=3, markeredgecolor=chameleon2, markerfacecolor=chameleon2)

x = np.linspace(0, 1, 100)
y = np.sqrt(1 - x * x)

plot(x, y, '-', color=chameleon3, linewidth=2)

xticks([0, 0.5, 1])
yticks([   0.5, 1])
show()

if quiet: savefig(outfile)
else:     show()

