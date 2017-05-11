#include "rational.h"
#include <algorithm>

rational::rational() {};

rational::rational(int num) {
    this->num = num;
    this->denom = 1;
};

rational::rational(int num, int denom) {
    this->num = num;
    this->denom = denom;
    int gcd = std::__gcd(num, denom);
    num /= gcd;
    denom /= gcd;
    this->num = num;
    this->denom = denom;
};

int rational::getNum() const {
    return num;
};

int rational::getDenom() const {
    return denom;
};

rational rational::operator+(rational const &x) const {
    int a = num*x.denom+x.num*denom;
    int b = denom*x.denom;
    int gcd = std::__gcd(a,b);
    return rational(a/gcd,b/gcd);

};

rational rational::operator-(rational const &x) const {
    int a = num*x.denom-x.num*denom;
    int b = denom*x.denom;
    int gcd = std::__gcd(a,b);
    return rational(a/gcd,b/gcd);
};

rational rational::operator*(rational const &x) const {
    int a = num*x.num;
    int b = denom*x.denom;
    int gcd = std::__gcd(a,b);
    return rational(a/gcd,b/gcd);
};

rational rational::operator/(rational const &x) const {
    int a = num*x.denom;
    int b = denom*x.num;
    int gcd = std::__gcd(a,b);
    return rational(a/gcd,b/gcd);
};

rational::~rational() {};
