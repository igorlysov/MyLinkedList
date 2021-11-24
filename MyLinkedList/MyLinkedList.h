//
// Created by мвидео on 15.11.2021.
//

#ifndef LINKEDLIST__LAB_MYLINKEDLIST_H
#define LINKEDLIST__LAB_MYLINKEDLIST_H

#include <iostream>
#include <initializer_list>
#include "ArgumentException.h"

template<class Item>
class MyLinkedList {
private:
    int _size;
    typedef struct Node{
        Item _data;
        Node* _prev;
        Node* _next;
    }Node;
    Node* _head, *_tail;
    enum {
        up = 0,
        down = 1,
    };

    /* Поиск узла в списке */
    /* Теперь в зависимости от значения count будет осуществляться поиск
     * либо сверху вниз (down), либо снизу вверх (up). При удалении элементов,
     * например из центра списка, при прохождении его от первого элемента,
     * наткнемся на пустую область памяти - поиск снизу вверх невозможен.
     * В этом случае пойдем из конца в начало. */
    Node& FindElement(int pos, int count=up) const {
        Node* currentNode;
        if (count == up) {
            currentNode = _head;
            for (int i = 1; i <= pos; i++)
                currentNode = currentNode->_next;
        } else {
            currentNode = _tail;
            for (int i = _size - 2; i >= pos; i--)
                currentNode = currentNode->_prev;
        }

        return *currentNode;
    }
public:
    /* Конструкторы и деструкторы - инициализация списка */
    /*
     * List : ...
     * */
    MyLinkedList() {
        _head = _tail = nullptr;
        _size = 0;
    }

    /* MyLinkedList(3)
     * List : null -> head = 3 = tail -> null
     * */
    explicit MyLinkedList(Item newItem) {
        _size = 1;
        _head = _tail = new Node;

        _head->_prev = _head->_next = nullptr;
        _head->_data = newItem;
    }

    /* Также является конструктором копирования */
    MyLinkedList(const MyLinkedList& otherList) {
        this->~MyLinkedList();
        _head = _tail = nullptr;
        _size = 0;

        Node* temp = otherList._head;
        while(temp != 0) {
            Add(temp->_data);
            temp = temp->_next;
        }
    }

    /*
     * MyLinkedList<int> list {1, 2, 3, 4}
     * list : null -> head = 1 -> 2 -> 3 -> 4 = tail -> null
     * */
    MyLinkedList(const std::initializer_list<Item>& initList) {
        _head = _tail = nullptr;
        _size = 0;
        /* Сможем инициализировать объекта списком инициализации -
         * аналогом списка Item:
         * MyLinkedList<Item> list {item1, item2, item3, ...} */
        int position = 0;
        for (auto element : initList) {
            Add(element, position);
            position++;
        }
        _size = position;
    }

