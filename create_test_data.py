import numpy as np

n = 10000
m = 5000
a = np.random.rand(n, m) * np.random.randint(1000, size = (n, m))
np.savetxt("test_data.txt", a, fmt = "% 10.5f", header=str(n) +' ' + str(m), comments = '')