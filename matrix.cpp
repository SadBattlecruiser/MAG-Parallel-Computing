#include "matrix.hpp"

template <typename T>
Matrix<T>::Matrix(const unsigned rows, const unsigned cols) {
  rows_ = rows;
  cols_ = cols;
  arr_ = new T*[rows_];
  for (unsigned i = 0; i < rows_; i++) {
    arr_[i] = new T[cols_];
  };
};

template <typename T>
unsigned Matrix<T>::get_rows() const {
  return rows_;
}

template <typename T>
unsigned Matrix<T>::get_cols() const {
  return cols_;
}

template <typename T>
void Matrix<T>::fill(const T& value) {
  for (unsigned i = 0; i < rows_; i++) {
    for (unsigned j = 0; j < cols_; j++) {
      arr_[i][j] = value;
    };
  };
};

template <typename T>
void Matrix<T>::swap_rows(const unsigned first, const unsigned second) {
  T* temp = arr_[first];
  arr_[first] = arr_[second];
  arr_[second] = temp;
};

template <typename T>
T*& Matrix<T>::operator[](const unsigned index) {
  return arr_[index];
};

template <typename T>
Matrix<T>::~Matrix() {
  for (unsigned i = 0; i < rows_; i++) {
    delete[] arr_[i];
  };
  delete[] arr_;
}
