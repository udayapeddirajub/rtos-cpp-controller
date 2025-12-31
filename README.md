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