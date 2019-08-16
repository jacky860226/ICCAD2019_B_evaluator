#pragma once
#include <algorithm>
template <typename T>
struct fraction
{
    T n, d;
    fraction(const T &_n = 0, const T &_d = 1) : n(_n), d(_d)
    {
        T t = std::__gcd(n, d);
        n = n / t;
        d = d / t;
        if (d < 0)
        {
            n = -n;
            d = -d;
        }
    }
    fraction operator-() const
    {
        return fraction(-n, d);
    }
    fraction operator+(const fraction &b) const
    {
        return fraction(n * b.d + b.n * d, d * b.d);
    }
    fraction operator-(const fraction &b) const
    {
        return fraction(n * b.d - b.n * d, d * b.d);
    }
    fraction operator*(const fraction &b) const
    {
        return fraction(n * b.n, d * b.d);
    }
    fraction operator/(const fraction &b) const
    {
        return fraction(n * b.d, d * b.n);
    }
    fraction operator+=(const fraction &b)
    {
        return *this = fraction(n * b.d + b.n * d, d * b.d);
    }
    fraction operator-=(const fraction &b)
    {
        return *this = fraction(n * b.d - b.n * d, d * b.d);
    }
    fraction operator*=(const fraction &b)
    {
        return *this = fraction(n * b.n, d * b.d);
    }
    fraction operator/=(const fraction &b)
    {
        return *this = fraction(n * b.d, d * b.n);
    }
    bool operator<(const fraction &b) const
    {
        return n * b.d < b.n * d;
    }
    bool operator>(const fraction &b) const
    {
        return n * b.d > b.n * d;
    }
    bool operator==(const fraction &b) const
    {
        return n * b.d == b.n * d;
    }
    bool operator!=(const fraction &b) const
    {
        return n * b.d != b.n * d;
    }
    bool operator<=(const fraction &b) const
    {
        return n * b.d <= b.n * d;
    }
    bool operator>=(const fraction &b) const
    {
        return n * b.d >= b.n * d;
    }
};