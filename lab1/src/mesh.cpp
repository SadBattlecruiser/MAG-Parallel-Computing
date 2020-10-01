#include "mesh.hpp"
#include "point.hpp"
#include "frame.hpp"
//#include "matrix.hpp"
#include "matrix.cpp"
#include <vector>

using namespace std;

Mesh::Mesh(const Frame& frame, const unsigned N_x, const unsigned N_y, const double T0, const bool Symmetry) {
  if (Symmetry) {
    std::vector<double> side_len = frame.get_side_len();
    sym_ = true;

    cout << "side_len: " << side_len[0] << ' ' << side_len[1] << ' '<< side_len[2] << ' '<< side_len[3] << ' '<< endl;

    N_xo_ = N_x;
    x_step_ = side_len[1] / (2*N_xo_);
    N_yo_ = N_y;
    y_step_ = side_len[0] / (2*N_yo_);
    N_xi_ = static_cast<unsigned>((side_len[1] - side_len[3]) / (2*x_step_));
    N_yi_ = static_cast<unsigned>((side_len[0] - side_len[2]) / (2*y_step_));

    mesh_ = new Point_T*[N_yo_];
    unsigned curr_node_num = 0;
    // Сначала длинные массивы - не упирающиеся в вырез
    for (unsigned i = 0; i < N_yi_; ++i) {
      mesh_[i] = new Point_T[N_xo_];
      for (unsigned j = 0; j < N_xo_; ++j) {
        mesh_[i][j] = Point_T(curr_node_num, x_step_ * j, y_step_ * i, T0);
        curr_node_num++;
      }
    }
    // Дальше короткие - которые упираются в вырез
    for (unsigned i = N_yi_; i < N_yo_; ++i) {
      mesh_[i] = new Point_T[N_xi_];
      for (unsigned j = 0; j < N_xi_; ++j) {
        mesh_[i][j] = Point_T(curr_node_num, x_step_ * j, y_step_ * i, T0);
        curr_node_num++;
      }
    }
    N_nodes_ = curr_node_num;
    //cout << "Mesh initializing" << endl;
  }
  else
    throw "symmetry=false in Mesh";
};

