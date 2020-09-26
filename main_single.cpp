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

// Та же точка, но с температурой
class Point_T : public Point {
public:
  Point_T(double x0=0, double y0=0, double T0=0);
  double T;
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
  vector<double> get_side_len() const;
  void print() const;
private:
  vector<double> side_len_;
  // Точки углов с левого нижнего против часовой
  Point ao_, bo_, co_, do_;
  Point ai_, bi_, ci_, di_;
};


// Класс сетки
class Mesh {
public:
  // Подразумевается, что стороны выреза нацело делятся на получающиеся шаги сетки. Иначе бобо
  Mesh(const Frame& frame, const unsigned N_x, const unsigned N_y, const double T0 = 0, const bool Symmetry = true);
private:
  bool sym_;
  double x_step_;
  double y_step_;
  Point_T** mesh_;
  unsigned N_xo_; // кол-во узлов в бОльшей части рамки - где нет выреза
  unsigned N_xi_; // кол-во узлов в меньшей части рамки
  unsigned N_yo_;
  unsigned N_yi_;
};

int main() {
  cout << "Hello, World!" << endl;
  Point_T tp(1, 2, 30);
  //tp.print();
  double side_len[] = {6., 8., 2., 4.};
  Frame tf(side_len);
  tf.print();
  Mesh ms(tf, 8, 6);
  return 0;
};



Point::Point(double x0, double y0) {
  x = x0;
  y = y0;
};

void Point::print() const {
  cout << "x: " << x << " y: " << y;
};


Point_T::Point_T(double x0, double y0, double T0) :
  Point(x0, y0) {
    T = T0;
  };


Frame::Frame(const double* side_len) {
  side_len_ = vector<double>(side_len, side_len + 4);
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

vector<double> Frame::get_side_len() const {
  return side_len_;
};

void Frame::print() const {
  cout << "ao: " << endl;
  ao_.print();
  cout << endl;

  cout << "bo: " << endl;
  bo_.print();
  cout << endl;

  cout << "co: " << endl;
  co_.print();
  cout << endl;

  cout << "do: " << endl;
  do_.print();
  cout << endl;

  cout << "ai: " << endl;
  ai_.print();
  cout << endl;

  cout << "bi: " << endl;
  bi_.print();
  cout << endl;

  cout << "ci: " << endl;
  ci_.print();
  cout << endl;

  cout << "di: " << endl;
  di_.print();
  cout << endl;
}


Mesh::Mesh(const Frame& frame, const unsigned N_x, const unsigned N_y, const double T0, const bool Symmetry) {
  if (Symmetry) {
    vector<double> side_len = frame.get_side_len();
    sym_ = true;

    N_xo_ = N_x;
    x_step_ = side_len[0] / N_xo_;
    N_yo_ = N_y;
    y_step_ = side_len[1] / N_yo_;
    N_xi_ = static_cast<unsigned>(side_len[2] / x_step_);
    N_yi_ = static_cast<unsigned>(side_len[3] / y_step_);

    mesh_ = new Point_T*[N_xo_];
    // Сначала длинные массивы - не упирающиеся в вырез
    for (int i = 0; i < N_yi_; ++i) {
      mesh_[i] = new Point_T[N_xo_];
      for (int j = 0; j < N_xo_; ++j) {
        mesh_[i][j] = Point_T(x_step_ * j, y_step_ * i, T0);
      }
    }
    // Дальше короткие - которые упираются в вырез
    for (int i = N_yi_; i < N_yo_; ++i) {
      mesh_[i] = new Point_T[N_xi_];
      for (int j = 0; j < N_xi_; ++j) {
        mesh_[i][j] = Point_T(x_step_ * j, y_step_ * i, T0);
      }
    }

    //cout << "Mesh initializing" << endl;
  }
  else
    throw "symmetry=false in Mesh";
};
