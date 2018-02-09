#%%
from pylab import *
from mpl_toolkits.mplot3d import Axes3D
import pylorenz as lorenz

#%%
lorenz.context('K40c')

#%%
fig = figure(figsize=(8,6))
ax = fig.gca(projection='3d')

#%%
n = 32    # Number of parameters
m = 1000  # Length of trajectory

# Parameters
R = linspace(0.1, 10, n)
sigma = 10.0
b = 8/3

# Initial solution
S = empty((m, 3, n))
S[0,:,:] = 10.0

# Integration
ode = lorenz.Stepper(sigma, b, R)
for i in range(1,m):
    S[i] = ode.advance(S[i-1], 1, 0.01)

# Draw the results
cmap = get_cmap('viridis')
ax.clear()
for i in range(n):
    ax.plot(S[:,0,i], S[:,1,i], S[:,2,i], color=cmap(i/n), alpha=0.4)