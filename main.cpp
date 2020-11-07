#include <iostream>
#include <cmath>
#include <ostream>
#include <string>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

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

    static constexpr int eps = 1000;

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


TEST_CASE("Construct") {
    SECTION("Rational") {
        const Rational a(3.2);
        const Rational Num(5, 10);
        REQUIRE(Num.GetNumerator() == 1);
        REQUIRE(Num.GetDenominator() == 2);
        REQUIRE(a.GetNumerator() == 16);
        REQUIRE(a.GetDenominator() == 5);
    }
    SECTION("Complex") {
        const Rational FirstNum(5, 10);
        const Rational NumI(3, 4);
        const Complex Num(FirstNum, NumI);
        const Rational FirstNum1;
        const Rational NumI1;
        const Complex Num1;
        const Complex Num2(Num);
        REQUIRE(Num.GetReal() == FirstNum);
        REQUIRE(Num.GetIm() == NumI);
        REQUIRE(Num1.GetReal() == FirstNum1);
        REQUIRE(Num1.GetIm() == NumI1);
        REQUIRE(Num2.GetReal() == FirstNum);
        REQUIRE(Num2.GetIm() == NumI);
    }
}
TEST_CASE("Setters") {
    const Rational FirstNum(5, 10);
    const Rational NumI(3, 4);
    Complex Num;
    Num.SetReal(FirstNum);
    Num.SetIm(NumI);
    REQUIRE(Num.GetReal() == FirstNum);
    REQUIRE(Num.GetIm() == NumI);
}

TEST_CASE("Complex = Complex") {
    Complex a(12.2, 8);
    Complex b(12.2, 8);
    a = b;
    REQUIRE(a == b);
}

TEST_CASE("Complex == Complex") {
    Complex a(1221, 0);
    Complex b(1221, 0);
    REQUIRE(a == b);
}

TEST_CASE("Complex != Complex") {
    Complex a(12.2, 8);
    Complex b(22, 12);
    REQUIRE(a != b);
}

TEST_CASE("Complex + Complex") {
    Complex a(12.2, 8);
    Complex b(22, 8);
    Complex c = a + b;
    REQUIRE(c.GetReal().toDouble()==Approx(34.2).epsilon(0.001));
    REQUIRE(c.GetIm()==16);
}

TEST_CASE("Complex - Complex") {
    Complex a(4.2, -33);
    Complex b(212, 0.2);
    Complex c = a - b;
    REQUIRE(c.GetReal().toDouble()==Approx(-207.79).epsilon(0.001));
    REQUIRE(c.GetIm().toDouble()==Approx(-33.2));
}
TEST_CASE("Complex * Complex") {
    Complex a(12.2, 8);
    Complex b(22, 8);
    Complex c = a * b;
    REQUIRE(c.GetReal().toDouble()==Approx(204.378));
    REQUIRE(c.GetIm().toDouble()==Approx(273.59));
}

//TEST_CASE("Complex / Complex") {
//    Complex a(-122, 0.9);
//    Complex b(22.22, 8.87);
//    Complex c = a / b;
//    REQUIRE(c.GetReal().toDouble()==Approx(-4.72192));
//    REQUIRE(c.GetIm().toDouble()==1);
//}
TEST_CASE("Complex += Complex") {
    Complex a(12.2, 8);
    Complex b(22, 8);
    Complex c = a + b;
    a+=b;
    REQUIRE(a.GetReal()==c.GetReal());
    REQUIRE(a.GetIm()==c.GetIm());
}

TEST_CASE("Complex -= Complex") {
    Complex a(1872, 78.87);
    Complex b(-2.862, 8);
    Complex c = a - b;
    a-=b;
    REQUIRE(a.GetReal()==c.GetReal());
    REQUIRE(a.GetIm()==c.GetIm());
}
TEST_CASE("Complex *= Complex") {
    Complex a(-12.2, 34);
    Complex b(265.434, 0);
    Complex c = a * b;
    a*=b;
    REQUIRE(a.GetReal()==c.GetReal());
    REQUIRE(a.GetIm()==c.GetIm());
}

TEST_CASE("abs"){
    Complex a(5,3.7);
    REQUIRE(a.abs().toDouble()==Approx(6.22012).epsilon(0.001));
}

TEST_CASE("arg"){
    Complex a(5,3.7);
    REQUIRE(a.arg().toDouble()==Approx(0.63707).epsilon(0.001));
}

TEST_CASE("power"){
    SECTION("Rational"){
        Rational a(16,17);
        REQUIRE(power(a,2).toDouble()==Approx(0.8858).epsilon(0.001));
    }
    SECTION("Complex") {
        Complex a(5,3.7);
        a=power(a,4);
        REQUIRE(a.GetReal().toDouble()==Approx(-1241.0838).epsilon(0.001));
        REQUIRE(a.GetIm().toDouble()==Approx(836.9399).epsilon(0.001));
    }

}

TEST_CASE("Rational == Rational") {
    Rational a(1221, 23);
    Rational b(1221, 23);
    REQUIRE(a == b);
}

TEST_CASE("Rational != Rational") {
    Rational a(1221, 23);
    Rational b(1221, 2.3);
    REQUIRE(a != b);
}

TEST_CASE("Rational = Rational") {
    Rational a(1221, 23);
    Rational b(122.1, 2.3);
    a=b;
    REQUIRE(a == b);
}

TEST_CASE("Rational + Rational") {
    Rational a(1221, 23);
    Rational b(122, 2);
    Rational c=a+b;
    Rational n (2.45);
    Rational x= b+n;
    REQUIRE(c.GetNumerator()==2624);
    REQUIRE(c.GetDenominator()==23);
    REQUIRE(x.GetNumerator()==1269);
    REQUIRE(x.GetDenominator()==20);
}

TEST_CASE("Rational - Rational") {
    Rational a(21, 3);
    Rational b(12, 9);
    Rational c=a-b;
    Rational n (24.5);
    Rational x= b-n;
    REQUIRE(c.GetNumerator()==17);
    REQUIRE(c.GetDenominator()==3);
    REQUIRE(x.GetNumerator()==-139);
    REQUIRE(x.GetDenominator()==6);
}

TEST_CASE("Rational * Rational") {
    Rational a(21, 3);
    Rational b(12, -9);
    Rational c=a*b;
    Rational n (24.5);
    Rational x= b*n;
    REQUIRE(c.GetNumerator()==-28);
    REQUIRE(c.GetDenominator()==3);
    REQUIRE(x.GetNumerator()==-98);
    REQUIRE(x.GetDenominator()==3);
}

TEST_CASE("Rational / Rational") {
    Rational a(14, 21);
    Rational b(-15, 7);
    Rational c=a/b;
    Rational n (24.5);
    Rational x= b/n;
    REQUIRE(c.GetNumerator()==-14);
    REQUIRE(c.GetDenominator()==45);
    REQUIRE(x.GetNumerator()==-30);
    REQUIRE(x.GetDenominator()==343);
}

//TEST_CASE("Complex /= Complex") {
//    Complex a(12.2, 8);
//    Complex b(22, 8);
//    Complex c = a / b;
//    a/=b;
//    REQUIRE(a.GetReal()==c.GetReal());
//    REQUIRE(a.GetIm()==c.GetIm());
//}


//int main() {
//    const Rational a(16,17);
//    cout<<a;
//    cout<<power(a,2);
//
//
//}

