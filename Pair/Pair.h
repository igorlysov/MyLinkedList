//
// Created by мвидео on 15.11.2021.
//

#ifndef LINKEDLIST__LAB_PAIR_H
#define LINKEDLIST__LAB_PAIR_H

#include <iostream>

class Pair {
private:
    int _first;
    double _second;
public:
    explicit Pair(int first=0, double second=0.0) : _first(first), _second(second) {}
    /* Перегрузка вывода Pair */
    friend std::ostream& operator<<(std::ostream&, const Pair&);
    /* Перегрузка ввода Pair */
    friend std::istream& operator>>(std::istream&, Pair&);
    /* Перегрузка присваивания Pair */
    Pair& operator=(const Pair&);
    /* Перегрузка проверки на равенство и неравенство */
    friend bool operator==(const Pair& left, const Pair& right);
    friend bool operator!=(const Pair& left, const Pair& right);
};

#endif //LINKEDLIST__LAB_PAIR_H
