```markdown
# RTOS C++ Controller - FreeRTOS Producer-Consumer Demo

[![CI](https://github.com/YOUR_USERNAME/rtos-cpp-controller/actions/workflows/ci.yml/badge.svg)](https://github.com/YOUR_USERNAME/rtos-cpp-controller/actions/workflows/ci.yml)

Modern **C++ FreeRTOS** demo using **producer-consumer pattern** with POSIX simulation. Demonstrates task creation, scheduling, and **inter-task communication** via queues.

## 🚀 Features
- ✅ **C++17** wrappers over FreeRTOS C API
- ✅ **Header-only** design (no Task.cpp needed)
- ✅ **Production-grade** CMake + GitHub Actions CI/CD
- ✅ **POSIX port** for Linux testing
- ✅ **Error hooks** for stack overflow, memory failure

## 📁 Clean Project Structure
```
rtos-cpp-controller/
├── .github/workflows/ci.yml     # GitHub Actions CI/CD
├── include/                     
│   ├── FreeRTOSConfig.h         # FreeRTOS configuration
│   ├── Task.hpp                # C++ Task base class (header-only)
│   ├── Queue.hpp               # C++ Queue wrapper (template)
├── src/
│   └── main.cpp                # Producer + Consumer demo
├── CMakeLists.txt              # CMake build system
└── README.md
```

## 🎯 How It Works

```
Producer Task    → sensorQueue.send(count)     [1,2,3...] every 1s
Consumer Task    → sensorQueue.receive()       Prints received data
RTOS Scheduler → Preemptive multitasking
```

**Sample Output:**
```
Starting RTOS Simulation...
[Producer] Sending: 1
	[Consumer] Received: 1
[Producer] Sending: 2
	[Consumer] Received: 2
... (runs forever)
```

## 🛠 Build & Run

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j2
timeout 10s ./rtos_demo    # Should see producer-consumer output
```

## 🔧 Technical Highlights

1. **`Task.hpp`**: `xTaskCreate()` wrapped in C++ class + virtual `run()`
2. **`Queue.hpp`**: Template wrapper for `xQueueCreate/Send/Receive`
3. **Static `taskEntry()`**: Bridges C++ objects ↔ FreeRTOS C API
4. **`vTaskStartScheduler()`**: RTOS kernel takes control (never returns)
5. **Hooks**: Production-grade error handling (stack overflow, malloc fail)

## 🌐 Real-World Use Cases

### **Industrial IoT**
```
SensorTask     → queue.send(sensor_data)     // ADC/I2C readings
ProcessTask    → data = queue.receive()      // Filter/validate
DisplayTask    → queue.send(display_cmd)     // LCD/OLED update
```

### **Automotive (ADAS)**
```
CAN_Task       → queue.send(can_message)     // Vehicle CAN bus
FusionTask     → data = queue.receive()      // Sensor fusion
SafetyTask     → logQueue.send(event)        // Safety logging
```

## 👨‍💻 Interview Talking Points
```
✅ RTOS Concepts: Tasks, Scheduling, IPC via Queues
✅ C++ Modern: Inheritance, Templates, RAII
✅ Production Ready: CMake, CI/CD, Error Handling
✅ Scalable: Add tasks/queues easily
✅ Portable: POSIX for CI, ARM Cortex for hardware
```

## 📊 CI/CD Status
![CI Badge Above] - Green = All tests pass automatically on push/PR

## 🔗 Related Technologies
- **FreeRTOS**: Industry standard RTOS
- **CMake 3.10+**: Cross-platform build system
- **GitHub Actions**: Ubuntu runner with timeout test
- **POSIX**: Linux thread simulation for CI
