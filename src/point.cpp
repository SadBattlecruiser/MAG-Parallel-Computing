#include "point.hpp"
#include <iostream>

Point::Point(double x0, double y0) {
  x = x0;
  y = y0;
};

void Point::print() const {
  std::cout << "x: " << x << " y: " << y;
};


Point_T::Point_T(double x0, double y0, double T0) :
  Point(x0, y0) {
    T = T0;
};
