#include <matrix.hpp>
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
void Matrix<T>::set_diag_to_one(const unsigned row_index) {
  if (rows_ != cols_) {
    cout << "rows != cols in set_diag_to_one" << endl;
    throw ("rows != cols in set_diag_to_one\n");
  }
  T temp = arr_[row_index][row_index];
  for (unsigned i = 0; i < cols_; i++) {
    arr_[row_index][i] = arr_[row_index][i] / temp;
  }
};

template <typename T>
void Matrix<T>::set_diag_to_one_r(const unsigned row_index) {
  if (rows_ != cols_) {
    cout << "rows != cols in set_diag_to_one_r" << endl;
    throw ("rows != cols in set_diag_to_one_r\n");
  }
  for (unsigned i = row_index + 1; i < cols_; i++) {
    arr_[row_index][i] = arr_[row_index][i] / arr_[row_index][row_index];
  }
  arr_[row_index][row_index] = 1.;
};


template <typename T>
void Matrix<T>::plus_row(const unsigned mod_row_index, const unsigned plus_row_index, const double coeff) {
  for (unsigned i = 0; i < cols_; i++) {
    arr_[mod_row_index][i] += arr_[plus_row_index][i] * coeff;
  }
};


template <typename T>
void Matrix<T>::print() const {
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

template <typename T>
void Matrix<T>::to_file(ofstream& file) const {
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

template <typename T>
void Matrix<T>::from_file(ifstream& file) {
  //cout << "FROM_FILE" << endl;
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

template <typename T>
vector<T>& gauss(const Matrix<T>& l_matr, const vector<T>& r_vect) {
  unsigned size_ = r_vect.size();
  if (l_matr.get_cols() != l_matr.get_rows()) {
    cout << "not square matrix in gauss" << endl;
    throw ("not square matrix in gauss");
  }
  if (size_ != l_matr.get_rows()) {
    cout << "l_matr size != r_vect size in gauss" << endl;
    throw ("l_matr size != r_vect size in gauss");
  }
  Matrix<T> l_matr_ = l_matr;
  vector<T> r_vect_ = r_vect;
  vector<T>& ret_vect = *(new vector<T>(size_));
  // Прямой ход
  #pragma omp parallel for
  // Не думаю, что есть смысл параллелить внутренний цикл -- все равно ядер не хватит
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
    T sum = 0;
    #pragma omp parallel for
    // Здесь нельзя трогать наружный цикл
    for (unsigned j = 0; j < i; j++) {
      sum += l_matr_[size_-i-1][size_-j-1] * ret_vect[size_-j-1];
    }
    ret_vect[size_-i-1] = r_vect_[size_-i-1] - sum;
  }
  return ret_vect;
}
