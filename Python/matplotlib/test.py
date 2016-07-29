#!usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
	
x = [1, 2, 3,  4,  5,  6,  7,  8,  9]
y = [1, 4, 9, 16, 25, 36, 49, 64, 81]

plt.subplot(2,2,1)
plt.plot(x, y)
plt.xlabel("x-lable")
plt.ylabel("y-lable")
plt.title("title")
plt.grid(True)
plt.legend()

plt.show()
