#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "FreeRTOS.h"
#include "queue.h"

template <typename T>
class Queue {
public:
    explicit Queue(UBaseType_t length) {
        handle_ = xQueueCreate(length, sizeof(T));
    }

    bool send(const T& item) {
        return xQueueSend(handle_, &item, portMAX_DELAY) == pdPASS;
    }

    T receive() {
        T item;
        xQueueReceive(handle_, &item, portMAX_DELAY);
        return item;
    }

private:
    QueueHandle_t handle_;
};

#endif