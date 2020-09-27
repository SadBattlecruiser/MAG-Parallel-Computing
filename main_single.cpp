#include <iostream>
#include <vector>
//#include <SFML/Window.hpp>
#include "point.hpp"
#include "matrix.cpp"
#include "frame.hpp"
#include "mesh.hpp"

using namespace std;

int main() {
  cout << "Hello, World!" << endl;
  Point_T tp(1, 2, 30);
  //tp.print();
  double side_len[] = {6., 8., 2., 4.};
  Frame tf(side_len);
  tf.print();
  Mesh ms(tf, 8, 6);
  Matrix<double> matr(3, 4);
  matr.fill(14.);
  cout << matr[1][1] << std::endl;
  //sf::Window window(sf::VideoMode(800, 600), "My window");

  return 0;
};