    ~MyLinkedList() {
        Delete(0, _size);
    }
    /* Добавление в начало и произвольное место */
    MyLinkedList& Add(const Item& newData, int pos=0) {
        if (pos < 0) throw PositionException();

        Node* tempNode = new Node;
        tempNode->_data = newData;
        if (pos >= _size) {
            _tail = tempNode;
            tempNode->_next = nullptr;
        } else {
            tempNode->_next = &FindElement(pos);
            tempNode->_next->_prev = tempNode;
        }

        if (pos == 0) {
            tempNode->_prev = nullptr;
            _head = tempNode;
        } else if (_size != 0 && pos < _size) {
            tempNode->_prev = &FindElement(pos - 1);
            tempNode->_prev->_next = tempNode;
        } else if (_size != 0 && pos >= _size) {
            tempNode->_prev = &FindElement(_size - 1);
            tempNode->_prev->_next = tempNode;
        }
        _size++;

        return *this;
    }
    /* Удаление узлов, начиная с узла, который указан в pos
     * (Удаление корня является частным случаем с pos=0, range=1) */
    MyLinkedList& Delete(int pos, int range=1) {
        if (range < 0) throw RangeException();
        if (pos < 0 || pos > _size) throw PositionException();

        int tempSize = _size;
        /* Сначала освобождаем ячейки памяти занятые элементами, которые
         * попали в указанный через range участок и параллельно считаем
         * новый размер нашего списка */
        for (int i = pos; i < pos + range && i < _size; i++, tempSize--) {
            delete &FindElement(i, down);

        }
        /* Если удалили все элементы */
        if (tempSize == 0) {
            _head = _tail = nullptr;
        } else {
            /* 1) Удалено заданное количество элементов, начиная с первого
             * 2) Удалены узлы, не начиная с первого, вплоть до последнего включительно
             * 3) Удалены узлы, не начиная с первого, но не доходя до последнего */
            if (pos == 0) /* (1) */ {
                _head = &FindElement(pos + range, down);
                _head->_prev = nullptr;
            } else if (pos + range >= _size) /* (2) */ {
                _tail = &FindElement(pos - 1);
                _tail->_next = nullptr;
            }
            else /* (3) */ {
                /* Сшиваем конец одного куска списка с началом другого down
                 * указывает нам о том, что поиск элемента идет сверху вниз
                 * Логично, что в одних случаях надо идти сверху вниз, а в
                 * других - наоборот.
                 * Это вызвано появлением пустого (удаленного) участка в центре
                 * списка ибо два куска его еще не сшиты между собой. Но у нас
                 * имеются указатели _head и _tail, каждый из которых указывает
                 * на отдельный кусок и можно таким образом проводить поиск в
                 * каждом из них */

                /* Пришиваем левый к правому */
                FindElement(pos - 1)._next = &FindElement(pos + range, down);
                /* Пришиваем правый к левому */
                FindElement(pos + range, down)._prev = &FindElement(pos - 1);
            }
        }
        _size = tempSize;

        return *this;
    }
    /* Удаление корня списка */
    MyLinkedList& DeleteHead() {
        return Delete(0);
    }
    /* Вывод элементов списка в прямом порядке */
    void Print() {
        Node *tempNode = _head;
        while (tempNode && tempNode != _tail) {
            std::cout << tempNode->_data << "->";
            tempNode = tempNode->_next;
        }
        if (tempNode) std::cout << tempNode->_data << std::endl;
        else std::cout << "Empty list" << std::endl;
    }
    /* Вывод элементов списка в обратном порядке */
    void ReversePrint() {
        Node *tempNode = _head;

        while (tempNode->_next != nullptr)
            tempNode = tempNode->_next;

        while (tempNode && tempNode != _head) {
            std::cout << tempNode->_data << "<-";
            tempNode = tempNode->_prev;
        }
        if (tempNode) std::cout << tempNode->_data << std::endl;
        else std::cout << "Empty list" << std::endl;
    }
    /* Взаимообмен двух узлов списка */
    void SwapTwo(Item elemFirst, Item elemSecond) {
        /* Если elemFirst и posSecond равны - ничего не меняем */
        if (elemFirst == elemSecond)
            return;
        /* Ищем элемент elemFirst и предыдущий ему */
        Node* xCurr = _head;
        while (xCurr && xCurr->_data != elemFirst) {
            xCurr = xCurr->_next;
        }
        /* Ищем элемент elemSecond и предыдущий ему */
        Node* yCurr = _head;
        while (yCurr && yCurr->_data != elemSecond) {
            yCurr = yCurr->_next;
        }
        /* Если elemFirst или elemSecond не в списке */
        if (xCurr == nullptr || yCurr == nullptr)
            return;
        /* Меняем содержимое */
        Item tempData = xCurr->_data;
        xCurr->_data = yCurr->_data;
        yCurr->_data = tempData;
    }
    /* Перегрузка оператора присваивания */
    MyLinkedList& operator=(const MyLinkedList& otherList) {
        /* Проверка на самоприсваивание */
        if(this == &otherList)
            return *this;
        /* Удаление старого списка */
        this->~MyLinkedList();
        Node* tempList = otherList._head;

        /* Копируем элементы */
        while(tempList != 0) {
            Add(tempList->_data);
            tempList = tempList->_next;
        }
        /* Если бы возвращаемое значение было void, то метод бы
         * работал, но нельзя было бы использовать цепочку из
         * приравниваний :
         * можно использовать так: list1 = list2 = list3; */
        return *this;
    }
};
#endif //LINKEDLIST__LAB_MYLINKEDLIST_H
