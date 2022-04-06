#include <iostream>
#include <time.h>
#include <random>
#include <chrono>

#include <Vector.h>
#include <LinkedList.h>

enum StickType {COMMON, UNUSUAL, RARE, LEGENDARY};

struct HogwartsStudent
{
    char faculty;
    StickType type;
    unsigned int employmentPercentage;

    void Print() const
    {
        printf("Faculty: %c, StickType: %d, Employment percentage: %u%\n", 
            faculty,
            type,
            employmentPercentage);
    }
};

struct Timer
{
    std::chrono::steady_clock::time_point m_Start;
    std::string tag;

    Timer(const char* tag)
    : tag(std::move(tag))
    {
        m_Start = std::chrono::steady_clock::now();
    }

    float Reset()
    {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<float> time = end - m_Start;
        m_Start = end;
        return time.count();
    }
};

void get_vector_time(Vector<HogwartsStudent>& vec, int rands[20000])
{
    std::cout << "\nVector tests:" << std::endl;
    
    Timer timer("Vector");
    float summary = 0;
    float time = 0;

    // 5.1 vector
    for (int i = 0; i < 50000; i++)
        vec.PushBack({static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i});
    time = timer.Reset();
    summary += time;
    // ~ 0.001 second
    std::cout << "Vector 5.1 time: " << time << std::endl; 

    // 5.2 vector
    timer.Reset();
    for (int i = 0; i < 10000; i++)
        vec.PushFront(
            {static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i}
        );
    time = timer.Reset();
    summary += time;
    // ~ 1.14 second
    std::cout << "Vector 5.2 time: " << time << std::endl; 

    // 5.3 vector
    timer.Reset();
    for (int i = 0; i < 20000; i++)
        vec.Get(rands[i]);
    time = timer.Reset();
    summary += time;
    // ~ 0.00017 seconds
    std::cout << "Vector 5.3 time: " << time << std::endl; 

    // 5.4 vector
    timer.Reset();
    for (int i = 0; i < 5000; i++)
        vec.PopFront();
    time = timer.Reset();
    summary += time;
    // ~ 0.62 seconds
    std::cout << "Vector 5.4 time: " << time << std::endl; 

    // 5.5 vector
    timer.Reset();
    for (int i = 0; i < 5000; i++)
        vec.PopBack();
    time = timer.Reset();
    summary += time;
    // ~ 0.00002 seconds
    std::cout << "Vector 5.5 time: " << time << std::endl; 
    std::cout << "Vector summary: " << summary << std::endl;
}

void get_list_time(LinkedList<HogwartsStudent>& list, int rands[20000])
{
    std::cout << "\nLinked List tests:" << std::endl;
    float summary;
    float time;
    Timer timer("Linked list");

     // 5.1 list
    for (int i = 0; i < 50000; i++)
        list.PushBack(
            {static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i}
        );
    time = timer.Reset();
    summary += time;
    // ~ 0.0002 second
    std::cout << "Linked List 5.1 time: " << time << std::endl;

    // 5.2 list
    timer.Reset();
    for (int i = 0; i < 10000; i++)
        list.PushFront(
            {static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i}
        );
    time = timer.Reset();
    summary += time;
    // ~ 0.0003 second
    std::cout << "Linked List 5.2 time: " << time << std::endl;

    // 5.3 list
    timer.Reset();
    for (int i = 0; i < 20000; i++)
        list.Get(rands[i]);
    time = timer.Reset();
    summary += time;
    // ~ 0.97 second
    std::cout << "Linked List 5.3 time: " << time << std::endl;

    // 5.4 list
    timer.Reset();
    for (int i = 0; i < 5000; i++)
        list.PopFront();
    time = timer.Reset();
    summary += time;
    // ~ 0.00008 second
    std::cout << "Linked List 5.4 time: " << time << std::endl;

    // 5.5 list
    timer.Reset();
    for (int i = 0; i < 5000; i++)
        list.PopBack();
    time = timer.Reset();
    summary += time;
    // ~ 0.00008 second
    std::cout << "Linked List 5.5 time: " << time << std::endl; 
    std::cout << "Linked List summary: " << summary << std::endl;
}

int main(void)
{
    LinkedList<HogwartsStudent> list;
    Vector<HogwartsStudent> vec;

    int rands[20000];
    for (int i = 0; i < 20000; i++)
        rands[i] = rand() % 32768;

    get_vector_time(vec, rands);
    get_list_time(list, rands);

    LinkedList<HogwartsStudent> l;
    for (int i = 0; i < 5; i++)
        l.PushFront(
            std::move(HogwartsStudent{static_cast<char>(i + 65), RARE, (unsigned int)rand() % 100})
        );
    std::cout << "\nBefore reverse" << std::endl;
    l.Print();
    std::cout << "\nAfter reverse" << std::endl;
    l.Reverse();
    l.Print();
    std::cout << "\nHas cycle?: " << l.HasCycle() << std::endl;
}