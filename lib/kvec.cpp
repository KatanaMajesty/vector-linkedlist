#include <kvec.h>

HogwartsStudent::HogwartsStudent(char faculty, StickType type, unsigned int percentage)
    : faculty(faculty)
    , type(type)
    , empl_percentage(percentage) 
{
    // std::cout << "HogwartsStudent value constructor: " << this << std::endl;
}
// just for debug
HogwartsStudent::HogwartsStudent(const HogwartsStudent& student)
    : faculty(student.faculty)
    , type(student.type)
    , empl_percentage(student.empl_percentage)
{
    // std::cout << "HogwartsStudent copy constructor: " << this << std::endl;
}
HogwartsStudent::~HogwartsStudent()
{
    // std::cout << "HogwartsStudent destructor: " << this << std::endl;
}
void HogwartsStudent::print() const
{
    printf("Faculty: %c, StickType: %d, Employment percentage: %u%\n", 
            faculty,
            type,
            empl_percentage);
}

void Vector::_reallocate(size_t _newcapacity)
{
    HogwartsStudent* new_data = new HogwartsStudent[_newcapacity];
    for (int i = 0; i < _size; i++)
        new_data[i] = _data[i];

    delete[] _data;
    _capacity = _newcapacity;
    _data = new_data;
}
Vector::Vector()
    : _capacity(2)
{
    // std::cout << "default size constructor: " << this << std::endl;
    _data = new HogwartsStudent[_capacity];
}
// non-default size constructor
Vector::Vector(size_t capacity)
    : _capacity(capacity)
{
    // std::cout << "non-default size constructor: " << this << std::endl;
    _data = new HogwartsStudent[_capacity]; 
}
// lvalue ref constructor
Vector::Vector(const Vector& vec)
{
    // std::cout << "lvalue ref constructor: " << this << std::endl;
    _size = vec._size;
    _capacity = vec._capacity;
    _data = new HogwartsStudent[_capacity];

    // copy a block of memory to our new Vector object
    memcpy(_data, vec._data, sizeof(HogwartsStudent) * _size);
}
// rvalue ref constructor
Vector::Vector(Vector&& vec) noexcept
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
Vector::~Vector()
{
    // std::cout << "Vector destructor: " << this << std::endl;
    delete[] _data;
}
// [] operator
const HogwartsStudent& Vector::operator[](size_t i)
{
    if (i >= _size)
        throw std::out_of_range("access to an element out of size boundaries");

    return _data[i];
}
// lvalue push_back
void Vector::push_back(const HogwartsStudent& student)
{
    // std::cout << "lvalue push_back of: " << &student << std::endl;
    if (_size >= _capacity)
        _reallocate(_capacity * 2);

    _data[_size] = HogwartsStudent(student);
    _size++;
}
// returns last element in vector
HogwartsStudent Vector::pop_back()
{
    // std::cout << "copy pop_back of: " << &_data[_size - 1] << std::endl;
    _size--;
    HogwartsStudent p = HogwartsStudent(_data[_size]); 
    _data[_size].~HogwartsStudent();
    return p;
}
const HogwartsStudent& Vector::get(size_t i)
{
    if (i >= _size)
        throw std::out_of_range("access to an element out of size boundaries");
    // std::cout << "Vector::get() returned: " << &_data[i] << std::endl;

    return _data[i];
}
// prints all elements of vector
void Vector::print() const noexcept
{
    for (size_t i = 0; i < _size; i++)
        _data[i].print();
}
// clears all elements of vector
void Vector::clear()
{
    _size = 0;
    _capacity = 2;
    delete[] _data;
}
// pushes elements at the beginning of vector
void Vector::push_front(const HogwartsStudent& student)
{
    // std::cout << "lvalue push_front of: " << &student << std::endl;
    if (_size >= _capacity - 1) // in order to get 1 extra place for new element
        _reallocate(_capacity * 2);

    for (size_t i = _size; i > 0; i--)
        _data[i] = _data[i - 1];

    _data[0] = student;
    _size++;
}
// returns first element in vector
HogwartsStudent Vector::pop_front()
{
    // std::cout << "copy pop_front of: " << &_data[0] << std::endl;
    HogwartsStudent student(_data[0]);

    for (size_t i = 1; i < _size; i++)
        _data[i - 1] = _data[i];

    _data[_size - 1].~HogwartsStudent(); // because there will be a copy at _size - 2
    _size--;
    return student;
}
// worst O(n), average O(_size - i), best O(1)
void Vector::insert(const HogwartsStudent& student, size_t i)
{
    if (i >= _size)
        throw std::out_of_range("insert method invoked out of vector range");

    if (_size >= _capacity - 1) // for 1 extra element
        _reallocate(_capacity * 2);

    for (size_t j = _size; j > i; j--)
        _data[j] = _data[j - 1];

    _data[i] = HogwartsStudent(student);
    _size++;
}
// worst O(n), average O(_size - i), best O(1)
void Vector::remove(size_t i)
{
    if (i >= _size)
        throw std::out_of_range("remove method invoked out of vector range");

    _data[i].~HogwartsStudent();
    for (int j = i + 1; j < _size; j++)
        _data[j - 1] = _data[j];
    
    _data[_size - 1].~HogwartsStudent(); // delete a copy of _data[_size - 2]
    _size--;
}

LinkedList::Node::Node(const HogwartsStudent& student)
    : data(student) {}

LinkedList::LinkedList()
    : _size(0), head(nullptr), tail(nullptr)
{
    // std::cout << "LinkedList value constructor: " << this << std::endl;
}
LinkedList::LinkedList(const LinkedList& list)
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
LinkedList::~LinkedList()
{
    // std::cout << "LinkedList destrutor: " << this << std::endl;
    clear();
}
// add element to the front of linkedlist
void LinkedList::push_front(const HogwartsStudent& student) 
{
    // std::cout << "LinkedList push_front of: " << &student << std::endl;
    Node* node = new Node(student);
    
    if (head != nullptr)
        head->prev = node;

    node->next = head;
    node->prev = nullptr;
    head = node;

    _size++;

    if (_size == 1)
        tail = head;
}
void LinkedList::push_back(const HogwartsStudent& student) 
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
const HogwartsStudent& LinkedList::get(size_t i) const
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
HogwartsStudent LinkedList::pop_back()
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
HogwartsStudent LinkedList::pop_front()
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
void LinkedList::print() const
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
void LinkedList::clear() 
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
void LinkedList::insert(const HogwartsStudent& student, size_t i)
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
void LinkedList::remove(size_t i)
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
void LinkedList::reverse()
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
int LinkedList::hasCycle()
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