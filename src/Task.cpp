#include "Task.hpp"
#include <iostream>
#include <thread>

void Task::start() {
    std::cout << "[System] Starting Task: " << name_ << std::endl;
    // In a real RTOS: xTaskCreate(taskEntry, name_.c_str(), ...);
    // For this simulation, we use std::thread to mimic the RTOS scheduler
    std::thread simulationThread(taskEntry, this);
    simulationThread.detach();
}

void Task::taskEntry(void* pvParameters) {
    Task* taskInstance = static_cast<Task*>(pvParameters);
    if (taskInstance) {
        taskInstance->run();
    }
}