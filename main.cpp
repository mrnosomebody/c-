#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <typeinfo>
#include <numeric>
#include <algorithm>

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
    double numerator, denominator;

    void reduce() {
        if (denominator < 0) {
            numerator = -(numerator);
            denominator = -denominator;
        }
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
        return abs(den);
    }

    void transformation() {
        while (this->numerator != int(numerator) or this->denominator != int(denominator)) {
            numerator *= 10;
            denominator *= 10;
        }
    }

    template<typename T>
    T lcm(T a, T b) { // НОК
        return (a * b) / gcd(a, b);
    }

public:
    //========================================
    // Constructors
    Rational() {
        this->numerator = 0;
        this->denominator = 0;
    }

    Rational(double numerator) {
        this->numerator = numerator;
        this->denominator = 1;
        //transformation();
        reduce();
    }

    Rational(double numerator, double denominator) {
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
        transformation();
        reduce();
    }


    //==================================================
    // Methods

    Rational &operator=(const Rational &other) = default;


    Rational operator+(const Rational &other) {
        Rational newr;
        if (denominator == other.denominator) {
            newr.numerator = numerator + other.numerator;
            newr.denominator = other.denominator;
        } else {
            int LcmNumber = lcm(denominator, other.denominator);
            newr.numerator =
                    (numerator * (LcmNumber / denominator)) + (other.numerator * (LcmNumber / other.denominator));
            newr.denominator = LcmNumber;
        }
        newr.reduce();
        return newr;
    }

    Rational &operator+=(const Rational &other) {
        this->numerator += other.numerator;
        this->denominator += other.denominator;
        reduce();
        return *this;
    }

    Rational operator-(const Rational &other) {
        Rational newr;
        if (denominator == other.denominator) {
            newr.numerator = numerator - other.numerator;
            newr.denominator = other.denominator;
        } else {
            int LcmNumber = lcm(denominator, other.denominator);
            newr.numerator =
                    (numerator * (LcmNumber / denominator)) - (other.numerator * (LcmNumber / other.denominator));
            newr.denominator = LcmNumber;
        }
        newr.reduce();
        return newr;
    }


    Rational &operator-=(const Rational &other) {
        this->numerator -= other.numerator;
        this->denominator -= other.denominator;
        reduce();
        return *this;
    }

    Rational operator*(const Rational &other) {
        Rational newr;
        newr.numerator = this->numerator * other.numerator;
        newr.denominator = this->denominator * other.denominator;
        newr.reduce();
        return newr;
    }

    Rational &operator*=(const Rational &other) {
        *this = *this * other;
        reduce();
        return *this;
    }

    Rational operator/(const Rational &other) {
        Rational newr;
        newr.numerator = this->numerator * other.denominator;
        newr.denominator = this->denominator * other.numerator;
        newr.reduce();
        return newr;
    }

    Rational &operator/=(const Rational &other) {
        *this = *this / other;
        reduce();
        return *this;
    }

    Rational operator-() const {
        return Rational(-this->numerator, denominator);
    }

    bool operator==(const Rational &other) const {    //==
        return this->numerator == other.numerator and this->denominator == other.denominator;
    }

    bool operator!=(const Rational &other) const {    //!=
        return !(this->numerator == other.numerator and this->denominator == other.denominator);
    }

    bool operator>(Rational second) const {
        return this->toDouble() > second.toDouble();
    }

    bool operator<(Rational second) const {
        return this->toDouble() < second.toDouble();
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
        if (rational.numerator > 0 and rational.denominator < 0)
            return os << '(' << -rational.numerator << "/" << -rational.denominator << ')';
        if (rational.numerator < 0 and rational.denominator > 0)
            return os << '(' << rational.numerator << "/" << rational.denominator << ')';
    }

    Rational stepen(int deg) {
        this->numerator = power(this->numerator, deg);
        this->denominator = power(this->denominator, deg);
        reduce();
        return *this;
    }

    double toDouble() const {
        return (double) this->numerator / this->denominator;
    }
};

Rational power(Rational num, int deg) {
    Rational result = 1;
    num = num.toDouble();
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


class Complex {
private:
    Rational real, imaginary;

public:

//------------------------------------------------------
//  Конструкторы
    Complex() {
        this->real = 0;
        this->imaginary = 0;
    }

    Complex(const Rational &real) {
        this->real = real;
        this->imaginary = 0;
    }


    Complex(const Rational &real, const Rational &imaginary) {
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
        *this = *this + other;
        return *this;
    }

    Complex operator-(const Complex &other) {   //-
        return Complex(this->real - other.real, this->imaginary - other.imaginary);
    }

    Complex &operator-=(const Complex &other) {  //-=
        *this = *this - other;
        return *this;
    }

    Complex operator*(const Complex &other) {  //*
        Complex result;
        result.real = real * other.real - imaginary * other.imaginary;
        result.imaginary = real * other.imaginary + imaginary * other.real;
        return result;
    }

    Complex &operator*=(const Complex &other) {  //*=
        return *this = *this * other;
    }

    Complex operator/(const Complex &other) {  // /
        Complex result;
        auto sqr = power(other.real, 2) + power(other.imaginary, 2);
        result.real = (this->real * other.real + this->imaginary * other.imaginary) / sqr;
        result.imaginary = (this->imaginary * other.real - this->real * other.imaginary) / sqr;
        return result;
    }

    Complex &operator/=(const Complex &other) {  // /=
        return *this = *this / other;
    }

    Complex operator-() {
        return Complex(-this->real, -this->imaginary);
    }
//============================================
// Methods

    Rational &GetReal() {
        return this->real;
    }

    Rational &GetIm() {
        return this->imaginary;
    }

    void SetReal(Rational &real) {
        this->real = real;
    }

    void SetIm(Rational &imaginary) {
        this->imaginary = imaginary;
    }

    Rational arg() {
        double pi = 3.14;
        if (this->real == 0 and this->imaginary == 0)
            return 0;
        if (this->real > 0)
            return atan((this->imaginary / this->real).toDouble());
        if (this->real < 0 and this->imaginary > 0)
            return pi + atan((this->imaginary / this->real).toDouble());
        if (this->real < 0 and this->imaginary < 0)
            return -pi + atan((this->imaginary / this->real).toDouble());
        if (this->real == 0 and this->imaginary > 0)
            return pi / 2;
        else return -pi / 2;
    }

    Rational abs() {
        Complex newr;
        newr.real = this->real * this->real;
        newr.imaginary = this->imaginary * this->imaginary;
        return sqrt((newr.real+newr.imaginary).toDouble());
    }

    friend Rational power(Rational num, int deg);

    Complex stepen(int deg) {
        Complex result;
        Rational temp = deg;
        result.real = power(this->abs(), deg) * cos((this->arg() * temp).toDouble());
        result.imaginary = power(this->abs(), deg) * sin((this->arg() * temp).toDouble());
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
        return os << complex.real << " - " << -(complex.imaginary) << "i";
    }


};

int main() {
    Complex a(-1, -1);
    Complex b(-10.54, -3.6);
    Complex c(10.54, 3.6);
    cout << b;


}