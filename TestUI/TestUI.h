//
// Created by мвидео on 19.11.2021.
//

#ifndef LINKEDLIST__LAB_TESTUI_H
#define LINKEDLIST__LAB_TESTUI_H

#include "Pair.h"
#include "MyLinkedList.h"

template<class Item>
class TestUI {
public:
    static void InitData(MyLinkedList<Item>& testList) {
        int amount;
        std::cout << "How many items do you want?" << std::endl;
        std::cin >> amount;
        try {
            if (amount < 0) throw RangeException();
        } catch (RangeException& exception) {
            std::cerr << exception.what() << std::endl;
        }

        std::cout << "Enter an item" << std::endl;
        Item newItem; int position = 0;
        while (amount > 0) {
            std::cout << "#" << position + 1 << std::endl;
            std::cin >> newItem;
            testList.Add(newItem, position);
            amount--; position++;
        }
    }

    static void ITest() {
        MyLinkedList<Item> testableList;
        std::cout << "Let's fill our list" << std::endl;
        TestUI<Item>::InitData(testableList);
        std::cout << "Here it is: " << std::endl;
        testableList.Print();
        int choice;
        std::cout << "What do you want to do with your list?" << std::endl <<
                  "1 - Add node" << std::endl <<
                  "2 - Delete node" << std::endl <<
                  "3 - Delete head" << std::endl <<
                  "4 - Print reversed list" << std::endl <<
                  "5 - Swap two elements" << std::endl;
        while (std::cin >> choice) {
            try {
                if (choice < 1 || choice > 5) {
                    throw ChoiceException();
                }
            } catch (ChoiceException& exception) {
                std::cerr << exception.what() << std::endl;
                continue;
            }

            switch (choice) {
                case 1: {
                    std::cout << "Enter an item and position to add (position=0 by default)" << std::endl;
                    Item newItem; int position; std::cin >> newItem >> position;
                    try {
                        testableList.Add(newItem, position);
                    } catch (PositionException& exception) {
                        std::cerr << exception.what() << std::endl;
                        break;
                    }
                    std::cout << "Updated list" << std::endl;
                    testableList.Print();
                    break;
                }
                case 2: {
                    std::cout << "Enter a position and range to delete (range=1 by default)" << std::endl;
                    int position; int range; std::cin >> position >> range;
                    try {
                        testableList.Delete(position, range);
                    } catch (PositionException& exception) {
                        std::cerr << exception.what() << std::endl;
                        break;
                    } catch (RangeException& exception) {
                        std::cerr << exception.what() << std::endl;
                        break;
                    }
                    std::cout << "Updated list" << std::endl;
                    testableList.Print();
                    break;
                }
                case 3: {
                    testableList.DeleteHead();
                    std::cout << "Head is deleted" << std::endl;
                    std::cout << "Updated list" << std::endl;
                    testableList.Print();
                    break;
                }
                case 4: {
                    std::cout << "Reversed list:" << std::endl;
                    testableList.ReversePrint();
                    break;
                }
                case 5: {
                    std::cout << "Enter two elements to be swapped" << std::endl;
                    Item firstItem; Item secondItem; std::cin >> firstItem >> secondItem;
                    testableList.SwapTwo(firstItem, secondItem);
                    std::cout << "Updated list" << std::endl;
                    testableList.Print();
                    break;
                }
            }
            std::cout << "Press q if you want to quit. Otherwise, pick one option from the list." << std::endl;
        }
    }
};


#endif //LINKEDLIST__LAB_TESTUI_H
