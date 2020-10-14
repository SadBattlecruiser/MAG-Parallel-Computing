#ifndef FRAME_HPP
#define FRAME_HPP

#include "point.hpp"
#include <vector>

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
  std::vector<double> get_side_len() const;
  void print() const;
private:
  std::vector<double> side_len_;
  // Точки углов с левого нижнего против часовой
  Point ao_, bo_, co_, do_;
  Point ai_, bi_, ci_, di_;
};

#endif
