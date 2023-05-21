#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int BUFFER_SIZE = 10;

queue<int> buffer;
mutex mtx;
condition_variable produce_cv, consume_cv;

void producer(int id) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        unique_lock<mutex> lck(mtx);
        while (buffer.size() == BUFFER_SIZE) {
            cout << "Buffer is full. Producer " << id << " is waiting.\n";
            produce_cv.wait(lck);
        }
        buffer.push(i);
        cout << "Producer " << id << " produced " << i << ".\n";
        lck.unlock();
        consume_cv.notify_one();
    }
}

void consumer(int id) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        unique_lock<mutex> lck(mtx);
        while (buffer.empty()) {
            cout << "Buffer is empty. Consumer " << id << " is waiting.\n";
            consume_cv.wait(lck);
        }
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed " << item << ".\n";
        lck.unlock();
        produce_cv.notify_one();
    }
}

int main() {
    thread t1(producer, 1);
    thread t2(consumer, 1);
    thread t3(consumer, 2);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
