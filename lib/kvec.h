#pragma once

#include <stdlib.h>
#include <string.h>
#include <iostream>

// не делайте так (HDD пизда)

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
    HogwartsStudent(char faculty, StickType type, unsigned int percentage)
        : faculty(faculty)
        , type(type)
        , empl_percentage(percentage) 
    {
        // std::cout << "HogwartsStudent value constructor: " << this << std::endl;
    }
    // just for debug
    HogwartsStudent(const HogwartsStudent& student)
        : faculty(student.faculty)
        , type(student.type)
        , empl_percentage(student.empl_percentage)
    {
        // std::cout << "HogwartsStudent copy constructor: " << this << std::endl;
    }
    ~HogwartsStudent()
    {
        // std::cout << "HogwartsStudent destructor: " << this << std::endl;
    }

    void print() const
    {
        printf("Faculty: %c, StickType: %d, Employment percentage: %u%\n", 
                faculty,
                type,
                empl_percentage);
    }

};

class Vector
{
    HogwartsStudent* _data;
    size_t _capacity = 0;
    size_t _size = 0;

    void _reallocate(size_t _newcapacity)
    {
        HogwartsStudent* new_data = new HogwartsStudent[_newcapacity];
        for (int i = 0; i < _size; i++)
            new_data[i] = _data[i];

        delete[] _data;
        _capacity = _newcapacity;
        _data = new_data;
    }
public:
    // default size constructor
    Vector()
        : _capacity(2)
    {
        // std::cout << "default size constructor: " << this << std::endl;
        _data = new HogwartsStudent[_capacity];
    }
    // non-default size constructor
    Vector(size_t capacity)
        : _capacity(capacity)
    {
        // std::cout << "non-default size constructor: " << this << std::endl;
        _data = new HogwartsStudent[_capacity]; 
    }
    // lvalue ref constructor
    Vector(const Vector& vec)
    {
        // std::cout << "lvalue ref constructor: " << this << std::endl;
        _size = vec._size;
        _capacity = vec._capacity;
        _data = new HogwartsStudent[_capacity];

        // copy a block of memory to our new Vector object
        memcpy(_data, vec._data, sizeof(HogwartsStudent) * _size);
    }
    // rvalue ref constructor
    Vector(Vector&& vec) noexcept
    {
        // std::cout << "rvalue ref constructor: " << this << std::endl;
        _size = vec._size;
        _capacity = vec._capacity;
        _data = vec._data;

        // this is really important, so that vec.~Vector() couldn't destroy our _data array
        vec._data = nullptr;
        vec._size = 0;
        vec._capacity = 0;
    }
    ~Vector()
    {
        // std::cout << "Vector destructor: " << this << std::endl;
        delete[] _data;
    }
    // [] operator
    const HogwartsStudent& operator[](size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("access to an element out of size boundaries");

        return _data[i];
    }
    // lvalue push_back
    void push_back(const HogwartsStudent& student)
    {
        // std::cout << "lvalue push_back of: " << &student << std::endl;
        if (_size >= _capacity)
            _reallocate(_capacity * 2);

        _data[_size] = student;
        _size++;
    }
    // rvalue push_back
    void push_back(HogwartsStudent&& student)
    {
        // std::cout << "rvalue push_back of: " << &student << std::endl;
        if (_size >= _capacity)
            _reallocate(_capacity * 2);

        // CHECK
        _data[_size] = student;
        _size++;
    }
    // rvalue pop_back(): returns last element in vector
    HogwartsStudent&& pop_back() __attribute_warn_unused_result__
    {
        // std::cout << "rvalue pop_back of: " << &_data[_size - 1] << std::endl;
        _size--;
        return std::move(_data[_size]);
    }
    const HogwartsStudent& get(size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("access to an element out of size boundaries");
        // std::cout << "Vector::get() returned: " << &_data[i] << std::endl;

        return _data[i];
    }
    // returns current size of vector
    inline size_t size() const noexcept {return _size;}
    // prints all elements of vector
    void print() const noexcept
    {
        for (size_t i = 0; i < _size; i++)
            _data[i].print();
    }
    // clears all elements of vector
    void clear()
    {
        _size = 0;
        _capacity = 0;
        delete[] _data;
    }
    // pushes elements at the beginning of vector
    void push_front(const HogwartsStudent& student)
    {
        // std::cout << "rvalue push_front of: " << &student << std::endl;
        if (_size >= _capacity - 1) // in order to get 1 extra place for new element
            _reallocate(_capacity * 2);

        for (size_t i = _size; i > 0; i--)
            _data[i] = _data[i - 1];

        _data[0] = student;
        _size++;
    }
    // returns first element in vector
    HogwartsStudent pop_front() __attribute_warn_unused_result__
    {
        // // // std::cout << "copy pop_front of: " << &_data[0] << std::endl;
        HogwartsStudent student(_data[0]);
        for (size_t i = 0; i < _size; i++)
            _data[i] = _data[i + 1];

        _size--;
        return student;
    }
    // worst O(n), average O(_size - i), best O(1)
    void insert(const HogwartsStudent& student, size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("insert method invoked out of vector range");

        if (_size >= _capacity)
            _reallocate(_capacity * 2);

        for (size_t j = _size; j > i; j--)
            _data[j] = _data[j - 1];

        _data[i] = student;
        _size++;
    }
    // worst O(n), average O(_size - i), best O(1)
    void remove(size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("remove method invoked out of vector range");

        _data[i].~HogwartsStudent();
        for (int j = i; j < _size; j++)
            _data[j] = _data[j + 1];
        
        _size--;
    }
};

