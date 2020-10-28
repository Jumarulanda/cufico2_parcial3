import numpy as np
import matplotlib.pyplot as plt

read_data = np.genfromtxt("test_dat.csv", delimiter=",", skip_header=1)

print(read_data)
