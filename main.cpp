#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;
int i = 0;
int max = 100;

void printEven() {
    while (i < max) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [](){ return (!(i % 2)); });
        std::cout << i << std::endl;
        i++;
        lock.unlock();
        cv.notify_all();
    }
}

void printOdd() {
    while (i < max) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [](){ return ((i % 2)); });
        std::cout << i << std::endl;
        i++;
        lock.unlock();
        cv.notify_all();
    }
}

int main()
{
    std::thread tEven(printEven);
    std::thread tOdd(printOdd);
    tEven.join();
    tOdd.join();
    return 0;
}
