#include <iostream>
#include <time.h>
#include <unistd.h>

template<class T = void, class T1 = void>
void test(T t, T1 t1)
{
    (void)t;
}

template<class T, class T1>
void test2(T t, T1 t1)
{
    (void)t;
}

int main()
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    for(int i = 0; i < 99999999; ++i)
        test2(1 , 2);
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    sleep(2);
    start = std::chrono::system_clock::now();
    for(int i = 0; i < 99999999; ++i)
        test(1 , 2);
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    sleep(2);
    start = std::chrono::system_clock::now();
    for(int i = 0; i < 99999999; ++i)
        test(1 , 2);
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
    sleep(2);
    start = std::chrono::system_clock::now();
    for(int i = 0; i < 99999999; ++i)
        test2(1 , 2);
    std::cout << "execution time : " << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start).count() << "ms" << std::endl;
}
