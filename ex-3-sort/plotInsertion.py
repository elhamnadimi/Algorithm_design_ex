import numpy as np
import matplotlib.pyplot as plt

plt.style.use('ggplot')

timesWorst = np.array([0.000008, 0.000018, 0.000065, 0.000244, 0.000959, 0.003895, 0.009370, 0.025223, 0.098736, 0.39722])
timesBest = np.array([0.000002, 0.000001, 0.000002, 0.000002, 0.000004, 0.000007, 0.000014, 0.000026, 0.000052, 0.000095 ])
numel = np.array([20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240])

# plt.plot(numel, timesBest, label='Best')
# plt.title("Best Case (Ordered)")
plt.plot(numel, timesWorst, label='Worst')
plt.title("Worst Case (Reverse)")
plt.xlabel('NumElem')
plt.ylabel('Times')
plt.legend()
plt.show()