// 02_class_complex.cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    double argument() const {
        return atan2(imag, real);
    }

    Complex root(int n, int k) const {
        double r = pow(modulus(), 1.0 / n);
        double theta = (argument() + 2 * M_PI * k) / n;
        return Complex(r * cos(theta), r * sin(theta));
    }

    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << fixed << setprecision(2)
            << c.real << " + i*" << c.imag;
        return out;
    }

    friend istream& operator>>(istream& in, Complex& c) {
        cout << "Введіть дійсну частину: ";
        in >> c.real;
        cout << "Введіть уявну частину: ";
        in >> c.imag;
        return in;
    }
};
