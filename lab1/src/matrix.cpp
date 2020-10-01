#include "matrix.hpp"
//#include <iostream>
//#include <fstream>

using namespace std;

/*template <typename T>
Matrix<T>::Matrix(const unsigned rows, const unsigned cols) {
  rows_ = rows;
  cols_ = cols;
  arr_ = new T*[rows_];
  for (unsigned i = 0; i < rows_; i++) {
    arr_[i] = new T[cols_];
  };
};*/

template <typename T>
Matrix<T>::Matrix(const unsigned rows, const unsigned cols) {
  rows_ = rows;
  cols_ = cols;
  arr_ = vector<vector<T> >(rows_);
  for (unsigned i = 0; i < rows_; i++) {
    arr_[i] = vector<T>(cols_);
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
  //cout << "IN FILL" << value << endl;
  for (unsigned i = 0; i < rows_; i++) {
    for (unsigned j = 0; j < cols_; j++) {
      arr_[i][j] = value;
      //cout << arr_[i][j] << ' ';
    };
    //cout << endl;
  };
};

template <typename T>
void Matrix<T>::swap_rows(const unsigned first, const unsigned second) {
  T* temp = arr_[first];
  arr_[first] = arr_[second];
  arr_[second] = temp;
};


template <typename T>
void Matrix<T>::print() const {
  cout << "IN PRINT" << endl;
  cout << "rows_: " << rows_ << " cols_: " << cols_ << endl;
  for (unsigned i = 0; i < rows_; i++) {
    for (unsigned j = 0; j < cols_; j++) {
      cout << arr_[i][j] << ' ';
    }
    cout << endl;
  }
}

template <typename T>
void Matrix<T>::to_file(ofstream& file) const {
  cout << "IN_FILE" << endl;
  //cout << "rows_: " << rows_ << " cols_: " << cols_ << endl;
  for (unsigned i = 0; i < rows_; i++) {
    file << arr_[i][0];
    for (unsigned j = 1; j < cols_; j++) {
      //cout << i << ' ' << j << endl;
      //cout << arr_[i][j] << ' ';
      file << ',' << arr_[i][j];
    }
    //cout << endl;
    file << endl;
  }
};

template <typename T>
void Matrix<T>::from_file(ifstream& file) {
  cout << "FROM_FILE" << endl;
  for (unsigned i = 0; i < rows_; i++) {
    //file >> arr_[i][0];
    for (unsigned j = 0; j < cols_; j++) {
      file >>  arr_[i][j];
    }
  }
}

template <typename T>
vector<T>& Matrix<T>::operator[](const unsigned index) {
  return arr_[index];
};

/*template <typename T>
Matrix<T>::~Matrix() {
  for (unsigned i = 0; i < rows_; i++) {
    delete arr_[i];
  };
  delete[] arr_;
}*/
