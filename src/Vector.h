#pragma once

template<class T> class Vector
{
private:
    T* m_Data;
    std::size_t m_Capacity = 0;
    std::size_t m_Size = 0;
private:
    void reallocate(std::size_t capacity)
    {
        m_Capacity = capacity;
        T* new_data = new T[m_Capacity];
        for (int i = 0; i < Size(); i++)
            new_data[i] = std::move(m_Data[i]);

        delete[] m_Data;
        m_Data = new_data;
    }
public:
    Vector()
    : m_Data{nullptr}
    , m_Capacity(4)
    , m_Size(0)
    {
        m_Data = new T[m_Capacity];
    }
    Vector(std::size_t capacity)
    : m_Data{nullptr}
    , m_Capacity(capacity)
    , m_Size(0)
    {
        m_Data = new T[m_Capacity]; 
    }
    ~Vector()
    {
        delete[] m_Data;
    }

    const T& operator[](std::size_t index) {return m_Data[index];}

    void PushBack(const T& student)
    {
        if (Size() >= Capacity())
            reallocate(Capacity() * 2);

        m_Data[Size()] = student;
        ++m_Size;
    }
    void PushBack(T&& student) noexcept
    {
        if (Size() >= Capacity())
            reallocate(Capacity() * 2);

        m_Data[Size()] = std::move(student);
        ++m_Size;
    }
    T PopBack()
    {
        --m_Size;
        T value = m_Data[Size()]; 
        m_Data[Size()].~T();
        return value;
    }
    
    void PushFront(const T& student)
    {
        if (Size() >= Capacity())
            reallocate(m_Capacity * 2);

        for (std::size_t i = Size(); i > 0; i--)
            m_Data[i] = std::move(m_Data[i - 1]);

        m_Data[0] = student;
        ++m_Size;
    }
    void PushFront(T&& student) noexcept
    {
        if (Size() >= Capacity())
            reallocate(Capacity() * 2);

        for (std::size_t i = Size(); i > 0; i--)
            m_Data[i] = std::move(m_Data[i - 1]);

        m_Data[0] = std::move(student);
        ++m_Size;
    }
    T PopFront()
    {
        T value = std::move(m_Data[0]);

        for (std::size_t i = 0; i < Size() - 1; i++)
            m_Data[i] = std::move(m_Data[i + 1]);

        m_Data[Size() - 1].~T();
        --m_Size;
        return value;
    }

    T& Get(std::size_t index)
    {
        if (!(index < Size()))
            throw std::out_of_range("Vector::Get() out of range");

        return m_Data[index];
    }
    const T& Get(std::size_t index) const
    {
        if (!(index < Size()))
            throw std::out_of_range("const Vector::Get() const out of range");

        return m_Data[index];
    }
    
    constexpr std::size_t Size() const {return m_Size;}
    constexpr std::size_t Capacity() const {return m_Capacity;}
    void Print() const noexcept
    {
        for (std::size_t i = 0; i < Size(); i++)
            m_Data[i].Print();
    }
    void Clear()
    {
        for (std::size_t i = 0; i < Size(); i++)
        m_Data[i].~T();

        delete[] m_Data;
        m_Data = nullptr;
    }

    void Insert(const T& student, std::size_t index)
    {
        if (!(index < Size()))
            throw std::out_of_range("Vector::Insert() out of range");

        if (Size() >= Capacity())
            reallocate(Capacity() * 2);

        for (std::size_t i = Size(); i > index; i--)
            m_Data[i] = std::move(m_Data[i - 1]);

        m_Data[index] = std::move(student);
        ++m_Size;
    }
    void Remove(std::size_t index)
    {
        if (!(index < Size()))
            throw std::out_of_range("Vector::Remove() out of range");

        m_Data[index].~T();
        for (std::size_t i = index; i < Size() - 1; i++)
            m_Data[i] = std::move(m_Data[i + 1]);
        
        m_Data[Size() - 1].~T();
        m_Size--;
    }
};