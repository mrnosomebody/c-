#include <iostream>
#include <cmath>
#include <ostream>
#include <string>

using namespace std;

template<typename T>
T power(T num, int deg) {
    T result(static_cast<int>(1));
    while (deg) {
        num *= num;
        deg /= 2;
        if (deg % 2 == 1) {
            result *= num;
            deg--;
        }
    }
    return result;
}


class Rational {

private:
    int numerator, denominator;

    void reduce() {
        if (denominator < 0) {
            numerator = -(numerator);
            denominator = -denominator;
        }
        int divider = gcd(numerator, denominator);
        numerator /= divider;
        denominator /= divider;
    }

    static int gcd(int num, int den) {
        while (num) {
            int a = den % num;
            den = num;
            num = a;
        }
        return abs(den);
    }


    template<typename T>
    static T lcm(T a, T b) { // НОК
        return (a * b) / gcd(a, b);
    }

    static constexpr int eps = 10000;

public:
    //========================================
    // Constructors
    Rational(double numerator) {
        denominator = eps;
        this->numerator = numerator * denominator;
        reduce();
    }


    Rational(int numerator = 0, int denominator = 1) : numerator(numerator), denominator(denominator) {
        reduce();
    }


    //==================================================
    // Methods

    Rational &operator=(const Rational &other) = default;


    Rational operator+(const Rational &other) const {
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

    Rational operator-(const Rational &other) const {
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

    Rational operator*(const Rational &other) const {
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

    Rational operator/(const Rational &other) const {
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
        return os;
    }

    Rational stepen(int deg) {
        this->numerator = power(this->numerator, deg);
        this->denominator = power(this->denominator, deg);
        reduce();
        return *this;
    }

    double toDouble() const {
        return (static_cast<double>(this->numerator ) / static_cast<double>(this->denominator));
    }

    double GetNumerator() const noexcept {
        return numerator;
    }

    double GetDenominator() const noexcept {
        return denominator;
    }

    Rational SetNumerator(double numerator) noexcept {
        this->numerator = numerator;
        return *this;
    }

    Rational SetDenominator(double denominator) noexcept {
        this->denominator = denominator;
        return *this;
    }
};


class Complex {
private:
    Rational real, imaginary;

public:

//------------------------------------------------------
//  Конструкторы
    Complex() = default;

    Complex(const Rational &real) {
        this->real = real;

    }


    Complex(const Rational &real, const Rational &imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }
//------------------------------------------------------------------------------------
// Перегрузки

    bool operator==(const Complex &other) const {    //==
        return this->real == other.real and this->imaginary == other.imaginary;
    }

    bool operator!=(const Complex &other) const {    //!=
        return !(this->real == other.real and this->imaginary == other.imaginary);
    }

    Complex &operator=(const Complex &other) = default;

    Complex operator+(const Complex &other) const {   //+
        return Complex(this->real + other.real, this->imaginary + other.imaginary);
    }

    Complex &operator+=(const Complex &other) {  //+=
        *this = *this + other;
        return *this;
    }

    Complex operator-(const Complex &other) const {   //-
        return Complex(this->real - other.real, this->imaginary - other.imaginary);
    }

    Complex &operator-=(const Complex &other) {  //-=
        *this = *this - other;
        return *this;
    }

    Complex operator*(const Complex &other) const {  //*
        Complex result;
        result.real = real * other.real - imaginary * other.imaginary;
        result.imaginary = real * other.imaginary + imaginary * other.real;
        return result;
    }

    Complex &operator*=(const Complex &other) {  //*=
        return *this = *this * other;
    }

    Complex operator/(const Complex &other) const {  // /
        Complex result;
        auto sqr = power(other.real, 2) + power(other.imaginary, 2);
        result.real = (this->real * other.real + this->imaginary * other.imaginary) / sqr;
        result.imaginary = (this->imaginary * other.real - this->real * other.imaginary) / sqr;
        return result;
    }

    Complex &operator/=(const Complex &other) {  // /=
        return *this = *this / other;
    }

    Complex operator-() const {
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

    const Rational &GetReal() const {
        return this->real;
    }

    const Rational &GetIm() const {
        return this->imaginary;
    }

    Complex SetReal(Rational other) {
        this->real = other;
        return *this;
    }

    Complex SetIm(Rational other) {
        this->imaginary = other;
        return *this;
    }

    Rational arg() const {
        double pi = 3.14;
        if (this->real == Rational() and this->imaginary == Rational())
            return {};
        if (this->real > Rational())
            return atan((this->imaginary / this->real).toDouble());
        if (this->real < Rational() and this->imaginary > Rational())
            return pi + atan((this->imaginary / this->real).toDouble());
        if (this->real < Rational() and this->imaginary < Rational())
            return -pi + atan((this->imaginary / this->real).toDouble());
        if (this->real == Rational() and this->imaginary > Rational())
            return pi / 2;
        else return -pi / 2;
    }

    Rational abs() const {
        Complex newr;
        newr.real = this->real * this->real;
        newr.imaginary = this->imaginary * this->imaginary;
        return sqrt((newr.real + newr.imaginary).toDouble());
    }


    friend ostream &operator<<(ostream &os, const Complex &complex) {
        if (complex.real == Rational())
            return os << complex.imaginary << "i";
        if (complex.imaginary == Rational())
            return os << complex.real;
        if (complex.imaginary > Rational())
            return os << complex.real << " + " << complex.imaginary << "i";
        if (complex.real == Rational() and complex.imaginary == Rational())
            return os << 0;
        return os << complex.real << " - " << -(complex.imaginary) << "i";
    }


};

int main() {
    const Complex a(-16.8, 12.756);
    Complex b(89793782, 4321);
    const Complex c(10.54, 3.6);

    cout << power(a, 2).GetReal().toDouble();


}

