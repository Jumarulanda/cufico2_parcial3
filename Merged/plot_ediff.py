import numpy as np
import argparse as arp
import matplotlib.pyplot as plt

# def prog arguments

parser = arp.ArgumentParser()
parser.add_argument("example2", help="String with the path of the plotting data")
args = parser.parse_args()

# plot font parameters
plt.rcParams["font.family"] = "serif"
plt.rcParams['mathtext.fontset'] = 'dejavuserif'
plt.rcParams['mathtext.rm'] = 'dejavuserif'
plt.rcParams['mathtext.it'] = 'dejavuserif'
plt.rcParams['mathtext.bf'] = 'dejavuserif'

read_data = np.genfromtxt(args.example2, delimiter=",", skip_header=1)

# figure construction

fig = plt.figure(constrained_layout = True)

grid = fig.add_gridspec(nrows = 2, ncols = 2)

f_yt = fig.add_subplot(grid[1,:])
f_ypt = fig.add_subplot(grid[0,1])
f_ypy = fig.add_subplot(grid[0,0])

f_yt.plot(read_data[:,-1],read_data[:,0],linestyle='-',linewidth=1,color='blue')
f_ypt.plot(read_data[:,-1],read_data[:,1],linestyle='-',linewidth=1,color='blue')
f_ypy.plot(read_data[:,0],read_data[:,1],linestyle='-',linewidth=1,color='blue')
# plot styling

f_yt.set_xlabel("x",fontsize=14)
f_yt.set_ylabel("Y(x)",fontsize=14)

f_ypt.set_xlabel("x",fontsize=14)
f_ypt.set_ylabel("Y'(x)",fontsize=14)

f_ypy.set_xlabel("Y(x)",fontsize=14)
f_ypy.set_ylabel("Y'(x)",fontsize=14)



plt.show()


###### Cálculo de convergencia ###

"""
def sol_book_example(x):
    c2 = (8-12*np.sin(np.log(2))-4*np.cos(np.log(2)))/70
    c1 = 11/10-c2 
    y = c1*x + c2/x**2 -3*np.sin(np.log(x))/10-np.cos(np.log(x))/10
    return y """
V1 = 110
R1 = 2
R2 = 4

def esferas(x):
    u = V1*R1*((R2-x)/(R2-R1))/x
    return u
    

true_sol = esferas(read_data[:,-1])
##true_sol[-1]=1e-8
convergence = np.absolute((true_sol-read_data[:,0]))

fig2 = plt.figure(constrained_layout = True)
plt.plot(read_data[:,-1],convergence,linestyle='-',linewidth=1,color='black')
plt.xlabel("x",fontsize=14)
plt.ylabel("Convergence",fontsize = 14)
plt.show()

