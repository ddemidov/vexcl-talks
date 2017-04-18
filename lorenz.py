#!/usr/bin/python
# coding=utf-8

from scipy.integrate import odeint
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
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

rc('font',  size=22)
rc('text',  color=chameleon2)
rc('axes',  labelcolor=chameleon2)
rc('axes',  edgecolor=chameleon2)
rc('axes',  facecolor=chameleon6)
rc('xtick', color=chameleon2)
rc('ytick', color=chameleon2)

def lorenz_system(x, t):
    sigma = 10
    R     = 50
    b     = 8.0/3
    return [
        -sigma * (x[0] - x[1]),
        R * x[0] - x[1] - x[0] * x[2],
        -b * x[2] + x[0] * x[1]
        ]

x0 = np.array([10, 10, 10])
t  = np.linspace(0, 25, 5000)

x = odeint(lorenz_system, x0, t)


fig = figure(num=1, figsize=(9,7))
ax = fig.gca(projection='3d')
for a in (ax.w_xaxis, ax.w_yaxis, ax.w_zaxis):
    a.set_pane_color((*chameleon1,0.5))

ax.plot(x[:,0], x[:,1], x[:,2], color=chameleon3)
title('Lorenz attractor trajectory\n')
locator_params(nbins=5)

if quiet: savefig(outfile, facecolor=chameleon6)
else:     show()

