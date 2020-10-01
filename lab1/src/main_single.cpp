#include <iostream>
#include <fstream>
#include <vector>
#include "point.hpp"
//#include "matrix.hpp"
#include "matrix.cpp"
#include "frame.hpp"
#include "mesh.hpp"

using namespace std;

//double T_z = 100. + 273.15; // Температура жидкости внутри трубы
double T_z = 1000;

int main() {
  Point_T tp(1, 2, 30);
  //tp.print();
  double side_len[] = {6., 8., 2., 4.};
  Frame tf(side_len);
  //tf.print();
  Mesh ms(tf, 16, 12);
  ms.print_cheme();
  cout << "test4\n" << endl;
  
  pair<Matrix<double>, vector<double> >& sle = ms.form_sle(T_z);
  cout << "test5\n" << endl;

  //sle.first.print();
  cout << "test6\n" << endl;

  ofstream fout;
  fout.open("matr_out.csv");
  sle.first.to_file(fout);
  fout.close();
  fout.open("vect_out.csv");
  for (int i = 0; i < sle.second.size(); i++) {
    fout << sle.second[i] << endl;
  }
  fout.close();
  cout << "test7\n" << endl;

  Matrix<double> matr2(40, 40);
  ifstream fin;
  fin.open("vect_res.csv");
  //matr2.from_file(fin);
  //matr2.print();
  ms.from_file(fin);
  ms.print_T();
  fin.close();
  cout << "test8\n" << endl;
  return 0;
};
