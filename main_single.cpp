#include <iostream>
#include <vector>

using namespace std;


class Point {
public:
  Point(double x0=0, double y0=0);
  void print() const;
  double x;
  double y;
};

// Класс рамки - просто форма разбиваемой области
// Прямоугольник с прямоугольным вырезом внутри
class Frame {
public:
  // Принимает длины сторон в порядке верт нар, гориз нар, верт внутр, гориз внутр,
  // Предполагается, что внутренний прямоугольник симметрично расположен
  Frame(const double* side_len);
  // Получить координаты углоов
  Point get_ao() const;
  Point get_bo() const;
  Point get_co() const;
  Point get_do() const;
  Point get_ai() const;
  Point get_bi() const;
  Point get_ci() const;
  Point get_di() const;
  void print() const;
private:
  // Точки углов с левого нижнего против часовой
  Point a_o, b_o, c_o, d_o; // Без _ ругается на do
  Point a_i, b_i, c_i, d_i;
};


int main() {
  cout << "Hello, World!" << endl;
  Point tp(1);
  //tp.print();
  double side_len[] = {6., 8., 2., 4.};
  Frame tf(side_len);
  tf.print();

  return 0;
};



Point::Point(double x0, double y0) {
  x = x0;
  y = y0;
};

void Point::print() const {
  cout << "x: " << x << " y: " << y;
}


Frame::Frame(const double* side_len) {
  a_o = Point(0, 0);
  b_o = Point(0, side_len[0]);
  c_o = Point(side_len[1], side_len[0]);
  d_o = Point(side_len[1], 0);
  double a_ix = (side_len[1] - side_len[3]) / 2;
  double a_iy = (side_len[0] - side_len[2]) / 2;
  a_i = Point(a_ix, a_iy);
  b_i = Point(a_ix, a_iy + side_len[2]);
  c_i = Point(a_ix + side_len[3], a_iy + side_len[2]);
  d_i = Point(a_ix + side_len[3], a_iy);
};

Point Frame::get_ao() const {
  return a_o;
}

Point Frame::get_bo() const {
  return b_o;
}

Point Frame::get_co() const {
  return c_o;
}

Point Frame::get_do() const {
  return d_o;
}

Point Frame::get_ai() const {
  return a_i;
}

Point Frame::get_bi() const {
  return b_i;
}

Point Frame::get_ci() const {
  return c_i;
}

Point Frame::get_di() const {
  return d_i;
}

void Frame::print() const {
  cout << "ao: " << endl;
  a_o.print();
  cout << endl;

  cout << "bo: " << endl;
  b_o.print();
  cout << endl;

  cout << "co: " << endl;
  c_o.print();
  cout << endl;

  cout << "do: " << endl;
  d_o.print();
  cout << endl;

  cout << "ai: " << endl;
  a_i.print();
  cout << endl;

  cout << "bi: " << endl;
  b_i.print();
  cout << endl;

  cout << "ci: " << endl;
  c_i.print();
  cout << endl;

  cout << "di: " << endl;
  d_i.print();
  cout << endl;
}
