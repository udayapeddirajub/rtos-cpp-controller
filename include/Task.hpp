#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include "FreeRTOS.h"
#include "task.h"
class Task {
public:
    Task(std::string name, UBaseType_t priority) : name_(name), priority_(priority) {}
    virtual ~Task() = default;
    void start() { xTaskCreate(taskEntry, name_.c_str(), configMINIMAL_STACK_SIZE, this, priority_, &handle_); }
    virtual void run() = 0;
protected:
    std::string name_;
    UBaseType_t priority_;
    TaskHandle_t handle_ = nullptr;
private:
    static void taskEntry(void* params) {
        Task* task = static_cast<Task*>(params);
        while (1) {
            task->run();
        }
        vTaskDelete(NULL);
    }
};
#endif
