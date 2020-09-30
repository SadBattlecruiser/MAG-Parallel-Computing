#ifndef MATRIX_HPP
#define MATRIX_HPP


template <typename T>
class Matrix {
public:
  Matrix(const unsigned rows, const unsigned cols);
  unsigned get_rows() const;
  unsigned get_cols() const;
  void fill(const T& value);
  void swap_rows(const unsigned first, const unsigned second);
  T*& operator[](const unsigned index);
  ~Matrix();
private:
  unsigned rows_;
  unsigned cols_;
  T** arr_;
};


#endif
