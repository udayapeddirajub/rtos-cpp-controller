#include <iostream>
#include "FreeRTOS.h"
#include "task.h"
#include "Task.hpp"
#include "Queue.hpp"

// Global Queue for communication
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

// --- RTOS REQUIRED HOOKS ---
extern "C" {
    void vApplicationTickHook(void) {}
    void vApplicationIdleHook(void) {}
    void vApplicationMallocFailedHook(void) { for (;;); }
    void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName) { (void)pcTaskName; (void)xTask; for (;;); }
}

int main() {
    std::cout << "Starting RTOS Simulation..." << std::endl;

    static Producer p("Producer", 1);
    static Consumer c("Consumer", 1);

    p.start();
    c.start();

    vTaskStartScheduler();
    return 0;
}