#######################################
#
#   plotTimeComplexities.py
#
#	Project 1
#	Data Structures & Algorithms
#	Wendy Slattery
#	3/8/20
#
######################################## 

import matplotlib.pyplot as plt
import numpy as np



x, y = np.loadtxt('timePlot.txt', delimiter=',', unpack=True)
plt.plot(x,y, label='Process Speed', marker="d")



plt.xlabel('vector data volume (Million)')
plt.ylabel('time (sec)')
plt.ylim(-50,2200)

plt.title('Insertion Sort\nA Comparison of Time Complexities')
plt.legend()
plt.show()

