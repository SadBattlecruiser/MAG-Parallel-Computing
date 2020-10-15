import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#N_nodes_data = pd.read_csv("N_nodes_compare_corei7_6500u.csv")
N_nodes_data = pd.read_csv("N_nodes_compare_corei5_3470.csv")
print(N_nodes_data)

# Графики времени
fig, ax = plt.subplots()
ax.plot(N_nodes_data['N_nodes'], N_nodes_data['single_total'], label = 'Single')
ax.plot(N_nodes_data['N_nodes'], N_nodes_data['openmp_total'], label = 'OpenMP 4 threads')
ax.set_xlabel('N nodes')
ax.set_ylabel('Time')
ax.grid(axis = 'both')
ax.legend(loc='upper left')
# Графики кубического корня времени, т.к. Гаусс O(n^1/3)
fig2, ax2 = plt.subplots()
ax2.plot(N_nodes_data['N_nodes'], np.power(N_nodes_data['single_total'], 1/3), label = 'Single')
ax2.plot(N_nodes_data['N_nodes'], np.power(N_nodes_data['openmp_total'], 1/3), label = 'OpenMP 4 threads')
ax2.set_xlabel('N nodes')
ax2.set_ylabel('Time^1/3')
ax2.grid(axis = 'both')
ax2.legend(loc='upper left')
# Графики rate, т.е. во сколько раз ускорились
fig3, ax3 = plt.subplots()
ax3.plot(N_nodes_data['N_nodes'], N_nodes_data['single_total'] / N_nodes_data['openmp_total'], label = 'OpenMP 4 threads')
ax3.set_xlabel('N nodes')
ax3.set_ylabel('Rate')
ax3.grid(axis = 'both')
ax3.legend(loc='upper left')


plt.show()
