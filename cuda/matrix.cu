#include "matrix.hpp"
//#include <iostream>
//#include <fstream>

using namespace std;
 
Matrix::Matrix(const size_t rows, const size_t cols) {
  rows_ = rows;
  cols_ = cols;
  arr_ = new double[rows*cols];
};

Matrix::Matrix(const Matrix& rmatr) {
    rows_ = rmatr.get_rows();
    cols_ = rmatr.get_cols();
    arr_ = new double[rows_ * cols_];
    for (size_t i = 0; i < rows_; i++) { 
        for (size_t j = 0; j < cols_; j++) {
            arr_[i * cols_ + j] = rmatr.get_arr()[i*cols_ + j];
        }        
    }

}

 
size_t Matrix::get_rows() const {
    return rows_;
}

 
size_t Matrix::get_cols() const {
    return cols_;
}

const double* Matrix::get_arr() const{
    return arr_;
}

 
void Matrix::fill(const double& value) {
  //cout << "IN FILL" << value << endl;
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      arr_[i * cols_ + j] = value;
      //cout << arr_[i][j] << ' ';
    };
    //cout << endl;
  };
};

 
void Matrix::swap_rows(const size_t first, const size_t second) {
  /*vector<double> temp = arr_[first];
  arr_[first] = arr_[second];
  arr_[second] = temp;*/
    for (size_t i = 0; i < cols_; i++) {
      double temp = arr_[first*cols_ + i];
      arr_[first*cols_ + i] = arr_[second * cols_ + i];
      arr_[second*cols_ + i] = temp;
  }
};

 
void Matrix::set_diag_to_one(const size_t row_index) {
  if (rows_ != cols_) {
    cout << "rows != cols in set_diag_to_one" << endl;
    throw ("rows != cols in set_diag_to_one\n");
  }
  double temp = arr_[row_index*cols_ + row_index];
  for (size_t i = 0; i < cols_; i++) {
    arr_[row_index*cols_ + i] = arr_[row_index*cols_ + i] / temp;
  }
};

 
void Matrix::set_diag_to_one_r(const size_t row_index) {
  if (rows_ != cols_) {
    cout << "rows != cols in set_diag_to_one_r" << endl;
    throw ("rows != cols in set_diag_to_one_r\n");
  }
  for (size_t i = row_index + 1; i < cols_; i++) {
    arr_[row_index*cols_ + i] = arr_[row_index * cols_ + i] / arr_[row_index * cols_ + row_index];
  }
  arr_[row_index * cols_ + row_index] = 1.;
};


 
void Matrix::plus_row(const size_t mod_row_index, const size_t plus_row_index, const double coeff) {
  for (size_t i = 0; i < cols_; i++) {
    arr_[mod_row_index * cols_ + i] += arr_[plus_row_index * cols_ + i] * coeff;
  }
};


 
void Matrix::print() const {
  cout << "IN PRINT" << endl;
  cout << "rows_: " << rows_ << " cols_: " << cols_ << endl;
  for (size_t i = 0; i < rows_; i++) {
    cout << i << " | ";
    for (size_t j = 0; j < cols_; j++) {
      cout << arr_[i * cols_ + j] << ' ';
    }
    cout << endl;
  }
}

 
void Matrix::to_file(ofstream& file) const {
  //cout << "IN_FILE" << endl;
  for (size_t i = 0; i < rows_; i++) {
    file << arr_[i * cols_ + 0];
    for (size_t j = 1; j < cols_; j++) {
      //cout << i << ' ' << j << endl;
      //cout << arr_[i][j] << ' ';
      file << ',' << arr_[i * cols_ + j];
    }
    //cout << endl;
    file << endl;
  }
};

 
void Matrix::from_file(ifstream& file) {
  //cout << "FROM_FILE" << endl;
  for (size_t i = 0; i < rows_; i++) {
    //file >> arr_[i][0];
    for (size_t j = 0; j < cols_; j++) {
      file >>  arr_[i * cols_ + j];
    }
  }
}

 
double* Matrix::operator[](const size_t index) {
  return arr_ + index*cols_;
};


Matrix::~Matrix() {
  delete[] arr_;
}


__global__ void addKernel(double* c, const double* a, const double* b, size_t size) {
    size_t idx = threadIdx.x + blockIdx.x *blockDim.x;
    if (idx < size) {
        c[idx] = a[idx] + b[idx];
    }
}

__global__ void fillVecKernel(double* vec, size_t size, double val) {
    size_t idx = threadIdx.x + blockIdx.x *blockDim.x;
    if (idx < size) {
        vec[idx] = val;
    }
}


__global__ void calculateMCoeffKernel(double* l_matr, size_t size, size_t i, size_t j, double* mcoeff) {
    *mcoeff = l_matr[i * size + j] / l_matr[j * size + j];
}

__global__ void plusRowKernel(double* l_matr, double* r_vec, size_t size,
                              size_t mr_idx, size_t pr_idx, double* mcoeff) {
    size_t idx = threadIdx.x + blockIdx.x *blockDim.x;
    if (idx < size) {
        //l_matr[mr_idx * size + idx] -= l_matr[pr_idx * size + idx] * l_matr[pr_idx * size + pr_idx];
        l_matr[mr_idx * size + idx] -= l_matr[pr_idx * size + idx] * (*mcoeff);
    }
}

