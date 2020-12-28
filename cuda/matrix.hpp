#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <fstream>
#include <vector>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace std;

class Matrix {
public:
  Matrix(const size_t rows, const size_t cols);
  Matrix(const Matrix& rmatr);
  size_t get_rows() const;
  size_t get_cols() const;
  const double* get_arr() const;
  void fill(const double& value);
  void swap_rows(const size_t first, const size_t second);
  void set_diag_to_one(const size_t row_index);
  void set_diag_to_one_r(const size_t row_index); // Думает, что левее диагонали нули и их не делит
  void plus_row(const size_t mod_row_index, const size_t plus_row_index, const double coeff); // К mod_row прибавл. plus_row * coeff
  void print() const;
  void to_file(ofstream& file) const;
  void from_file(ifstream& file);
  double* operator[](const size_t index);
  /*template <typename T1>
    friend ostream& operator<< (ostream& os, const Matrix<T1>& mtr);*/
  ~Matrix();
private:
  size_t rows_;
  size_t cols_;
  //T** arr_;
  double* arr_;
};


vector<double>& gauss(const Matrix& l_matr, const vector<double>& r_vect);
vector<double>& gauss_cuda(const Matrix& l_matr, const vector<double>& r_vect);


#endif
