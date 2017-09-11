#include <thread>
#include <condition_variable>
#include <iostream>
#include <deque>
#include <mutex>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void producer() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<std::mutex> uni_locker(mu);
        q.push_front(count);
        cond.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --count;
    }
}

void consumer() {
    int data = 0;
    while (data != 1) {
        std::unique_lock<std::mutex> uni_locker(mu); // 这里需要的是 unique_lock, 因为它需要在 wait 处释放， 激活时再获取
        cond.wait(uni_locker, 
                  []() { // 防止线程自己假激活自己
            return !q.empty();
        });
        data = q.back();
        q.pop_back();
        uni_locker.unlock();
        std::cout << "Consumer get data from programmer" << data << std::endl;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();

    return 0;
}