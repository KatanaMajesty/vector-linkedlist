#include <kvec.h>
#include <iostream>
#include <time.h>
#include <random>

int main(void)
{
    clock_t begin;
    clock_t end;

    Vector vec;
    LinkedList list;

    {
        std::cout << "\nVector tests:" << std::endl;
        double summary = 0;
        double time;
        // 5.1 vector
        begin = clock();
        for (int i = 0; i < 50000; i++)
            vec.push_back({static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i});
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.001 second
        std::cout << "Vector 5.1 time: " << time << std::endl; 

        // 5.2 vector
        begin = clock();
        for (int i = 0; i < 10000; i++)
            vec.push_front({static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i});
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 1.14 second
        std::cout << "Vector 5.2 time: " << time << std::endl; 

        // 5.3 vector
        begin = clock();
        for (int i = 0; i < 20000; i++)
            vec.get(rand() % 60000);
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.00017 seconds
        std::cout << "Vector 5.3 time: " << time << std::endl; 

        // 5.4 vector
        begin = clock();
        for (int i = 0; i < 5000; i++)
            vec.pop_front();
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.62 seconds
        std::cout << "Vector 5.4 time: " << time << std::endl; 

        // 5.5 vector
        begin = clock();
        for (int i = 0; i < 5000; i++)
            vec.pop_back();
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.00002 seconds
        std::cout << "Vector 5.5 time: " << time << std::endl; 
        std::cout << "Vector summary: " << summary << std::endl;
    }

    {
        std::cout << "\nLinked List tests:" << std::endl;
        double summary = 0;
        double time;
        // 5.1 list
        begin = clock();
        for (int i = 0; i < 50000; i++)
            list.push_back({static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i});
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.0002 second
        std::cout << "Linked List 5.1 time: " << time << std::endl;

        // 5.2 list
        begin = clock();
        for (int i = 0; i < 10000; i++)
            list.push_front({static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i});
        end = clock();
        // ~ 0.0003 second
        std::cout << "Linked List 5.2 time: " << time << std::endl;

        // 5.3 list
        begin = clock();
        for (int i = 0; i < 20000; i++)
            list.get(rand() % 60000);
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.97 second
        std::cout << "Linked List 5.3 time: " << time << std::endl;

        // 5.4 list
        begin = clock();
        for (int i = 0; i < 5000; i++)
            list.pop_front();
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.00008 second
        std::cout << "Linked List 5.4 time: " << time << std::endl;

        // 5.5 list
        begin = clock();
        for (int i = 0; i < 5000; i++)
            list.pop_back();
        end = clock();
        time = double(end - begin) / CLOCKS_PER_SEC;
        summary += time;
        // ~ 0.00008 second
        std::cout << "Linked List 5.5 time: " << time << std::endl; 
        std::cout << "Linked List summary: " << summary << std::endl;
    }

    // {
    //     std::vector<HogwartsStudent> vec;
    //     std::cout << "\nstd::vector tests:" << std::endl;
    //     double summary = 0;
    //     double time;
    //     // 5.1 std::vec
    //     begin = clock();
    //     for (int i = 0; i < 50000; i++)
    //         vec.push_back({static_cast<char>(i + 65), StickType(i % 4), (unsigned int) i});
    //     end = clock();
    //     time = double(end - begin) / CLOCKS_PER_SEC;
    //     summary += time;
    //     // ~ 0.0002 second
    //     std::cout << "std::vector 5.1 time: " << time << std::endl;

    //     // 5.5 std::vec
    //     begin = clock();
    //     for (int i = 0; i < 5000; i++)
    //         vec.pop_back();
    //     end = clock();
    //     time = double(end - begin) / CLOCKS_PER_SEC;
    //     summary += time;
    //     // ~ 0.00008 second
    //     std::cout << "std::vector 5.5 time: " << time << std::endl; 
    //     std::cout << "std::vector summary: " << summary << std::endl;
    // }
}