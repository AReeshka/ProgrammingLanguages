#ifndef LAZY_STRING_H
#define LAZY_STRING_H


#include <iostream>
#include <string>
#include <mutex>

class lazy_string {
private:
    struct shared {
        std::string data;
        int links;

        shared() {
            data = std::string();
            links = 1;
        }

        shared(const std::string &s) {
            data = s;
            links = 1;
        }
    };

    struct help {
    private:
        lazy_string *str;
        int ind;

    public:
        help(lazy_string *s, int pos) {
            str = s;
            ind = pos;
        }

        help &operator=(const char c) {
            str->ref_counter();
            str->smart_pointer->data[ind] = c;
            return *this;
        }

        operator char() const {
            return str->smart_pointer->data[ind];
        }
    };

    shared *smart_pointer;
    int lengh, index;
    std::mutex mut;
    void ref_counter();

public:
    lazy_string();

    ~lazy_string();

    lazy_string(const std::string &);

    lazy_string(const lazy_string &);

    char at(size_t) const;

    size_t size() const;

    size_t length() const;


    help operator[](size_t);

    char operator[](size_t) const;


    friend std::ostream &operator<<(std::ostream &, lazy_string &);

    friend std::istream &operator>>(std::istream &, lazy_string &);

    lazy_string substr(size_t, size_t);
};

#endif
