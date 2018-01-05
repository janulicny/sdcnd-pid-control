import numpy as np

data = np.genfromtxt('data.txt', delimiter='\t')[1:,:]


Kp = data[:,0]
Kd = data[:,1]
Ki = data[:,2]
error = data[:,3]
errorn = 1-(error - min(error))/(max(error) - min(error))
errorn = errorn**5

import matplotlib.pyplot as plt

plt.scatter(Kp, Kd, c=error, s=100*errorn, cmap='plasma', alpha=0.5)
plt.colorbar()
plt.xlabel("K_p")
plt.ylabel("K_d")
#plt.plot(Kp, Kd, '.k-')

#from matplotlib.mlab import griddata
#xi = np.linspace(np.min(Kp), np.max(Kp), len(Kp))
#yi = np.linspace(np.min(Kd), np.max(Kd), len(Kd))
##DEM = griddata(Kp, Kd, error, xi, yi)
#
#import scipy as sp
#
#XI, YI = np.meshgrid(xi, yi)
#points = np.vstack((Kp,Kd)).T
#DEM = sp.interpolate.griddata(points, error, (XI,YI), method='linear')
#DEM[np.where(np.isnan(DEM))] = np.nanmax(DEM)
#
#levels = np.arange(np.min(DEM),np.max(DEM),200)
#
#plt.figure()
#plt.contour(DEM, levels,linewidths=0.4,colors='k')
#plt.scatter(Kp, Kd, c=error, s=5, cmap='plasma', alpha = 0.5)
#plt.show()


#from mpl_toolkits.mplot3d import Axes3D
#
#
#fig = plt.figure()
#ax = fig.add_subplot(111, projection='3d')
#ax.scatter(Kp, Kd, error)

