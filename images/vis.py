import numpy as np
import matplotlib.pyplot as plt


p = np.genfromtxt('P.txt')
bl = np.zeros(p.shape)
plt.plot(bl,'r')
plt.plot(p)
#plt.plot(pd,'g')
plt.ylabel('CTE')
plt.xlabel('t [steps]')
plt.title('P controller')
plt.ylim((-7, 7))

plt.figure()
pd = np.genfromtxt('PD.txt')
bl = np.zeros(pd.shape)
plt.plot(bl,'r')
plt.plot(pd)
plt.ylabel('CTE')
plt.xlabel('t [steps]')
plt.title('PD controller')
plt.ylim((-7, 7))

#data = np.genfromtxt('data.txt', delimiter='\t')[1:,:]
#
#
#Kp = data[:,0]
#Kd = data[:,1]
#Ki = data[:,2]
#error = data[:,3]
#errorn = 1-(error - min(error))/(max(error) - min(error))
#errorn = errorn**5
#
#plt.scatter(Kp, Kd, c=error, s=100*errorn, cmap='plasma', alpha=0.5)
#plt.colorbar()
#plt.xlabel("K_p")
#plt.ylabel("K_d")
