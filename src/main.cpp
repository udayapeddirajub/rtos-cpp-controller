#include <iostream>
#include "FreeRTOS.h"
#include "task.h"
#include "Task.hpp"
#include "Queue.hpp"

Queue<int> sensorQueue(5);

class Producer : public Task {
public:
    using Task::Task;
    void run() override {
        int count = 0;
        while (true) {
            std::cout << "[Producer] Sending: " << ++count << std::endl;
            sensorQueue.send(count);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
};

class Consumer : public Task {
public:
    using Task::Task;
    void run() override {
        while (true) {
            int val = sensorQueue.receive();
            std::cout << "\t[Consumer] Received: " << val << std::endl;
        }
    }
};

extern "C" {
    void vApplicationTickHook(void) {}
    void vApplicationIdleHook(void) {}
    void vApplicationMallocFailedHook(void) { std::cout << "Malloc failed!" << std::endl; for (;;); }
    void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName) {
        std::cout << "Stack overflow in " << pcTaskName << std::endl;
        for (;;);
    }
}

int main() {
    std::cout << "Starting RTOS Simulation..." << std::endl;
    Producer p("Producer", 1);
    Consumer c("Consumer", 1);
    p.start();
    c.start();
    vTaskStartScheduler();
    std::cout << "Scheduler failed to start!" << std::endl;
    return 1;
}
