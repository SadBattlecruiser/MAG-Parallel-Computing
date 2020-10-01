#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename T>
class Matrix {
public:
  Matrix(const unsigned rows, const unsigned cols);
  unsigned get_rows() const;
  unsigned get_cols() const;
  void fill(const T& value);
  void swap_rows(const unsigned first, const unsigned second);
  void print() const;
  void to_file(ofstream& file) const;
  void from_file(ifstream& file);
  //T*& operator[](const unsigned index);
  vector<T>& operator[](const unsigned index);
  /*template <typename T1>
    friend ostream& operator<< (ostream& os, const Matrix<T1>& mtr);*/
  //~Matrix();
private:
  unsigned rows_;
  unsigned cols_;
  //T** arr_;
  vector<vector<T> > arr_;
};


#endif
