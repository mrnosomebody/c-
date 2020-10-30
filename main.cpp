#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double real, imaginary;

public:

//------------------------------------------------------
//  Конструкторы
    Complex() {}

    Complex(double real) {
        this->real = real;
        this->imaginary = 0;
    }

    Complex(double real, double imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }
//------------------------------------------------------------------------------------
// Перегрузки

    bool operator==(const Complex &other) {    //==
        return this->real == other.real and this->imaginary == other.imaginary;
    }

    bool operator!=(const Complex &other) {    //!=
        return !(this->real == other.real and this->imaginary == other.imaginary);
    }

    Complex &operator=(const Complex &other) {   //=
        this->real = other.real;
        this->imaginary = other.imaginary;
        return *this;
    }

    Complex operator+(const Complex &other) {   //+
        return Complex(this->real + other.real, this->imaginary + other.imaginary);
    }

    Complex &operator+=(const Complex &other) {  //+=
        this->real += other.real;
        this->imaginary += other.imaginary;
        return *this;
    }

    Complex operator-(const Complex &other) {   //-
        return Complex(this->real - other.real, this->imaginary - other.imaginary);
    }

    Complex &operator-=(const Complex &other) {  //-=
        this->real -= other.real;
        this->imaginary -= other.imaginary;
        return *this;
    }

    Complex operator*(const Complex &other) {  //*
        return Complex(this->real * other.real - imaginary * other.imaginary,
                       real * other.imaginary + imaginary * other.real);
    }

    Complex &operator*=(const Complex &other) {  //*=
        return *this = *this * other;
    }

    Complex operator/(const Complex &other) {  // /
        Complex result;
        double sqr = other.real * other.real + other.imaginary * other.imaginary;
        result.real = (this->real * other.real + this->imaginary * other.imaginary) / sqr;
        result.imaginary = (this->imaginary * other.real - this->real * other.imaginary) / sqr;
        return result;
    }

    Complex &operator/=(const Complex &other) {  // /=
        return *this = *this * other;
    }

    Complex operator-() {
        return Complex(this->real * (-1), this->imaginary * (-1));
    }
//============================================
// Methods

    double GetReal() {
        return this->real;
    }

    double GetIm() {
        return this->imaginary;
    }

    void SetReal(double real) {
        this->real = real;
    }

    void SetIm(double imaginary) {
        this->imaginary = imaginary;
    }

    double arg() {
        double pi = 3.14;
        double argument = 0;
        if (this->real == 0 and this->imaginary == 0)
            return 0;
        if (this->real > 0)
            return atan(this->imaginary/ this->real);
        if (this->real < 0 and this->imaginary > 0)
            return pi + atan(this->imaginary/ this->real);
        if (this->real < 0 and this->imaginary < 0)
            return -pi + atan(this->imaginary/ this->real);
        if (this->real == 0 and this->imaginary > 0)
            return pi / 2;
        else return -pi/2;
    }

    double abs(){
        return sqrt(this->real * this->real + this->imaginary * this->imaginary);
    }
};

int main() {
    Complex a(1, -sqrt(3));
//    Complex b(5, 4);
//    a = -b;
    cout << a.arg();
    cout<<atan(-sqrt(3)/1);
}