#include "Complex.h"
#include <cmath>
#include <cstring>

Complex::Complex(const double re, const double im) : real(re), imag(im) {}

Complex::Complex(const Complex &c)
{
    memcpy(this, &c, sizeof(Complex));
}

Complex &Complex::operator=(const Complex &c)
{
    memcpy(this, &c, sizeof(Complex));
    return *this;
}

Complex Complex::Polar(const double leng, const double arg)
{
    this->real = leng * cos(arg);
    this->imag = leng * sin(arg);
    return *this;
}

double Complex::Real()
{
    return this->real;
}

double Complex::Imag()
{
    return this->imag;
}

// Return sum of squares
double Complex::Norm()
{
    return this->imag * this->imag + this->real * this->real;
}

double Complex::Abs()
{
    return sqrt(this->Norm());
}

// Return the principal value of the arc tangent of y/x, expressed in radians.
double Complex::Arg()
{
    return atan2(imag, real);
}

// Preifx increment operator, add both 2 parts
Complex Complex::operator++()
{
    ++this->real;
    ++this->imag;
    return *this;
}

// Postfix increment operator, add both 2 parts
Complex Complex::operator++(int)
{
    auto tmp = *this;
    this->real++;
    this->imag++;
    return tmp;
}

// Preifx decrement operator, minus both 2 parts
Complex Complex::operator--()
{
    --this->real;
    --this->imag;
    return *this;
}

// Postifx decrement operator, minus both 2 parts
Complex Complex::operator--(int)
{
    auto tmp = *this;
    this->real--;
    this->imag--;
    return tmp;
}

Complex::~Complex() {}

// --------------------------------
// Firend functions
// --------------------------------

Complex Polar(const double leng, const double arg)
{
    return Complex(leng * cos(arg), leng * sin(arg));
}

double Norm(const Complex &x)
{
    return x.imag * x.imag + x.real * x.real;
}

double Abs(const Complex &x)
{
    return sqrt(Norm(x));
}

double Arg(const Complex &x)
{
    return atan2(x.imag, x.real);
}

Complex operator+(const Complex &x, const Complex &y)
{
    return Complex(x.real + y.real, x.imag + y.imag);
}

Complex operator-(const Complex &x, const Complex &y)
{
    return Complex(x.real - y.real, x.imag - y.imag);
}

Complex operator*(const Complex &x, const Complex &y)
{
    return Complex(x.real * y.real - x.imag * y.imag,
                   x.real * y.imag + x.imag * y.real);
}

// To divide complex numbers, you must multiply by the conjugate.
Complex operator/(const Complex &x, const Complex &y)
{
    auto conjugate = Complex(y.real, -y.imag);
    auto denominator = x * conjugate;
    return Complex(denominator.real / conjugate.Norm(),
                   denominator.imag / conjugate.Norm());
}

Complex operator+=(Complex &x, const Complex &y)
{
    return (x = x + y);
}

Complex operator-=(Complex &x, const Complex &y)
{
    return (x = x - y);
}

Complex operator*=(Complex &x, const Complex &y)
{
    return (x = x * y);
}

Complex operator/=(Complex &x, const Complex &y)
{
    return (x = x / y);
}

bool operator==(const Complex &x, const Complex &y)
{
    return x.real == y.real && x.imag == y.imag;
}

bool operator!=(const Complex &x, const Complex &y)
{
    return !(x == y);
}

ostream &operator<<(ostream &o, const Complex &x)
{
    o << "(" << x.real << "," << x.imag << ")";
    return o;
}