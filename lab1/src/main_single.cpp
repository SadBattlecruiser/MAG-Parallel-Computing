#include <iostream>
#include <fstream>
#include <vector>
#include "point.hpp"
//#include "matrix.hpp"
#include "matrix.cpp"
#include "frame.hpp"
#include "mesh.hpp"

using namespace std;

double T_z = 100. + 273.15; // Температура жидкости внутри трубы

int main() {
  Point_T tp(1, 2, 30);
  //tp.print();
  double side_len[] = {6., 8., 2., 4.};
  Frame tf(side_len);
  //tf.print();
  Mesh ms(tf, 8, 6);
  ms.print_cheme();
  pair<Matrix<double>, vector<double> >& sle = ms.form_sle(T_z);
  cout << "test5\n" << endl;
  sle.first.print();
  cout << "test6\n" << endl;
  ofstream fout;
  fout.open("matr_out.csv");
  sle.first.to_file(fout);
  fout.close();
  cout << "test7\n" << endl;

  Matrix<double> matr2(40, 40);
  ifstream fin;
  fin.open("matr_out2.csv");
  matr2.from_file(fin);
  matr2.print();
  fin.close();
  cout << "test8\n" << endl;
  return 0;
};
