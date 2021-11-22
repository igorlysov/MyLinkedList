#include "TestUI.h"

void TestMenu() {
    std::cout << "Choose a type for Container test" << std::endl <<
              "1 - Int" << std::endl <<
              "2 - Float" << std::endl <<
              "3 - Double" << std::endl <<
              "4 - Pair (custom type : Pair = (int : double))" << std::endl;
    int choice; std::cin >> choice;
    try {
        if (choice < 0 || choice > 4) {
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
    /*Pair newPair(1,1.0);
    std::cout << newPair << std::endl;
    //MyLinkedList<int> intList {1, 2, 3, 4, 5, 6};
    MyLinkedList<int> intList {1, 2, 3, 4, 5, 6};
    intList.ReversePrint();
    intList.Print();
    intList.SwapTwo(2,3);
    intList.Print();
    MyLinkedList<Pair> pairList {Pair(2, -3.1), Pair(-3, 4.2)};
    pairList.ReversePrint();

    pairList.Add(newPair, 4);
    pairList.Print();
    pairList.Delete(1);
    pairList.Print();
    pairList.DeleteHead();
    pairList.Print();*/
    TestMenu();
    return 0;
}
