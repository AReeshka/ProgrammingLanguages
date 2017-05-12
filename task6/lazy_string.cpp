#include "lazy_string.h"
#include <string>

void lazy_string::ref_counter() {
    if (smart_pointer->links == 1) return;
    shared *now = new shared((smart_pointer->data).substr(index, lengh));
    (smart_pointer->links)--;
    smart_pointer = now;
    index = 0;
}

lazy_string::lazy_string() {
    smart_pointer = new shared();
    index = lengh = 0;
}

lazy_string::~lazy_string() {
    (smart_pointer->links)--;
    if (smart_pointer->links == 0)
        delete smart_pointer;
}

lazy_string::lazy_string(const std::string &q) {
    smart_pointer = new shared(q);
    index = 0;
    lengh = q.size();
}

lazy_string::lazy_string(const lazy_string &q) {
    smart_pointer = q.smart_pointer;
    (smart_pointer->links)++;
    index = q.index;
    lengh = q.lengh;
}


char lazy_string::at(size_t ind) const {
    return smart_pointer->data[index + ind];
}

size_t lazy_string::size() const {
    return lengh;
}

size_t lazy_string::length() const {
    return lengh;
}


lazy_string::help lazy_string::operator[](size_t pos) {
    return help(this, pos);
}

char lazy_string::operator[](size_t pos) const {
    return smart_pointer->data[index + pos];
}


std::ostream &operator<<(std::ostream &out, lazy_string &q) {
    for (size_t i = q.index; i < q.index + q.lengh; i++) {
        out << (q.smart_pointer->data[i]);
    }
    return out;
}

std::istream &operator>>(std::istream &in, lazy_string &q) {
    q.ref_counter();
    in >> q.smart_pointer->data;
    q.index = 0;
    q.lengh = q.smart_pointer->data.length();
    return in;
}

lazy_string lazy_string::substr(size_t begin, size_t len) {
    lazy_string *tmp = new lazy_string();
    tmp->smart_pointer = smart_pointer;
    tmp->index = index + begin;
    tmp->lengh = len;
    (smart_pointer->links)++;
    return *tmp;
}

int main() {
    return 0;
}