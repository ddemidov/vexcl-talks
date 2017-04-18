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

rc('font',  size=22)
rc('axes',  labelcolor=chameleon2)
rc('axes',  edgecolor=chameleon2)
rc('axes',  facecolor=chameleon6)
rc('xtick', color=chameleon2)
rc('ytick', color=chameleon2)

figure(figsize=(7,7))

x = np.random.uniform(0, 1, 3000)
y = np.random.uniform(0, 1, 3000)

i = (x * x + y * y) < 1.0

plot(x[i==0], y[i==0], 'o', markersize=3, markeredgecolor=chameleon3, markerfacecolor=chameleon3)
plot(x[i==1], y[i==1], 'o', markersize=3, markeredgecolor=chameleon4, markerfacecolor=chameleon4)

x = np.linspace(0, 1, 100)
y = np.sqrt(1 - x * x)

#plot(x, y, '-', color=chameleon2, linewidth=2)

xticks([0, 0.5, 1])
yticks([   0.5, 1])
xlim([0,1])
ylim([0,1])
show()

if quiet: savefig(outfile, facecolor=chameleon6)
else:     show()

