#include <initializer_list>
#include <iostream>

class Base {
  int sidenum;
  std::string name;
  double *params;

public:
  Base(std::initializer_list<double> arglist) {
    set_sidenum(arglist.size() / 2);
    int i{};
    params = new double[sidenum * 2];
    for (double const &val : arglist) {
      if (i == sidenum * 2) {
        std::cout << "Even number of arguments needed. Last argument ignored\n";
        break;
      } else {
        params[i++] = val;
      }
    }
    set_name("Фигура");
  }
  Base() {
    set_sidenum(0);
    set_name("Фигура");
    params = nullptr;
  }
  int get_sidenum() { return sidenum; }
  std::string get_name() { return name; }
  void set_sidenum(int sidenum) { this->sidenum = sidenum; }
  void set_name(std::string name) { this->name = name; }
  double *get_params() { return params; }
  double get_sum_angles() {
    double sum_angles = 0;
    for (int i = sidenum; i < sidenum * 2; i++) {
      sum_angles += params[i];
    }
    return sum_angles;
  }
  double get_sum_angles_req() { return 180 * (sidenum - 2); }
  bool is_sum_angles_ok() {
    if (get_sidenum() < 3) {
      return true;
    }
    return get_sum_angles() == get_sum_angles_req();
  }
  virtual bool is_compliant() { return get_sidenum() == 0; }
  virtual void print_info_pm() {
    std::cout << name << ": "
              << "\n";
    std::cout << (is_compliant() ? "П" : "Неп") << "равильная\n";
    std::cout << "Количество сторон: " << sidenum << "\n\n";
  }
  void print_info() {
    std::cout << name << ": "
              << "\n";
    char symb = 'a';
    std::cout << "Стороны: ";
    for (int i{}, j{}; i < sidenum * 2; ++i, ++j) {
      if (i == sidenum) {
        symb = 'A';
        std::cout << "\nУглы: ";
        j = 0;
      }
      std::cout << char(symb + j) << "=" << params[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }
  Base(const Base &bs_first)
      : sidenum(bs_first.sidenum),
        name(bs_first.name) { // deep copy constructor
    if (bs_first.params) {
      params = new double[sidenum * 2];
      for (int i = 0; i < sidenum * 2; i++)
        params[i] = bs_first.params[i];
    } else
      params = nullptr;
  }
  Base & operator=(const Base &bs_first) { // deep copy assignment overloading
    // self-assignment is a special case: don't need to do anything
    if (this == &bs_first) {
      return *this;
    } else {
      sidenum = bs_first.sidenum;
      name = bs_first.name;
      if (bs_first.params) {
        params = new double[sidenum * 2];
        for (int i = 0; i < sidenum * 2; ++i) { // copy bs_first's values
          params[i] = bs_first.params[i];       // into this array
        }
      } else
        params = nullptr;
      return *this;
    }
  }
  ~Base() { delete[] params; }
};

class Triangle : public Base {
public:
  Triangle(double a, double b, double c, double A, double B, double C)
      : Base({a, b, c, A, B, C}) {
    set_name("Треугольник");
  }
  bool is_compliant() override { return is_sum_angles_ok(); }
  void print_info_pm() override {
    std::cout << get_name() << ": "
              << "\n";
    // std::cout << get_sum_angles() << ": "<< "\n";
    std::cout << (is_compliant() ? "П" : "Неп") << "равильная\n";
    std::cout << "Количество сторон: " << get_sidenum() << "\n";
    char symb = 'a';
    std::cout << "Стороны: ";
    for (int i{}, j{}; i < get_sidenum() * 2; ++i, ++j) {
      if (i == get_sidenum()) {
        symb = 'A';
        std::cout << "\nУглы: ";
        j = 0;
      }
      std::cout << char(symb + j) << "=" << get_params()[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }
};
class Right_Triangle : public Triangle {
public:
  Right_Triangle(double a, double b, double c, double A, double B)
      : Triangle(a, b, c, A, B, 90) {
    set_name("Прямоугольный треугольник");
  }
  bool is_compliant() override {
    return Triangle::is_compliant() && get_params()[5] == 90;
  }
};

class Isosceles : public Triangle {
public:
  Isosceles(double a, double b, double A, double B)
      : Triangle(a, b, a, A, B, A) {
    set_name("Равнобедренный треугольник");
  }
  bool is_compliant() override {
    return Triangle::is_compliant() && get_params()[0] == get_params()[2] &&
           get_params()[3] == get_params()[5];
  }
};

class Equilateral : public Isosceles {
public:
  Equilateral(double a) : Isosceles(a, a, 60, 60) {
    set_name("Равносторонний треугольник");
  }
  bool is_compliant() override {
    return Isosceles::is_compliant() && get_params()[0] == get_params()[1] &&
           get_params()[3] == 60;
  }
};
class Quadrangle : public Base {
public:
  Quadrangle(double a, double b, double c, double d, double A, double B,
             double C, double D)
      : Base({a, b, c, d, A, B, C, D}) {
    set_name("Четырёхугольник");
  }
  bool is_compliant() override { return is_sum_angles_ok(); }
  void print_info_pm() override {
    std::cout << get_name() << ": "
              << "\n";
    std::cout << (is_compliant() ? "П" : "Неп") << "равильная\n";
    std::cout << "Количество сторон: " << get_sidenum() << "\n";
    char symb = 'a';
    std::cout << "Стороны: ";
    for (int i{}, j{}; i < get_sidenum() * 2; ++i, ++j) {
      if (i == get_sidenum()) {
        symb = 'A';
        std::cout << "\nУглы: ";
        j = 0;
      }
      std::cout << char(symb + j) << "=" << get_params()[i] << " ";
    }
    std::cout << std::endl << std::endl;
  }
};
class Parallelogram : public Quadrangle {
public:
  Parallelogram(double a, double b, double A, double B)
      : Quadrangle(a, b, a, b, A, B, A, B) {
    set_name("Параллелограмм");
  }
  bool is_compliant() override {
    return Quadrangle::is_compliant() && get_params()[0] == get_params()[2] &&
           get_params()[1] == get_params()[3] &&
           get_params()[4] == get_params()[6] &&
           get_params()[5] == get_params()[7];
  }
};
class Rectangle : public Parallelogram {
public:
  Rectangle(double a, double b) : Parallelogram(a, b, 90, 90) {
    set_name("Прямоугольник");
  }
  bool is_compliant() override {
    return Parallelogram::is_compliant() && get_params()[4] == 90;
  }
};
class Square : public Rectangle {
public:
  Square(double a) : Rectangle(a, a) { set_name("Квадрат"); }
  bool is_compliant() override {
    return Rectangle::is_compliant() && get_params()[0] == get_params()[1];
  }
};
class Rhombus : public Parallelogram {
public:
  Rhombus(double a, double A, double B) : Parallelogram(a, a, A, B) {
    set_name("Ромб");
  }
  bool is_compliant() override {
    return Parallelogram::is_compliant() && get_params()[0] == get_params()[1];
  }
};

int main() {
  // Triangle ABC;
  Base bs;
  bs.print_info_pm();
  Triangle ABC(10, 20, 30, 50, 60, 70);
  ABC.print_info_pm();
  Right_Triangle rABC1(10, 20, 30, 50, 60);
  rABC1.print_info_pm();
  Right_Triangle rABC2(10, 20, 30, 50, 40);
  rABC2.print_info_pm();
  Isosceles ABA(10, 20, 50, 60);
  ABA.print_info_pm();
  Equilateral AAA(30);
  AAA.print_info_pm();
  Quadrangle ABCD(10, 20, 30, 40, 50, 60, 70, 80);
  ABCD.print_info_pm();
  Rectangle ABABr(10, 20);
  ABABr.print_info_pm();
  Square AAAA(20);
  AAAA.print_info_pm();
  Parallelogram ABAB(20, 30, 30, 40);
  ABAB.print_info_pm();
  Rhombus rhAAAA(30, 30, 40);
  rhAAAA.print_info_pm();

  // std::streamsize prec = std::cout.precision();
}
