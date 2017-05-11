//
// Created by Аришка) on 12.05.17.
//

#include "rational.h"
#include <iostream>

int main() {
    rational a(3,2);
    rational b(3,2);
    rational c(3,4);
    rational d = a- b;
    std::cout << d.getNum() << '/' << d.getDenom() << std::endl;
}