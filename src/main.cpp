#include <iostream>
#include "Task.hpp"
#include "Queue.hpp"

// Define a shared queue for integers (e.g., sensor readings)
Queue<int> sensorQueue(10);

class ProducerTask : public Task {
public:
    using Task::Task;
    void run() override {
        int count = 0;
        while (true) {
            std::cout << "[" << name_ << "] Sending Data: " << ++count << std::endl;
            sensorQueue.send(count);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
};

class ConsumerTask : public Task {
public:
    using Task::Task;
    void run() override {
        while (true) {
            int data = sensorQueue.receive();
            std::cout << "\t[" << name_ << "] Processed Data: " << data << std::endl;
        }
    }
};

int main() {
    ProducerTask p("Producer", 1);
    ConsumerTask c("Consumer", 1);

    p.start();
    c.start();

    // Keep main alive
    while (true) { std::this_thread::sleep_for(std::chrono::seconds(1)); }
    return 0;
}