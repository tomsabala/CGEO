
#pragma once
#include <exception>

struct Exception2D : public std::exception{
private:
    char const *msg;
public:
    Exception2D(char const *m) : msg(m){}
    const char * what () const throw () {
        return this->msg;
    }
};
