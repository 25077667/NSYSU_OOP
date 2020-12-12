#ifndef __FORM_H__
#define __FORM_H__
#include <iostream>
#include <sstream>

struct Bound_form;

class Form
{
private:
    friend std::ostream &operator<<(std::ostream &, const Bound_form &);
    int prc;
    std::ios_base::fmtflags fmt;

public:
    explicit Form(int p = 6) : prc(p) { fmt = std::ios_base::fmtflags(); }
    ~Form() = default;
    Bound_form operator()(double d) const;

    Form &scientific()
    {
        fmt = std::ios_base::scientific;
        return *this;
    }

    Form &fixed()
    {
        fmt = std::ios_base::fixed;
        return *this;
    }

    Form &general()
    {
        fmt = std::ios_base::fmtflags();
        return *this;
    }

    Form &precision(int p)
    {
        prc = p;
        return *this;
    }
};

struct Bound_form {
    const Form &f;
    double val;
    Bound_form(const Form &ff, double v) : f(ff), val(v) {}
};

Bound_form Form::operator()(double d) const
{
    return Bound_form(*this, d);
}

std::ostream &operator<<(std::ostream &os, const Bound_form &bf)
{
    std::ostringstream s;
    s.precision(bf.f.prc);
    s.setf(bf.f.fmt, std::ios_base::floatfield);
    s << bf.val;

    return os << s.str();
}

#endif