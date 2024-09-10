#include <iostream>
#include <future>
#include <chrono>
#include <mutex>

int main()
{
    srand(time(0));
    size_t n1, n2, n3;
    std::cout << "Input fibonacci number: ";
    std::cin >> n1;
    std::cout << "Input natural number: ";
    std::cin >> n2;
    std::cout << "Input rand number: ";
    std::cin >> n3;
    std::mutex cout_mutex;
    auto first_future = std::async(std::launch::async, [&]() {
        cout_mutex.lock();
        size_t first = 0, second = 1;
        for (size_t i = 0; i < n1; ++i) {
            int temp = second;
            second = first + second;
            first = temp;
            std::cout << "first_thread: ";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << first << std::endl;
        }
        cout_mutex.unlock();
        });
    auto second_future = std::async(std::launch::async, [&]() {
        cout_mutex.lock();
        for (size_t i = 1; i < n2 + 1; ++i) {
            std::cout << "second_thread: ";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << i << std::endl;
        }
        cout_mutex.unlock();
        });
    auto third_future = std::async(std::launch::async, [&]() {
        cout_mutex.lock();
        for (size_t i = 0; i < n3; ++i) {
            std::cout << "third_thread: ";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout << rand() % 50 << std::endl;
        }
        cout_mutex.unlock();
        });
    first_future.get();
    second_future.get();
    third_future.get();
    std::cout << "Threads have ended" << std::endl;

    return 0;
}
