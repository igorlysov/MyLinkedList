//
// Created by мвидео on 19.11.2021.
//

#ifndef LINKEDLIST__LAB_ARGUMENTEXCEPTION_H
#define LINKEDLIST__LAB_ARGUMENTEXCEPTION_H

#include <exception>
#include <string>

class ArgumentException : public std::exception {
public:
    virtual const char* what() noexcept = 0;
};

class PositionException : public ArgumentException {
public:
    const char* what() noexcept override {
        return "Invalid position!";
    }
};

class RangeException : public ArgumentException {
public:
    const char* what() noexcept override {
        return "Invalid range!";
    }
};

class ChoiceException : public ArgumentException {
public:
    const char* what() noexcept override {
        return "Invalid choice!";
    }
};

class SizeException : public ArgumentException {
public:
    const char* what() noexcept override {
        return "Empty list!";
    }
};


#endif //LINKEDLIST__LAB_ARGUMENTEXCEPTION_H
