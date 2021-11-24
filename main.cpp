#include "TestUI.h"
#include <list>

void TestMenu() {
    std::cout << "Choose a type for Container test" << std::endl <<
              "1 - Int" << std::endl <<
              "2 - Float" << std::endl <<
              "3 - Double" << std::endl <<
              "4 - Pair (custom type : Pair = (int : double))" << std::endl;
    int choice; std::cin >> choice;
    try {
        if (choice < 1 || choice > 4) {
            throw ChoiceException();
        }
    } catch (ChoiceException& exception) {
        std::cerr << exception.what() << std::endl;
    }

    switch (choice) {
        case 1: {
            TestUI<int>::ITest();
            return;
        }
        case 2: {
            TestUI<float>::ITest();
            return;
        }
        case 3: {
            TestUI<double>::ITest();
            return;
        }
        case 4: {
            TestUI<Pair>::ITest();
            return;
        }
    }
}

int main() {
    TestMenu();
    MyLinkedList<int> list;
    return 0;
}

/*
 * item2.next - > item3; item2.prev -> item1 ...
 *
 *
 * null -> head = item1 -> item2 -> item3 -> ... -> item_n = tail -> null
 *
 *
 *
 * */












