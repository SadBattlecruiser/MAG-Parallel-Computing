#include "matrix.hpp"
//#include <iostream>
//#include <fstream>

using namespace std;
/* 
Matrix::Matrix(const unsigned rows, const unsigned cols) {
  rows_ = rows;
  cols_ = cols;
  arr_ = new T*[rows_];
  for (unsigned i = 0; i < rows_; i++) {
    arr_[i] = new T[cols_];
  };
};*/

 
Matrix::Matrix(const unsigned rows, const unsigned cols) {
  rows_ = rows;
  cols_ = cols;
  arr_ = vector<vector<double> >(rows_);
  for (unsigned i = 0; i < rows_; i++) {
    arr_[i] = vector<double>(cols_);
  };
};

 
unsigned Matrix::get_rows() const {
  return rows_;
}

 
unsigned Matrix::get_cols() const {
  return cols_;
}

 
void Matrix::fill(const double& value) {
  //cout << "IN FILL" << value << endl;
  for (unsigned i = 0; i < rows_; i++) {
    for (unsigned j = 0; j < cols_; j++) {
      arr_[i][j] = value;
      //cout << arr_[i][j] << ' ';
    };
    //cout << endl;
  };
};

 
void Matrix::swap_rows(const unsigned first, const unsigned second) {
  vector<double> temp = arr_[first];
  arr_[first] = arr_[second];
  arr_[second] = temp;
};

 
void Matrix::set_diag_to_one(const unsigned row_index) {
  if (rows_ != cols_) {
    cout << "rows != cols in set_diag_to_one" << endl;
    throw ("rows != cols in set_diag_to_one\n");
  }
  double temp = arr_[row_index][row_index];
  for (unsigned i = 0; i < cols_; i++) {
    arr_[row_index][i] = arr_[row_index][i] / temp;
  }
};

 
void Matrix::set_diag_to_one_r(const unsigned row_index) {
  if (rows_ != cols_) {
    cout << "rows != cols in set_diag_to_one_r" << endl;
    throw ("rows != cols in set_diag_to_one_r\n");
  }
  for (unsigned i = row_index + 1; i < cols_; i++) {
    arr_[row_index][i] = arr_[row_index][i] / arr_[row_index][row_index];
  }
  arr_[row_index][row_index] = 1.;
};


 
void Matrix::plus_row(const unsigned mod_row_index, const unsigned plus_row_index, const double coeff) {
  for (unsigned i = 0; i < cols_; i++) {
    arr_[mod_row_index][i] += arr_[plus_row_index][i] * coeff;
  }
};


 
void Matrix::print() const {
  cout << "IN PRINT" << endl;
  cout << "rows_: " << rows_ << " cols_: " << cols_ << endl;
  for (unsigned i = 0; i < rows_; i++) {
    cout << i << " | ";
    for (unsigned j = 0; j < cols_; j++) {
      cout << arr_[i][j] << ' ';
    }
    cout << endl;
  }
}

 
void Matrix::to_file(ofstream& file) const {
  //cout << "IN_FILE" << endl;
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

 
void Matrix::from_file(ifstream& file) {
  //cout << "FROM_FILE" << endl;
  for (unsigned i = 0; i < rows_; i++) {
    //file >> arr_[i][0];
    for (unsigned j = 0; j < cols_; j++) {
      file >>  arr_[i][j];
    }
  }
}

 
vector<double>& Matrix::operator[](const unsigned index) {
  return arr_[index];
};

/* 
Matrix::~Matrix() {
  for (unsigned i = 0; i < rows_; i++) {
    delete arr_[i];
  };
  delete[] arr_;
}*/

 
vector<double>& gauss(const Matrix& l_matr, const vector<double>& r_vect) {
  unsigned size_ = r_vect.size();
  if (l_matr.get_cols() != l_matr.get_rows()) {
    cout << "not square matrix in gauss" << endl;
    throw ("not square matrix in gauss");
  }
  if (size_ != l_matr.get_rows()) {
    cout << "l_matr size != r_vect size in gauss" << endl;
    throw ("l_matr size != r_vect size in gauss");
  }
  Matrix l_matr_ = l_matr;
  vector<double> r_vect_ = r_vect;
  vector<double>& ret_vect = *(new vector<double>(size_));
  // Прямой ход
  for (unsigned i = 0; i < size_; i++) {
    for (unsigned j = 0; j < i; j++) {
      r_vect_[i] -= r_vect_[j] * l_matr_[i][j];
      l_matr_.plus_row(i, j, -l_matr_[i][j]);
    }
    r_vect_[i] /= l_matr_[i][i];
    l_matr_.set_diag_to_one_r(i);
  }
  // Обратный ход
  for (unsigned i = 0; i < size_; i++) {
    double sum = 0;
    //cout << "i: " << i  << endl;
    for (unsigned j = 0; j < i; j++) {
      sum += l_matr_[size_-i-1][size_-j-1] * ret_vect[size_-j-1];
    }
    ret_vect[size_-i-1] = r_vect_[size_-i-1] - sum;
  }
  return ret_vect;
}
