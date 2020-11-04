import numpy as np
import argparse as arp
import matplotlib.pyplot as plt

# def prog arguments

parser = arp.ArgumentParser()
parser.add_argument("dat_dir", help="String with the path of the plotting data")
args = parser.parse_args()

# plot font parameters
plt.rcParams["font.family"] = "serif"
plt.rcParams['mathtext.fontset'] = 'dejavuserif'
plt.rcParams['mathtext.rm'] = 'dejavuserif'
plt.rcParams['mathtext.it'] = 'dejavuserif'
plt.rcParams['mathtext.bf'] = 'dejavuserif'

read_data = np.genfromtxt(args.dat_dir, delimiter=",", skip_header=1)

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
