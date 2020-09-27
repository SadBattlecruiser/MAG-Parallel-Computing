#include "frame.hpp"
#include "point.hpp"
#include <vector>
#include <iostream>

Frame::Frame(const double* side_len) {
  side_len_ = std::vector<double>(side_len, side_len + 4);
  ao_ = Point(0, 0);
  bo_ = Point(0, side_len_[0]);
  co_ = Point(side_len_[1], side_len_[0]);
  do_ = Point(side_len_[1], 0);
  double a_ix = (side_len_[1] - side_len_[3]) / 2;
  double a_iy = (side_len_[0] - side_len_[2]) / 2;
  ai_ = Point(a_ix, a_iy);
  bi_ = Point(a_ix, a_iy + side_len_[2]);
  ci_ = Point(a_ix + side_len_[3], a_iy + side_len_[2]);
  di_ = Point(a_ix + side_len_[3], a_iy);
};

Point Frame::get_ao() const {
  return ao_;
}

Point Frame::get_bo() const {
  return bo_;
}

Point Frame::get_co() const {
  return co_;
}

Point Frame::get_do() const {
  return do_;
}

Point Frame::get_ai() const {
  return ai_;
}

Point Frame::get_bi() const {
  return bi_;
}

Point Frame::get_ci() const {
  return ci_;
}

Point Frame::get_di() const {
  return di_;
}

std::vector<double> Frame::get_side_len() const {
  return side_len_;
};

void Frame::print() const {
  std::cout << "ao: " << std::endl;
  ao_.print();
  std::cout << std::endl;

  std::cout << "bo: " << std::endl;
  bo_.print();
  std::cout << std::endl;

  std::cout << "co: " << std::endl;
  co_.print();
  std::cout << std::endl;

  std::cout << "do: " << std::endl;
  do_.print();
  std::cout << std::endl;

  std::cout << "ai: " << std::endl;
  ai_.print();
  std::cout << std::endl;

  std::cout << "bi: " << std::endl;
  bi_.print();
  std::cout << std::endl;

  std::cout << "ci: " << std::endl;
  ci_.print();
  std::cout << std::endl;

  std::cout << "di: " << std::endl;
  di_.print();
  std::cout << std::endl;
}
