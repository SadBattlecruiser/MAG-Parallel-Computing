#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>
#include "point.hpp"
//include "matrix.hpp"
#include "matrix.cpp" // Клятi шаблоны, небамбит
#include "frame.hpp"
#include "mesh.hpp"

using namespace std;

double T_z = 100. + 273.15;   // Температура жидкости внутри трубы
double T_beg = 30. + 273.15;  // Начальная температура пластины
double dt = 0.2;
double time_end = 10;
double sigm = 0.1;
unsigned N_x = 16; // Узлов по x
unsigned N_y = 12; // Узлов по y


int main(int argc, char *argv[]) {
  bool to_console = false;
  bool to_file = false;
  bool compare_flag = false;
  // Читаем что передали при вызове
  // Если ничего не передали, настройки по умолчанию
  if (argc == 5) {
    sscanf(argv[1], "%lf", &time_end);
    sscanf(argv[2], "%lf", &dt);
    sscanf(argv[3], "%u", &N_x);
    sscanf(argv[4], "%u", &N_y);
  }
  else if (argc == 6 && !strcmp(argv[5], "-c")) {
    sscanf(argv[1], "%lf", &time_end);
    sscanf(argv[2], "%lf", &dt);
    sscanf(argv[3], "%u", &N_x);
    sscanf(argv[4], "%u", &N_y);
    to_console = true;
  }
  else if (argc == 6 && !strcmp(argv[5], "-f")) {
    sscanf(argv[1], "%lf", &time_end);
    sscanf(argv[2], "%lf", &dt);
    sscanf(argv[3], "%u", &N_x);
    sscanf(argv[4], "%u", &N_y);
    to_file = true;
  }
  // Специально для скрипта питона
  else if (argc == 6 && !strcmp(argv[5], "-d")) {
    sscanf(argv[1], "%lf", &time_end);
    sscanf(argv[2], "%lf", &dt);
    sscanf(argv[3], "%u", &N_x);
    sscanf(argv[4], "%u", &N_y);
    compare_flag = true;
  }

  time_t meshing_time_begin = clock();
  // Длины сторон
  double side_len[] = {6., 8., 2., 4.};
  // Геометрия
  Frame tf(side_len);
  // Сетка
  Mesh ms_nonstat(tf, N_x, N_y, T_beg);
  if (to_console) {
    cout << "--------------------------------------" << endl;
    cout << "Node numbering:" << endl;
    ms_nonstat.print_cheme();
  }
  time_t meshing_time = clock() - meshing_time_begin;

  // Нестационарное решение
  double curr_time = 0;
  ofstream fout_nonstat;
  unsigned n_steps = time_end / dt + 1;
  //
  if (to_console) {
    cout << "--------------------------------------" << endl;
    cout << "Nonstationary solve:" << endl;
    cout << "time: " << curr_time << endl;
    ms_nonstat.print_T();
    cout << "--------------------------------------" << endl;
  }
  else if (to_file) {
    fout_nonstat.open("nonstat.txt");
    fout_nonstat << curr_time << endl;
    ms_nonstat.file_T(fout_nonstat);
    fout_nonstat << endl;
  }
  //
  for (unsigned i = 0; i < n_steps; i++) {
    curr_time += dt;
    pair<Matrix<double>, vector<double> >& sle_nonstat = ms_nonstat.form_sle_nonstat(T_z, sigm, dt);
    vector<double>& gauss_res_nonstat  = gauss(sle_nonstat.first, sle_nonstat.second);
    ms_nonstat.from_vector(gauss_res_nonstat);
    //
    if (to_console) {
      cout << "time: " << curr_time << endl;
      ms_nonstat.print_T();
      cout << "--------------------------------------" << endl;
    }
    else if (to_file) {
      fout_nonstat << curr_time << endl;
      ms_nonstat.file_T(fout_nonstat);
      fout_nonstat << endl;
    }
    //
  }
  fout_nonstat.close();
  time_t nonstationary_time = clock() - meshing_time;

  // Стаиионарное решение
  Mesh ms_stat(tf, N_x, N_y, T_beg);
  time_t stationary_sle_beg = clock();
  pair<Matrix<double>, vector<double> >& sle_stat = ms_stat.form_sle_stat(T_z);
  time_t stationary_sle_time = clock() - stationary_sle_beg;
  time_t stationary_gauss_beg = clock();
  vector<double>& gauss_res_stat = gauss(sle_stat.first, sle_stat.second);
  time_t stationary_gauss_time = clock() - stationary_gauss_beg;
  ms_stat.from_vector(gauss_res_stat);
  if (to_console) {
    cout << "--------------------------------------" << endl;
    cout << "Stationary solve:" << endl;
    ms_stat.print_T();
    cout << "--------------------------------------" << endl;
  }
  else if (to_file) {
    ofstream fout_stat("stat.txt");
    ms_stat.file_T(fout_stat);
    fout_stat.close();
  }
  time_t stationary_time = clock() - nonstationary_time;

  time_t total_time = clock();
  if (compare_flag) {
    cout << ms_nonstat.get_N_nodes() << ' ' << nonstationary_time << ' ' << nonstationary_time * dt / time_end;
  }
  else {
    cout << "meshing_time: " << meshing_time << endl;
    cout << "nonstationary_time: " << nonstationary_time << endl;
    cout << "\tavg_step time: " << nonstationary_time * dt / time_end << endl;
    cout << "stationary_sle_time: " << stationary_sle_time << endl;
    cout << "stationary_gauss_time: " << stationary_gauss_time << endl;
    cout << "stationary_time: " << stationary_time << endl;
    cout << "total_time: " << total_time << endl;
  }
  return 0;
};