pair<Matrix<double>, vector<double> >& Mesh::form_sle(const double T_z) const {
  Matrix<double> ret_matr(N_nodes_, N_nodes_);
  ret_matr.fill(0);
  vector<double> ret_vect(N_nodes_);
  // Сначала заполняем матрицу для всех узлов, кроме границ. Вектор не трогаем, там уже 0
  // Сначала длинные массивы - не упирающиеся в вырез
  for (unsigned i = 1; i < N_yi_; ++i) {
    for (unsigned j = 1; j < N_xo_ - 1; ++j) {
      //cout << "i: " << i << " j: " << j << endl;
      ret_matr[mesh_[i][j].num][mesh_[i-1][j].num] = 1 / (x_step_*x_step_);
      ret_matr[mesh_[i][j].num][mesh_[i+1][j].num] = 1 / (x_step_*x_step_);
      ret_matr[mesh_[i][j].num][mesh_[i][j].num] = -2 * (1/(x_step_*x_step_) + 1/(y_step_*y_step_));
      ret_matr[mesh_[i][j].num][mesh_[i][j-1].num] = 1 / (y_step_*y_step_);
      ret_matr[mesh_[i][j].num][mesh_[i][j+1].num] = 1 / (y_step_*y_step_);
    }
  }
  // Дальше короткие - которые упираются в вырез
  for (unsigned i = N_yi_; i < N_yo_ - 1; ++i) {
    for (unsigned j = 1; j < N_xi_ - 1; ++j) {
      ret_matr[mesh_[i][j].num][mesh_[i-1][j].num] = 1 / (x_step_*x_step_);
      ret_matr[mesh_[i][j].num][mesh_[i+1][j].num] = 1 / (x_step_*x_step_);
      ret_matr[mesh_[i][j].num][mesh_[i][j].num] = -2 * (1/(x_step_*x_step_) + 1/(y_step_*y_step_));
      ret_matr[mesh_[i][j].num][mesh_[i][j-1].num] = 1 / (y_step_*y_step_);
      ret_matr[mesh_[i][j].num][mesh_[i][j+1].num] = 1 / (y_step_*y_step_);
    }
  }
  // Теперь ГУ
  // На внутренней границе - температура
  for (unsigned i = N_xi_; i < N_xo_; ++i) {
    ret_matr[mesh_[N_yi_ - 1][i].num][mesh_[N_yi_ - 1][i].num] = 1;
    ret_vect[mesh_[N_yi_ - 1][i].num] = T_z;
  }
  for (unsigned i = N_yi_; i < N_yo_; ++i) {
    ret_matr[mesh_[i][N_xi_ - 1].num][mesh_[i][N_xi_ - 1].num] = 1;
    ret_vect[mesh_[i][N_xi_ - 1].num] = T_z;
  }
  // Ножняя грань dT/dy = -T т.к. нормаль против y
  for (unsigned i = 0; i < N_xo_; ++i) {
    ret_matr[mesh_[0][i].num][mesh_[0][i].num] = y_step_ - 1;
    ret_matr[mesh_[1][i].num][mesh_[1][i].num] = 1;
  }
  // Левая грань dT/dx = -T т.к. нормаль против x
  for (unsigned i = 0; i < N_yo_; ++i) {
    ret_matr[mesh_[i][0].num][mesh_[i][0].num] = x_step_ - 1;
    ret_matr[mesh_[i][1].num][mesh_[i][1].num] = 1;
  }
  // Правая грань dT/dx = 0 т.к. симметрия
  for (unsigned i = 0; i < N_yi_; ++i) {
    ret_matr[mesh_[i][N_xo_ - 1].num][mesh_[i][N_xo_ - 1].num] = 1;
    ret_matr[mesh_[i][N_xo_ - 2].num][mesh_[i][N_xo_ - 2].num] = -1;
  }
  // Верхняя грань dT/dy = 0 т.к. симметрия
  for (unsigned i = 0; i < N_xi_; ++i) {
    ret_matr[mesh_[N_yo_ - 1][i].num][mesh_[N_yo_ - 1][i].num] = 1;
    ret_matr[mesh_[N_yo_ - 2][i].num][mesh_[N_yo_ - 2][i].num] = -1;
  }
  return *(new pair<Matrix<double>, vector<double> >(ret_matr, ret_vect));
}

void Mesh::print_cheme() const {

  // Размеры
  cout << "x_step: " << x_step_ << endl;
  //cout << "side_len[1] / N_xo_: " << side_len[1] / N_xo_ << endl;
  cout << "y_step: " << y_step_ << endl;
  //cout << "side_len[1] / N_xo_: " << side_len[0] / N_yo_ << endl;
  cout << "N_xo: " << N_xo_ << endl;
  cout << "N_yo: " << N_yo_ << endl;
  cout << "N_xi: " << N_xi_ << endl;
  //cout << "(side_len[3] / x_step_): " << (side_len[3] / x_step_) << endl;
  cout << "N_yi: " << N_yi_ << endl;
  //cout << "(side_len[2] / y_step_): " << (side_len[2] / y_step_) << endl;

  // Сначала длинные массивы - не упирающиеся в вырез
  for (unsigned i = 0; i < N_yi_; ++i) {
    for (unsigned j = 0; j < N_xo_; ++j) {
      //cout << '+';
      cout << mesh_[i][j].num << ' ';
    }
    cout << endl;
  }
  // Дальше короткие - которые упираются в вырез
  for (unsigned i = N_yi_; i < N_yo_; ++i) {
    for (unsigned j = 0; j < N_xi_; ++j) {
      //cout << '+';
      cout << mesh_[i][j].num << ' ';
    }
    cout << endl;
  }
};

Mesh::~Mesh() {
  for (unsigned i = 0; i < N_yo_; i++) {
    delete[] mesh_[i];
  }
  delete[] mesh_;
}
