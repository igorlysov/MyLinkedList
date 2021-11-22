//
// Created by мвидео on 15.11.2021.
//

#include "Pair.h"

std::ostream &operator<<(std::ostream &os, const Pair &pair) {
    os << "(" << pair._first << ":" << pair._second << ")";
    return os;
}

std::istream &operator>>(std::istream &in, Pair &pair) {
    in >> pair._first;
    in >> pair._second;
    return in;
}

Pair &Pair::operator=(const Pair &otherPair) {
    /* Проверка на самоприсваивание */
    if(this == &otherPair)
        return *this;
    /* Переопределяем поля Pair */
    this->_first = otherPair._first;
    this->_second = otherPair._second;
    /* Возвращаем *this, чтобы была возможна цепочка присваиваний */
    return *this;
}

bool operator==(const Pair &left, const Pair &right) {
    return (left._first == right._first) && (left._second == right._second);
}

bool operator!=(const Pair &left, const Pair &right) {
    return (left._first != right._first) || (left._second != right._second);
}
