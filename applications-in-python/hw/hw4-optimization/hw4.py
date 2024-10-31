'''
Dhruv Chakraborty
UID: 204-962-098
PIC 16
Prof. Ryu

HW #4: Scientific Computing and Optimization
'''

#Problem 1:

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize

#number of timesteps
T = 16

terminal_pos = (10,1)

#Dynamics given by Newton's equation F=ma
def rocketDynamics(a):
    v = (1/float(T))*np.stack((np.cumsum(a[:,0]),np.cumsum(a[:,1]-9.8)),axis=-1)
    x = (1/float(T))*(np.cumsum(v,axis=0))[:,0]
    y = (1/float(T))*(np.cumsum(v,axis=0))[:,1]
    return (x,y,v)

# we add coefficients to ensure we are at least approximately stationary at the given target at the end of route
def objFunc(a):
    a = np.reshape(a,(T,2))
    (x,y,v) = rocketDynamics(a)
    targetInaccuracy = np.sqrt( (x[-1]-terminal_pos[0])**2 + (y[-1]-terminal_pos[1])**2 )
    terminalSpeed = np.sqrt(np.sum(v[-1,:]**2))
    fuelUse = np.sum(np.sqrt(np.sum(a**2,axis=1)))
    return  35*targetInaccuracy + 25*terminalSpeed + fuelUse
 

a = np.zeros((T,2))

#Initialize thrust to something
a[0,0] = 50
a[:T/2,1] = 12
a[T/2:,1] = 0

#Perform optimization
sol = minimize(objFunc,a,method='BFGS',options={'disp': True})
a = np.reshape(sol.x,(T,2))

x,y,v = rocketDynamics(a)

# calculate key values at end
targetInaccuracy = np.sqrt( (x[-1]-terminal_pos[0])**2 + (y[-1]-terminal_pos[1])**2 )
terminalSpeed = np.sqrt(np.sum(v[-1,:]**2))
fuelUse = np.sum(np.sqrt(np.sum(a**2,axis=1)))

print "Achieved objective value: {}".format(objFunc(a))
print "Target inaccuracy: {}; terminal speed: {}; and fuel use: {}.".format(targetInaccuracy,terminalSpeed,fuelUse)


x = np.insert(x,0,0)
y = np.insert(y,0,0)
plt.plot(x,y)


# plot results of optimization
plt.quiver(x[:-1],y[:-1],x[1:]-x[:-1],y[1:]-y[:-1], scale_units='xy', angles='xy', scale=1)
plt.quiver(x[:-1],y[:-1],x[1:]-x[:-1],y[1:]-y[:-1], scale_units='xy', angles='xy', scale=1)

plt.xlabel('Horizontal Position')
plt.ylabel('Vertical Position')
plt.title("Rocket dyamics")

plt.show()


#======================#

#Problem 2:

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize

#number of timesteps
T = 16
terminal_pos = (10,1)
M_thrust = 90

#Dynamics given by Newton's equation F=ma
def rocketDynamics(a):
    v = (1/float(T))*np.stack((np.cumsum(a[:,0]),np.cumsum(a[:,1]-9.8)),axis=-1)
    x = (1/float(T))*(np.cumsum(v,axis=0))[:,0]
    y = (1/float(T))*(np.cumsum(v,axis=0))[:,1]
    return (x,y,v)

# we add coefficients to ensure we are at least approximately stationary at the given target at the end of route
def objFunc(a):
    a = np.reshape(a,(T,2))
    (x,y,v) = rocketDynamics(a)
    targetInaccuracy = np.sqrt( (x[-1]-terminal_pos[0])**2 + (y[-1]-terminal_pos[1])**2 )
    terminalSpeed = np.sqrt(np.sum(v[-1,:]**2))
    
    thrust = a + [0, 9.8] # thrust is acceleration + 9.8 in vertical component
    max_thrust = np.amax(np.sqrt(np.sum(thrust**2, axis = 1))) # get maximum thrust
    deviation = max_thrust - M_thrust
    if (deviation <= 0): # if the maximum thrust is less than M, we just try to minimize targetInaccuracy and terminalSpeed
        return 3*targetInaccuracy + 2*terminalSpeed
    else:
        return  3*targetInaccuracy + 2*terminalSpeed + 1000*deviation # if maximum thrust more than M, correct by assigning high coefficient to it
 

