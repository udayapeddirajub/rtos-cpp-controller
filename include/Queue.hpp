#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

/**
 * @brief A C++ Template Wrapper for RTOS-style Queues.
 * In a real hardware RTOS, this would wrap xQueueSend and xQueueReceive.
 */
template <typename T>
class Queue {
public:
    explicit Queue(size_t maxSize) : maxSize_(maxSize) {}

    // Send data to the queue (Blocks if full)
    void send(const T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        // Wait until there's space
        cvFull_.wait(lock, [this]() { return queue_.size() < maxSize_; });
        
        queue_.push(item);
        
        lock.unlock();
        cvEmpty_.notify_one();
    }

    // Receive data from the queue (Blocks if empty)
    T receive() {
        std::unique_lock<std::mutex> lock(mtx_);
        // Wait until there's data
        cvEmpty_.wait(lock, [this]() { return !queue_.empty(); });
        
        T item = queue_.front();
        queue_.pop();
        
        lock.unlock();
        cvFull_.notify_one();
        return item;
    }

private:
    std::queue<T> queue_;
    size_t maxSize_;
    std::mutex mtx_;
    std::condition_variable cvEmpty_;
    std::condition_variable cvFull_;
};

#endif