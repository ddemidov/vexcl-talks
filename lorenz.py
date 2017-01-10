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

def lorenz_system(x, t):
    sigma = 10
    R     = 28
    b     = 8.0/3
    return [
        -sigma * (x[0] - x[1]),
        R * x[0] - x[1] - x[0] * x[2],
        -b * x[2] + x[0] * x[1]
        ]

x0 = np.array([10, 10, 10])
t  = np.linspace(0, 50, 5000)

x = odeint(lorenz_system, x0, t)

rc('font', size=22)

fig = figure(num=1, figsize=(9,7))
ax = fig.gca(projection='3d')
ax.plot(x[:,0], x[:,1], x[:,2], label='trajectory', color=chameleon3)
locator_params(nbins=5)

if quiet: savefig(outfile)
else:     show()

