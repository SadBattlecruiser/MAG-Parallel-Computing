#include <iostream>
#include <fstream>
#include <vector>
#include "point.hpp"
//#include "matrix.hpp"
#include "matrix.cpp"
#include "frame.hpp"
#include "mesh.hpp"

#include <cmath>

using namespace std;

//double T_z = 100. + 273.15; // Температура жидкости внутри трубы
double T_z = 1000;

int main() {
  Point_T tp(1, 2, 30);
  //tp.print();
  double side_len[] = {6., 8., 2., 4.};
  Frame tf(side_len);
  //tf.print();
  Mesh ms(tf, 8, 6);
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

  //vector<double>& gauss_res = gauss(sle.first, sle.second);
  Matrix<double> test_matr(4, 4);
  vector<double> test_vect(4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      test_matr[i][j] = 16 - i + j;
    }
    test_vect[i] = 8*i;
  }
  test_matr[0][0] = 10;
  test_matr[1][1] = 11;
  test_matr[2][2] = 12;

  vector<double>& gauss_res = gauss(test_matr, test_vect);
  cout << "test7.5\n" << endl;

  /*Matrix<double> matr2(40, 40);
  ifstream fin;
  fin.open("vect_res.csv");
  ms.from_file(fin);
  ms.print_T();
  fin.close();
  cout << "test8\n" << endl;
  return 0;*/
};
