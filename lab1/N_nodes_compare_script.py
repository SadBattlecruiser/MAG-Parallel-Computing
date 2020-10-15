import numpy as np
import pandas as pd
import subprocess


single_path = "single\\out\\main.exe"
openmp_path = "openmp\\out\\main.exe"

# Сравниваем при различных разбиениях при постоянном количестве шагов интегрирования
t_end = 10
h_t = 0.2
N_x_list = np.arange(8, 48, 8)
N_y_list = np.arange(6, 36, 6)
#N_x_list = np.arange(8, 24, 8)
#N_y_list = np.arange(6, 18, 6)
N_list = np.array([N_x_list, N_y_list]).T
print(N_list)

N_nodes_data = pd.DataFrame(columns=['N_nodes','total', 'avg', 'openmp_total', 'openmp_avg'])
for i, [N_x, N_y] in enumerate(N_list):
    print(i, N_x, N_y)
    #print(single_path, str(t_end), str(h_t), str(N_x), str(N_y), '-d')
    # Однопоточное решение
    single_curr = subprocess.run([single_path, str(t_end), str(h_t), str(N_x), str(N_y), '-d'], stdout=subprocess.PIPE).stdout
    n_nodes, single_total, single_avg = [float(s) for s in single_curr.split()]
    print('single_total', single_total)
    print('single_avg', single_avg)
    # OpenMP решение
    openmp_curr = subprocess.run([openmp_path, str(t_end), str(h_t), str(N_x), str(N_y), '-d'], stdout=subprocess.PIPE).stdout
    n_nodes, openmp_total, openmp_avg = [float(s) for s in openmp_curr.split()]
    print('openmp_total', openmp_total)
    print('openmp_avg', openmp_avg)
    print('\n')
    N_nodes_data.loc[i] = [n_nodes, single_total, single_avg, openmp_total, openmp_avg]
print(N_nodes_data)
N_nodes_data.to_csv("N_nodes_compare.csv")
