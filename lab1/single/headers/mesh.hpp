#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <fstream>
#include "point.hpp"
#include "frame.hpp"
#include "matrix.hpp"

using namespace std;

// Класс сетки
// Принимает геометрию, возвращает СЛАУ
class Mesh {
public:
  // Подразумевается, что стороны выреза нацело делятся на получающиеся шаги сетки. Иначе бобо
  Mesh(const Frame& frame, const unsigned N_x, const unsigned N_y, const double T0 = 0, const bool Symmetry = true);
  pair<Matrix<double>, vector<double> >& form_sle_stat(const double T_z) const;  // Сама слау для стационарного уравнения
  pair<Matrix<double>, vector<double> >& form_sle_nonstat(const double T_z, const double sigm, const double dt) const;  // Сама слау для нестационарного уравнения
  void from_vector(const vector<double>& vect); // Задать темпеаратуру по вектору правой части
  void from_file(ifstream& file);               // Считать вектор из файла и задать по нему температуры
  void print_cheme() const;                     // Распечатать номера узлов
  void print_T() const;                         // Распечатать температуры
  void file_T(ofstream& fout) const;            // Распечатать температуры
  ~Mesh();
private:
  bool sym_;
  double x_step_;
  double y_step_;
  Point_T** mesh_;
  unsigned N_xo_; // кол-во узлов в бОльшей части рамки - где нет выреза
  unsigned N_xi_; // кол-во узлов в меньшей части рамки
  unsigned N_yo_;
  unsigned N_yi_;
  unsigned N_nodes_; // Количество узлов всего
};


#endif