class LinkedList
{
    struct Node
    {
        HogwartsStudent data;
        Node* next;
        Node* prev;

        Node(const HogwartsStudent& student)
            : data(student) {}
    };
    size_t _size;
    Node* head;
    Node* tail;
public:
    // friend class LinkedList;
    // value constructor
    LinkedList()
        : _size(0), head(nullptr), tail(nullptr)
    {
        // std::cout << "LinkedList value constructor: " << this << std::endl;
    }
    // copy constructor
    LinkedList(const LinkedList& list)
    {
        // std::cout << "LinkedList copy constructor: " << this << std::endl;
        _size = list._size;
        // std::cout << list._size << std::endl;
        Node* p = list.head;
        Node* _newp;
        Node* buff = nullptr;
        while (p != nullptr)
        {
            _newp = new Node(p->data);
            if (buff == nullptr)
                head = _newp;
            _newp->prev = buff;
            if (_newp->prev != nullptr)
                _newp->prev->next = _newp;
            
            if (p->next == nullptr) // detect tail
                tail = _newp;

            p = p->next;
            buff = _newp;
        }
    }
    // default destructor
    ~LinkedList()
    {
        // std::cout << "LinkedList destrutor: " << this << std::endl;
        clear();
    }
    // add element to the front of linkedlist
    void push_front(const HogwartsStudent& student) 
    {
        // std::cout << "LinkedList push_front of: " << &student << std::endl;
        Node* node = new Node(student);

        node->next = head;
        node->prev = nullptr;
        head = node;

        _size++;

        if (_size == 1)
            tail = head;
    }
    void push_back(const HogwartsStudent& student) 
    {
        // std::cout << "LinkedList push_back of: " << &student << std::endl;
        Node* node = new Node(student);

        if (tail != nullptr)
            tail->next = node;

        node->next = nullptr;
        node->prev = tail;
        tail = node;
        
        _size++;

        if (_size == 1)
            head = tail;
    }
    // get a reference of i element of linkedlist or nullptr
    const HogwartsStudent& get(size_t i) const
    {
        if (_size == 0)
            throw std::out_of_range("size of linkedlist is 0"); 

        Node *p = tail;
        bool _s = (_size - 1) / 2 > i;
        size_t iter = _size - 1;
        if (_s) // start from head
        {
            p = head;
            iter = 0;
        }
        
        while (p != nullptr)
        {
            if (iter == i)
                return p->data;

            _s ? iter++ : iter--;
            p = _s ? p->next : p->prev;
        }
        throw std::runtime_error("no data was found in linked list");
    }
    // get last element of linkedlist
    HogwartsStudent pop_back() __attribute_warn_unused_result__ 
    {
        if (_size == 0)
            throw std::out_of_range("size of linkedlist is 0");

        HogwartsStudent student = tail->data;
        Node* p = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete p;
        _size--;
        return student;
    }
    // get first element of linkedlist
    HogwartsStudent pop_front() __attribute_warn_unused_result__ 
    {
        if (_size == 0)
            throw std::out_of_range("size of linkedlist is 0");
        
        HogwartsStudent student = head->data;
        Node* p = head;
        head = head->next;
        head->prev = nullptr;
        delete p;
        _size--;
        return student;
    }

    inline size_t size() const noexcept { return _size; }
    void print() const
    {
        if (_size == 0)
            return;
        Node* p = head;
        while (p != nullptr)
        {
            p->data.print();
            p = p->next;
        }
    }
    void clear() 
    {
        Node* p = head;
        Node* _assistant_node;
        while (p != nullptr)
        {
            _assistant_node = p;
            p = p->next;
            delete _assistant_node;
        }
        // very important in order to avoid double free()
        head = nullptr; 
        tail = nullptr;
        _size = 0;
    }
    // worst O(n)
    void insert(const HogwartsStudent& student, size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("insert method invoked out of linkedlist range");

        size_t j = 0;
        Node* p = head;
        Node* _assistant_node;
        Node* _newnode = new Node(student);

        while (j++ < i) // seek for the element to move to right
            p = p->next;
            
        _assistant_node = p->prev;
        _assistant_node->next = _newnode;
        p->prev = _newnode;
        _newnode->prev = _assistant_node;
        _newnode->next = p;

        _size++;
    }
    void remove(size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("remove method invoked out of linkedlist range");

        size_t j = 0;
        Node* p = head;
        Node* _assistant_node;
        
        while (j++ < i)
            p = p->next;

        _assistant_node = p->prev;
        _assistant_node->next = p->next;
        
        _assistant_node->prev = p->prev;
        delete p;
        _size--;
    }
    void reverse()
    {
        Node* p = head;
        Node* prev = nullptr;
        Node* curr = nullptr;
        while (p != nullptr)
        {
            curr = p;
            p = p->next;
            curr->next = prev;
            prev = curr;
        }
        head = curr;
    }
    int hasCycle()
    {
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) 
        {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) 
                return 1;
        }     
        return 0;
    }
};