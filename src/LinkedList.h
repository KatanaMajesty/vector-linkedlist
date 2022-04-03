#pragma once

#include <cstddef>

template<class T> class LinkedList
{
private:
    struct Node
    {
        T value;
        Node* next;
    };
private:
    std::size_t m_Size;
    Node* m_Head;
    Node* m_Tail;
public:
    LinkedList()
    : m_Size(0)
    , m_Head{nullptr}
    , m_Tail{nullptr}
    {
    }
    ~LinkedList()
    {
        Clear();
    }

    void PushFront(const T& student)
    {
        Node* node = new Node {student, m_Head};
        m_Head = node;

        ++m_Size;

        if (Size() == 1)
            m_Tail = m_Head;
    }
    void PushFront(T&& student) noexcept
    {
        Node* node = new Node {std::move(student), m_Head};
        m_Head = node;

        ++m_Size;

        if (Size() == 1)
            m_Tail = m_Head;
    }
    T PopFront()
    {
        if (Size() == 0)
            throw std::out_of_range("LinkedList::PopFront() out of range");

        Node* ptr = m_Head;
        T value = std::move(ptr->value);
        m_Head = m_Head->next;
        delete ptr;
        --m_Size;
        return value;
    }

    void PushBack(const T& student)
    {
        Node* node = new Node {student, nullptr};

        if (m_Tail != nullptr)
            m_Tail->next = node;

        m_Tail = node;
        
        ++m_Size;

        if (Size() == 1)
            m_Head = m_Tail;
    }
    void PushBack(T&& student) noexcept
    {
        Node* node = new Node {std::move(student), nullptr};

        if (m_Tail != nullptr)
            m_Tail->next = node;

        m_Tail = node;
        
        ++m_Size;

        if (Size() == 1)
            m_Head = m_Tail;
    }

    T PopBack()
    {
        if (Size() == 0)
            throw std::out_of_range("LinkedList::PopBack() out of range");

        Node* ptr = m_Head;
        T value = std::move(m_Tail->value);
        
        while (ptr->next && ptr->next->next)
            ptr = ptr->next;

        ptr->next = nullptr;
        delete m_Tail;
        m_Tail = ptr;
        --m_Size;
        return value;
    }

    T& Get(std::size_t index)
    {
        if (Size() == 0)
            throw std::out_of_range("LinkedList::Get() out of range"); 

        Node* ptr = m_Head;
        
        for (std::size_t i = 0; ptr; i++)
        {
            if (i == index)
                break;

            ptr = ptr->next;
        }
        return ptr->value;
    }
    const T& Get(std::size_t index) const
    {
        if (Size() == 0)
            throw std::out_of_range("const LinkedList::Get() const out of range"); 

        Node* ptr = m_Head;
        
        for (std::size_t i = 0; ptr; i++)
        {
            if (i == index)
                break;

            ptr = ptr->next;
        }
        return ptr->value;
    }

    inline std::size_t Size() const noexcept { return m_Size; }
    void Print() const
    {
        Node* ptr = m_Head;
        while (ptr)
        {
            ptr->value.Print();
            ptr = ptr->next;
        }
    }
    void Clear()
    {
        Node* prev = nullptr;
        while (m_Head)
        {
            prev = m_Head;
            m_Head = m_Head->next;
            delete prev;
        }

        m_Head = nullptr; 
        m_Tail = nullptr;
        m_Size = 0;
    }

    void Insert(const T& student, std::size_t index)
    {
        if (!(index < Size()))
            index = Size();

        Node* right = m_Head;
        Node* left = nullptr;
        Node* node = new Node {student};

        for (std::size_t i = 0; i <= index; i++)
        {
            left = right;
            right = right->next;
        }
            
        node->next = right;
        if (left)
            left->next = node;
        else m_Head = node;

        if (!node->next)
            m_Tail = node;

        ++m_Size;
    }
    void Insert(T&& student, std::size_t index)
    {
        if (!(index < Size()))
            index = Size();

        Node* right = m_Head;
        Node* left = nullptr;
        Node* node = new Node {std::move(student)};

        for (std::size_t i = 0; i < index; i++)
        {
            left = right;
            right = right->next;
        }
            
        node->next = right;
        if (left)
            left->next = node;
        else m_Head = node;

        if (!node->next)
            m_Tail = node;

        ++m_Size;
    }

    void Remove(std::size_t index)
    {
        if (!(index < Size()))
            throw std::out_of_range("remove method invoked out of linkedlist range");

        Node* target = m_Head;
        Node* prev = nullptr;
        
        for (std::size_t i = 0; i < index; i++)
        {
            prev = target;
            target = target->next;
        }

        if (prev)
            prev->next = target->next;
        else m_Head = target->next;

        if (m_Tail == target)
            m_Tail = prev;

        delete target;
        
        --m_Size;
    }
    void Reverse()
    {
        Node* ptr = m_Head;
        Node* prev = nullptr;
        Node* curr = nullptr;
        while (ptr)
        {
            curr = ptr;
            ptr = ptr->next;
            curr->next = prev;
            prev = curr;
        }
        m_Head = curr;
    }

    bool HasCycle()
    {
        Node* slow = m_Head;
        Node* fast = m_Head;
        while (fast != nullptr && fast->next != nullptr) 
        {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) 
                return true;
        }     
        return false;
    }
};