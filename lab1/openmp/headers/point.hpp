#ifndef POINT_HPP
#define POINT_HPP

class Point {
public:
  Point(double x0=0, double y0=0);
  void print() const;
  double x;
  double y;
};

// Та же точка, но узел - с температурой и номером
class Point_T : public Point {
public:
  Point_T(unsigned node_num=0, double x0=0, double y0=0, double T0=0);
  double T;
  unsigned num;
};

#endif
