#ifndef TASK_HPP
#define TASK_HPP

#include <string>

// Simulating FreeRTOS types for the POSIX demo environment
typedef void* TaskHandle_t;

class Task {
public:
    Task(std::string name, int priority)
        : name_(name), priority_(priority) {
    }

    virtual ~Task() = default;

    // Logic to start the task
    void start();

    // The actual logic implemented by derived classes
    virtual void run() = 0;

protected:
    std::string name_;
    int priority_;
    TaskHandle_t handle_;

    // Static bridge between C-style RTOS and C++ Object
    static void taskEntry(void* pvParameters);
};

#endif