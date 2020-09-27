#include "mesh.hpp"
#include "point.hpp"
#include "frame.hpp"
#include <vector>

Mesh::Mesh(const Frame& frame, const unsigned N_x, const unsigned N_y, const double T0, const bool Symmetry) {
  if (Symmetry) {
    std::vector<double> side_len = frame.get_side_len();
    sym_ = true;

    N_xo_ = N_x;
    x_step_ = side_len[0] / N_xo_;
    N_yo_ = N_y;
    y_step_ = side_len[1] / N_yo_;
    N_xi_ = static_cast<unsigned>(side_len[2] / x_step_);
    N_yi_ = static_cast<unsigned>(side_len[3] / y_step_);

    mesh_ = new Point_T*[N_xo_];
    // Сначала длинные массивы - не упирающиеся в вырез
    for (unsigned i = 0; i < N_yi_; ++i) {
      mesh_[i] = new Point_T[N_xo_];
      for (unsigned j = 0; j < N_xo_; ++j) {
        mesh_[i][j] = Point_T(x_step_ * j, y_step_ * i, T0);
      }
    }
    // Дальше короткие - которые упираются в вырез
    for (unsigned i = N_yi_; i < N_yo_; ++i) {
      mesh_[i] = new Point_T[N_xi_];
      for (unsigned j = 0; j < N_xi_; ++j) {
        mesh_[i][j] = Point_T(x_step_ * j, y_step_ * i, T0);
      }
    }

    //cout << "Mesh initializing" << endl;
  }
  else
    throw "symmetry=false in Mesh";
};
