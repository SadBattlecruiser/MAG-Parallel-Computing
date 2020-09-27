#ifndef MESH_HPP
#define MESH_HPP

#include "point.hpp"
#include "frame.hpp"

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


#endif