a = np.zeros((T,2))

#Initialize thrust to something
a[0,0] = 50
a[:T/2,1] = 12
a[T/2:,1] = 0

#Perform optimization
sol = minimize(objFunc,a,method='BFGS',options={'disp': True})
a = np.reshape(sol.x,(T,2))


x,y,v = rocketDynamics(a)

# calculate key values at end
targetInaccuracy = np.sqrt( (x[-1]-terminal_pos[0])**2 + (y[-1]-terminal_pos[1])**2 )
terminalSpeed = np.sqrt(np.sum(v[-1,:]**2))
thrust = a + [0, 9.8] # find thrust
maxThrust = np.amax(np.sqrt(np.sum(thrust**2, axis=1))) # gives us maximum thrust

print "Achieved objective value: {}".format(objFunc(a))
print "Target inaccuracy: {}; terminal speed: {}; and max thrust: {}.".format(targetInaccuracy,terminalSpeed,maxThrust)


x = np.insert(x,0,0)
y = np.insert(y,0,0)
plt.plot(x,y)


# plot results of optimization
plt.quiver(x[:-1],y[:-1],x[1:]-x[:-1],y[1:]-y[:-1], scale_units='xy', angles='xy', scale=1)
plt.quiver(x[:-1],y[:-1],x[1:]-x[:-1],y[1:]-y[:-1], scale_units='xy', angles='xy', scale=1)

plt.xlabel('Horizontal Position')
plt.ylabel('Vertical Position')
plt.title("Rocket dyamics")

plt.show()



#=========================#
# Problem 3:

import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize

#number of timesteps
T = 16

terminal_pos = (10,1)

#Dynamics given by Newton's equation F=ma
def rocketDynamics(a):
    v = (1/float(T))*np.stack((np.cumsum(a[:,0]),np.cumsum(a[:,1]-9.8)),axis=-1)
    x = (1/float(T))*(np.cumsum(v,axis=0))[:,0]
    y = (1/float(T))*(np.cumsum(v,axis=0))[:,1]
    return (x,y,v)

# we add coefficients to ensure we are at least approximately stationary at the given target at the end of route
def objFunc(a):
    a = np.reshape(a,(T,2))
    (x,y,v) = rocketDynamics(a)
    targetInaccuracy = np.sqrt( (x[-1]-terminal_pos[0])**2 + (y[-1]-terminal_pos[1])**2 )
    terminalSpeed = np.sqrt(np.sum(v[-1,:]**2))
    fuelUse = np.sum(np.sqrt(np.sum(a**2,axis=1)))
    return  35*targetInaccuracy + 25*terminalSpeed + fuelUse

a = np.zeros((T,2))

#Initialize thrust to something
a[0,0] = 50
a[:T/2,1] = 12
a[T/2:,1] = 0

#Perform optimization
sol = minimize(objFunc,a,method='BFGS',options={'disp': True})
a = np.reshape(sol.x,(T,2))

x,y,v = rocketDynamics(a)

# calculate key values at end
targetInaccuracy = np.sqrt( (x[-1]-terminal_pos[0])**2 + (y[-1]-terminal_pos[1])**2 )
terminalSpeed = np.sqrt(np.sum(v[-1,:]**2))
fuelUse = np.sum(np.sqrt(np.sum(a**2,axis=1)))

print "Achieved objective value: {}".format(objFunc(a))
print "Target inaccuracy: {}; terminal speed: {}; and fuel use: {}.".format(targetInaccuracy,terminalSpeed,fuelUse)

thrust = a + [0, 9.8] # get thrust by adding gravity to acceleration
x_thrust = thrust[:,0] # x component of thrust
y_thrust = thrust[:,1] # y component of thrust


x = np.insert(x,0,0)
y = np.insert(y,0,0)
plt.plot(x,y)

# plot results of optimization
plt.quiver(x[:-1],y[:-1],x_thrust,y_thrust, scale_units='xy', angles='xy', scale=100) # plot thrust at given values as vectors, scaling by 100 to normalize

plt.plot(terminal_pos[0],terminal_pos[1],'*',color = '#FF0000',markersize=15) # add star to signify target

plt.xlabel('Horizontal Position')
plt.ylabel('Vertical Position')
plt.title("Rocket dyamics")

plt.show()

