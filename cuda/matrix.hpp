#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Matrix {
public:
  Matrix(const unsigned rows, const unsigned cols);
  unsigned get_rows() const;
  unsigned get_cols() const;
  void fill(const double& value);
  void swap_rows(const unsigned first, const unsigned second);
  void set_diag_to_one(const unsigned row_index);
  void set_diag_to_one_r(const unsigned row_index); // Думает, что левее диагонали нули и их не делит
  void plus_row(const unsigned mod_row_index, const unsigned plus_row_index, const double coeff); // К mod_row прибавл. plus_row * coeff
  void print() const;
  void to_file(ofstream& file) const;
  void from_file(ifstream& file);
  //T*& operator[](const unsigned index);
  vector<double>& operator[](const unsigned index);
  /*template <typename T1>
    friend ostream& operator<< (ostream& os, const Matrix<T1>& mtr);*/
  //~Matrix();
private:
  unsigned rows_;
  unsigned cols_;
  //T** arr_;
  vector<vector<double> > arr_;
};


vector<double>& gauss(const Matrix& l_matr, const vector<double>& r_vect);


#endif
