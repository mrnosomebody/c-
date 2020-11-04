#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <typeinfo>

using namespace std;

template<typename T>
T power(T num, int deg) {
    T result = 1;
    while (deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
        } else {
            deg--;
            result *= num;
        }
    }

    return result;
}


class Rational {

private:
    int numerator, denominator;

    void reduce() {
        numerator = abs(numerator);
        denominator = abs(denominator);
        int divider = gcd(numerator, denominator);
        numerator /= divider;
        denominator /= divider;
    }

    int gcd(int num, int den) {
        while (num) {
            int a = den % num;
            den = num;
            num = a;
        }
        return den;
    }

    int lcm(int num, int den) { // НОК
        return (num * den) / gcd(num, den);
    }

public:
    //========================================
    // Constructors
    Rational() {
        this->numerator = 0;
        this->denominator = 0;
    }

    Rational(int numerator) {
        this->numerator = numerator;
        this->denominator = 1;
    }

    Rational(int numerator, int denominator) {
        if (this->denominator == 0) {
            throw -1;
        }
        if (this->denominator > 0) {
            this->numerator = numerator;
            this->denominator = denominator;
        } else {
            this->numerator = -numerator;
            this->denominator = -denominator;
        }
        reduce();
    }


    //==================================================
    // Methods

    Rational &operator=(const Rational &other) {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    Rational &operator=(const int value) {
        this->numerator = value;
        this->denominator = 1;
        return *this;
    }

    Rational operator+(const Rational &other) {
        this->numerator = this->numerator * other.denominator + other.numerator * this->denominator;
        this->denominator = this->denominator * other.denominator;
        reduce();
        return Rational(numerator, denominator);
    }

    Rational &operator+=(const Rational &other) {
        this->numerator += other.numerator;
        this->denominator += other.denominator;
        reduce();
        return *this;
    }

    Rational operator-(const Rational &other) {
        this->numerator = this->numerator * other.denominator - other.numerator * this->denominator;
        this->denominator = this->denominator * other.denominator;
        reduce();
        return Rational(numerator, denominator);
    }

    Rational &operator-=(const Rational &other) {
        this->numerator -= other.numerator;
        this->denominator -= other.denominator;
        reduce();
        return *this;
    }

    Rational operator*(const Rational &other) {
        this->numerator = this->numerator * other.numerator;
        this->denominator = this->denominator * other.denominator;
        reduce();
        return Rational(numerator, denominator);
    }

    Rational &operator*=(const Rational &other) {
        *this = *this * other;
        reduce();
        return *this;
    }

    Rational operator/(const Rational &other) {
        this->numerator = this->numerator * other.denominator;
        this->denominator = this->denominator * other.numerator;
        reduce();
        return Rational(numerator, denominator);
    }

    Rational &operator/=(const Rational &other) {
        *this = *this / other;
        reduce();
        return *this;
    }

    Rational operator-() {
        return Rational(-this->numerator, denominator);
    }

    bool operator==(const Rational &other) {    //==
        return this->numerator == other.numerator and this->denominator == other.denominator;
    }

    bool operator!=(const Rational &other) {    //!=
        return !(this->numerator == other.numerator and this->denominator == other.denominator);
    }

    friend ostream &operator<<(ostream &os, const Rational &rational) {
        if (rational.numerator == 0)
            return os << 0;
        if (rational.denominator == 1)
            return os << rational.numerator;
        if (rational.denominator == -1)
            return os << -rational.numerator;
        if (rational.numerator > 0 and rational.denominator > 0)
            return os << '(' << rational.numerator << "/" << rational.denominator << ')';
        if (rational.numerator < 0 and rational.denominator < 0)
            return os << '(' << -rational.numerator << "/" << -rational.denominator << ')';
        if ((rational.numerator > 0 and rational.denominator < 0) or
            (rational.numerator < 0 and rational.denominator > 0))
            return os << '(' << -rational.numerator << "/" << rational.denominator << ')';
    }

    Rational stepen(int deg) {
        this->numerator = power(this->numerator, deg);
        this->denominator = power(this->denominator, deg);
        reduce();
        return *this;
    }
};


class Complex {
private:
    double real, imaginary;

public:

//------------------------------------------------------
//  Конструкторы
    Complex() {
        this->real = 0;
        this->imaginary = 0;
    }

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
        return Complex(-this->real, -this->imaginary);
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
            return atan(this->imaginary / this->real);
        if (this->real < 0 and this->imaginary > 0)
            return pi + atan(this->imaginary / this->real);
        if (this->real < 0 and this->imaginary < 0)
            return -pi + atan(this->imaginary / this->real);
        if (this->real == 0 and this->imaginary > 0)
            return pi / 2;
        else return -pi / 2;
    }

    double abs() {
        return sqrt(this->real * this->real + this->imaginary * this->imaginary);
    }

    friend double power(double num, int deg);

    Complex stepen(int deg) {
        Complex result;
        result.real = power(this->abs(), deg) * cos(this->arg() * deg);
        result.imaginary = power(this->abs(), deg) * sin(this->arg() * deg);
        return result;
    }

    friend ostream &operator<<(ostream &os, const Complex &complex) {
        if (complex.real == 0)
            return os << complex.imaginary << "i";
        if (complex.imaginary == 0)
            return os << complex.real;
        if (complex.imaginary > 0)
            return os << complex.real << " + " << complex.imaginary << "i";
        if (complex.real == 0 and complex.imaginary == 0)
            return os << 0;
        return os << complex.real << " - " << fabs(complex.imaginary) << "i";
    }


};

int main() {
    Rational a(5, 7);
    Rational b(1.54, 3.6);
    cout << b;

}