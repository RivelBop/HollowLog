# HollowLog
 Simple C++ Logging Library

# Overview
HollowLog is a lightweight and easy-to-use logging library for C++ applications. It provides a
simple interface for logging messages with different severity levels, making it easier to track
application behavior and debug issues.

# Requirements
* **C++17** (or newer)

# Usage
To use HollowLog in your C++ project, follow these steps:
1. Download the ```HollowLog``` directory in ```include``` from the repository and place it into your source code.
2. ```#include``` the header file in your source code:
   ```cpp
   #include "HollowLog/HollowLog.h"
   ```
3. To log messages, start by setting/specifying the initial log level (ERROR, WARN, INFO = default, DEBUG, TRACE):
   ```cpp
   HollowLog::set(HollowLog::YOUR_LOG_LEVEL);
   ```
   OR (if you want to log SPECIFIC levels, use bitwise OR with ```specify()```)
    ```cpp
    HollowLog::specify(HollowLog::YOUR_LOG_LEVEL | ...);
    ```
4. Use the logging functions to log messages at different severity levels:
    ```cpp
   HollowLog::error("This is an error message.");
   HollowLog::warn("This is a warning message.");
   HollowLog::info("This is an informational message.");
   HollowLog::debug("This is a debug message.");
   HollowLog::trace("This is a trace message.");
   ```
   OR (using formatting)
    ```cpp
   HollowLog::error("%s", "This is an error message.");
   HollowLog::warn("%d", 123);
   HollowLog::info("%f", 3.14);
   HollowLog::debug("%x", 255);
   HollowLog::trace("%s Some Number: %d", "This is a trace message.", 43);
    ```
   OR (using categories)
   ```cpp
   HollowLog::errorCat("Category", "%s", "This is an error message.");
   HollowLog::warnCat("SomeCategory", "This is a warning message.");
   HollowLog::infoCat("IDK", "%f", 3.14);
   HollowLog::debugCat(":0", "This is a debug message.");
   HollowLog::traceCat("XD", "%s Some Number: %d", "This is a trace message.", 43);
   ```
If you want to change the log level at any point in your application, simply call the
```set()``` or ```specify()``` function again with the desired log level(s). 

That's it! You can now log messages in your C++ application using HollowLog!  

# Work in Progress
HollowLog is currently a work in progress. Future updates may include additional features such as: 
- File Logging
- And More?
