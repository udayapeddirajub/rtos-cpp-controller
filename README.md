rtos-cpp-controller/
├── .github/workflows/  
│   └── ci.yml          # CI/CD Pipeline
├── include/  
│   ├── Task.hpp        # C++ Base class for FreeRTOS tasks
│   └── Queue.hpp       # C++ wrapper for RTOS communication
├── src/  
│   ├── main.cpp        # Kernel entry point
│   └── Task.cpp        # Task implementation
├── CMakeLists.txt      # Build system
└── .gitignore          # Ignore build/ and temporary files





Description: This is a FreeRTOS producer-consumer demo running POSIX simulation on Linux. 

It demonstrates task creation, scheduling, and inter-task communication via 

queues - core RTOS concepts. Producer generates data every 1s, Consumer processes 

it. Uses C++ wrappers over FreeRTOS C API for modern syntax.



Workflow:

1\. Custom Task base class wraps xTaskCreate()

2\. Static taskEntry() bridges C++ object → FreeRTOS C function

3\. Queue<int> template wraps xQueueCreate/Send/Receive

4\. vTaskStartScheduler() never returns - RTOS takes over

5\. Hooks handle edge cases (stack overflow, malloc failure)

6\. CI/CD validates with GitHub Actions + timeout test



Use Cases:

Sensor Task    → sensorQueue.send(reading)    // ADC/I2C data

ProcessingTask → int data = sensorQueue.receive()  // Process data

DisplayTask    → sensorQueue.send(display\_cmd)     // Update LCD



CAN\_Bus\_Task     → sensorQueue.send(can\_message)      // Car CAN data

ADAS\_Task        → data = sensorQueue.receive()       // Process for autonomous driving

Logger\_Task      → logQueue.send(data)                // Log for debugging





