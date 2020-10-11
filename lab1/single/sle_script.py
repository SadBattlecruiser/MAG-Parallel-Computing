import numpy as np
import pandas as pd

matr = np.genfromtxt('matr_out.csv', delimiter=',')
print(matr)
vect_r = np.genfromtxt('vect_out.csv', delimiter=',')
print(vect_r)

vect_res = np.linalg.solve(matr, vect_r)
print(vect_res)
np.savetxt("vect_res.csv", vect_res, delimiter=",")
