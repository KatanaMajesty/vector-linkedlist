#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>

enum StickType
{
    COMMON, UNUSUAL, RARE, LEGENDARY
};

struct HogwartsStudent
{
    char faculty;
    StickType type;
    unsigned int empl_percentage;

    HogwartsStudent() = default;
    HogwartsStudent(char faculty, StickType type, unsigned int percentage);
    // just for debug
    HogwartsStudent(const HogwartsStudent& student);
    ~HogwartsStudent();

    void print() const;
};

class Vector
{
    HogwartsStudent* _data;
    size_t _capacity = 0;
    size_t _size = 0;

    void _reallocate(size_t _newcapacity);
public:
    // default size constructor
    Vector(); // ok
    // non-default size constructor
    Vector(size_t capacity); // ok
    // lvalue ref constructor
    Vector(const Vector& vec); // ok
    // rvalue ref constructor
    Vector(Vector&& vec) noexcept __attribute_deprecated__; // ? есть ли этому практическое применение?
    ~Vector(); // ok
    // [] operator
    const HogwartsStudent& operator[](size_t i); // ok
    // lvalue push_back
    void push_back(const HogwartsStudent& student); // ok
    
    // pop_back(): Что лучше? Возврат копии или возврат ref или const ref, который потом самостоятельно придётся удалять?
    // returns and removes last element in vector
    HogwartsStudent pop_back() __attribute_warn_unused_result__; // ? можно ли реализовать с помощью возврата const ref?
    // get an i element of vector
    const HogwartsStudent& get(size_t i); // ok
    // returns current size of vector
    inline size_t size() const noexcept {return _size;} // ok
    // prints all elements of vector
    void print() const noexcept; // ok
    // clears all elements of vector
    void clear(); // ok, _capacity 0 -> 2
    // pushes elements at the beginning of vector
    void push_front(const HogwartsStudent& student); // ok
    // returns first element in vector
    HogwartsStudent pop_front() __attribute_warn_unused_result__; // ok
    // worst O(n), average O(_size - i), best O(1)
    void insert(const HogwartsStudent& student, size_t i); // ok
    // worst O(n), average O(_size - i), best O(1)
    void remove(size_t i); // ok
};

class LinkedList
{
    struct Node;
    
    size_t _size;
    Node* head;
    Node* tail;
public:
    // value constructor
    LinkedList();
    // copy constructor
    LinkedList(const LinkedList& list);
    // default destructor
    ~LinkedList();
    // add element to the front of linkedlist
    void push_front(const HogwartsStudent& student) ;
    void push_back(const HogwartsStudent& student) ;
    // get a reference of i element of linkedlist or nullptr
    const HogwartsStudent& get(size_t i) const;
    // get last element of linkedlist
    HogwartsStudent pop_back() __attribute_warn_unused_result__ ;
    // get first element of linkedlist
    HogwartsStudent pop_front() __attribute_warn_unused_result__ ;

    inline size_t size() const noexcept { return _size; }
    void print() const;
    void clear();
    // worst O(n)
    void insert(const HogwartsStudent& student, size_t i);
    void remove(size_t i);
    void reverse();
    int hasCycle();
};

struct LinkedList::Node
{
    HogwartsStudent data;
    Node* next;
    Node* prev;

    Node(const HogwartsStudent& student);
};