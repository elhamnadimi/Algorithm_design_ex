import numpy as np
import matplotlib.pyplot as plt

plt.style.use('ggplot')
plt.rc('font', family='sans-serif')

worstTimes = np.array([0.000005, 0.000013, 0.000044, 0.000127, 0.000418,\
 0.001644, 0.006190, 0.012179, 0.043791, 0.164035])
bestTimes = np.array([0.000005, 0.000005, 0.000007, 0.000014, 0.000027,\
 0.000056, 0.000118, 0.000252, 0.000586, 0.001123])
numElems = np.array([20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240])

plt.plot(numElems, bestTimes, lw=1, ls='-', marker='o', label='best')
plt.title("Quick Sort Best Case")
plt.xlabel("Number")
plt.ylabel("Time[s]")
plt.legend()
plt.show()