__global__ void diagElemsToVecKernel(double* l_matr, double* diag_vec, size_t size) {
    size_t idx = threadIdx.x + blockIdx.x *blockDim.x;
    if (idx < size) {
        diag_vec[idx] = l_matr[idx*size + idx];
    }
}

__global__ void setDiagToOneKernel(double* l_matr, double* r_vec, double* diag_vec, size_t size,
                                   size_t mr_idx) {
    size_t idx = threadIdx.x + blockIdx.x *blockDim.x;
    if (idx < size) {
        l_matr[mr_idx * size + idx] /= diag_vec[mr_idx];
    }
}

__global__ void rvecDiagDivKernel(double* r_vec, double* diag_vec, double size) {
    size_t idx = threadIdx.x + blockIdx.x *blockDim.x;
    if (idx < size) {
        r_vec[idx] /= diag_vec[idx];
    }
}


vector<double>& gauss_cuda(const Matrix& l_matr, const vector<double>& r_vect) {
    size_t size = r_vect.size();
    if (l_matr.get_cols() != l_matr.get_rows()) {
        cout << "not square matrix in gauss" << endl;
        throw ("not square matrix in gauss");
    }
    if (size != l_matr.get_rows()) {
        cout << "l_matr size != r_vect size in gauss" << endl;
        throw ("l_matr size != r_vect size in gauss");
    }
    // Делаем копию вектора правой части в виде массива
    double* r_vec = new double[size];
    for (size_t i = 0; i < size; i++) {
        r_vec[i] = r_vect[i];
    }


    dim3 N_threads1(8);
    dim3 N_blocks1(size / 8 + 1);
    dim3 N_threads_once(1);
    dim3 N_blocks_once(1);
    // Выделяем память на девайсе
    double* l_matr_dev;
    double* r_vec_dev;
    double* ret_vec_dev;
    size_t l_matr_size = size * size * sizeof(double);
    size_t vec_size = size * sizeof(double);
    cudaMalloc((void**) &l_matr_dev, l_matr_size);
    cudaMalloc((void**) &r_vec_dev, vec_size);
    cudaMalloc((void**) &ret_vec_dev, vec_size);
    // Зануляем правый вектор
    fillVecKernel<<<N_blocks1, N_threads1>>>(ret_vec_dev, size, 0);
    // Копируем туда данные
    cudaMemcpy(l_matr_dev, l_matr.get_arr(), l_matr_size, cudaMemcpyHostToDevice);
    cudaMemcpy(r_vec_dev, r_vec, vec_size, cudaMemcpyHostToDevice);
    // Прямой ход
    // Приводим матрицу к верхнетреугольной
    double* mcoeff;
    cudaMalloc((void**)&mcoeff, sizeof(double));
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < i; j++) {
            calculateMCoeffKernel<<<N_threads_once, N_blocks_once >>>(l_matr_dev, size, i, j, mcoeff);
            plusRowKernel<<<N_blocks1, N_threads1>>>(l_matr_dev, r_vec_dev, size, i, j, mcoeff);
        }
     }
    cudaFree(mcoeff);
    cudaDeviceSynchronize();
    // Выводим единицы на главной диагонали
    // Вытаскиваем диагональные элементы, чтобы модифицировать матрицу
    double* diag_vec_dev;
    cudaMalloc((void**)&diag_vec_dev, vec_size);
    diagElemsToVecKernel <<<N_blocks1, N_threads1 >>> (l_matr_dev, diag_vec_dev, size);
    // Диагональный элементы строк в единицы
    for (size_t i = 0; i < size; i++) {
        setDiagToOneKernel <<<N_blocks1, N_threads1 >>> (l_matr_dev, r_vec_dev, diag_vec_dev, size, i);
    }
    // И правый вектор
    rvecDiagDivKernel<<<N_blocks1, N_threads1 >>>(r_vec_dev, diag_vec_dev, size);
    cudaFree(diag_vec_dev);

    //// Обратный ход
    //for (size_t i = 0; i < size; i++) {
    //    //setDiagToOneKernel << <N_blocks1, N_threads1 >> > (l_matr_dev, r_vec_dev, diag_vec_dev, size, i);
    //    
    //}

    //// Лепим возвращаемый вектор
    //double* ret_vec = new double[size];
    //cudaMemcpy(ret_vec, ret_vec_dev, vec_size, cudaMemcpyDeviceToHost);
    //vector<double> ret_vect;
    //for (size_t i = 0; i < size; i++) {
    //    ret_vect.push_back(ret_vec[i]);
    //}
    //// Возвращаем
    delete[] r_vec;
    //delete[] ret_vec;
    //return ret_vect;

    // Обратный ход
    double* l_matr_host = new double[size*size];
    double* r_vec_host = new double[size];
    cudaMemcpy(l_matr_host, l_matr_dev, l_matr_size, cudaMemcpyDeviceToHost);
    cudaMemcpy(r_vec_host, r_vec_dev, vec_size, cudaMemcpyDeviceToHost);
    vector<double>& ret_vect = *(new vector<double>(size));
    for (size_t i = 0; i < size; i++) {
        double sum = 0;
        for (size_t j = 0; j < i; j++) {
            sum += l_matr_host[(size - i - 1)*size + (size - j - 1)] * ret_vect[size - j - 1];
        }
        ret_vect[size - i - 1] = r_vec_host[size - i - 1] - sum;
    }
    return ret_vect;
}
