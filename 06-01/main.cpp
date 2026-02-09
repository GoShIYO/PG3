#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int main()
{
    std::mutex m;
    std::condition_variable cv;
    int turn = 1;

    auto worker = [&](int id)
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [&] { return turn == id; });
            std::cout << "thread " << id << std::endl;
            ++turn;
            lk.unlock();
            cv.notify_all();
        };

    std::thread th1(worker, 1);
    std::thread th2(worker, 2);
    std::thread th3(worker, 3);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}