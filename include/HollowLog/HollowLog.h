#pragma once

#include <chrono>
#include <cstdio>
#include <mutex>
#include <string>

class HollowLog {
public:
    enum Level : unsigned char {
        NONE  = 1,  // 1 << 0
        ERROR = 2,  // 1 << 1
        WARN  = 4,  // 1 << 2
        INFO  = 8,  // 1 << 3
        DEBUG = 16, // 1 << 4
        TRACE = 32  // 1 << 5
    };

    // Static class - Constructor is not needed
    HollowLog() = delete;

    // Static class - Deconstructor is not needed
    ~HollowLog() = delete;

    // ONLY logs the specified levels
    static void specify(unsigned char levels) {
        level = levels;
        updateLevel();
    }

    // Logs levels <= the specified level
    static void set(Level aLevel) {
        level = (aLevel << 1) - 1;
        updateLevel();
    }

    // Logs error messages to the console
    template<typename... T>
    static void error(const std::string &format, T... params) {
    	static const std::string color = "\033[1;31m";
    	static const std::string levelTag = " [ERROR]: ";
        if (errorFlag) {
            log(color, levelTag, format, params...);
        }
    }

    // Logs warning messages to the console
    template<typename... T>
    static void warn(const std::string &format, T... params) {
    	static const std::string color = "\033[1;33m";
    	static const std::string levelTag = " [WARN]: ";
        if (warnFlag) {
            log(color, levelTag, format, params...);
        }
    }

    // Logs info messages to the console
    template<typename... T>
    static void info(const std::string &format, T... params) {
    	static const std::string color = "\033[1;34m";
       	static const std::string levelTag = " [INFO]: ";
        if (infoFlag) {
            log(color, levelTag, format, params...);
        }
    } 

    // Logs debug messages to the console
    template<typename... T>
    static void debug(const std::string &format, T... params) {
    	static const std::string color = "\033[1;32m";
       	static const std::string levelTag = " [DEBUG]: ";
        if (debugFlag) {
            log(color, levelTag, format, params...);
        }
    }

    // Logs trace messages to the console
    template<typename... T>
    static void trace(const std::string &format, T... params) {
    	static const std::string color = "\033[1;37m";
       	static const std::string levelTag = " [TRACE]: ";
        if (traceFlag) {
            log(color, levelTag, format, params...);
        }
    }

private:
    // Keep track of the current level
    inline static unsigned char level = NONE;

    // Cache the flag check for each level
    inline static bool errorFlag = false;
    inline static bool warnFlag  = false;
    inline static bool infoFlag  = false;
    inline static bool debugFlag = false;
    inline static bool traceFlag = false;

    // Updates the status of each level based on the selected level
    static void updateLevel() {
        errorFlag = level & ERROR;
        warnFlag  = level & WARN;
        infoFlag  = level & INFO;
        debugFlag = level & DEBUG;
        traceFlag = level & TRACE;
    }

    // For thread-safety
    inline static std::mutex logMutex;

    // Keeps track of the starting time to get the time of each log event
    inline static auto startTime = std::chrono::high_resolution_clock::now();

    // Logs a message to the console
    template<typename... T>
    static void log(const std::string &color, const std::string &levelTag, const std::string &format, T... params) {
        // Lock the mutex (unlocked when it goes out of scope) for thread-safety
        std::lock_guard<std::mutex> lock(logMutex);

        // Get the elapsed time (since the start of the program)
        auto currTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currTime - startTime;
        auto elapsedNano = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();

        // Hours
        auto elapsedHour = elapsedNano / 3600000000000L;
        elapsedNano -= (elapsedHour * 3600000000000L);

        // Minutes
        auto elapsedMin = elapsedNano / 60000000000L;
        elapsedNano -= (elapsedMin * 60000000000L);

        // Seconds
        auto elapsedSec = elapsedNano / 1000000000L;
        elapsedNano -= (elapsedSec * 1000000000L);

        // Milliseconds
        auto elapsedMilli = elapsedNano / 1000000L;

        // FORMAT -> hours:minutes:seconds:milliseconds [LEVEL]:
        std::string prefix = color;
        prefix.append(std::to_string(elapsedHour)).append(":")
        .append(std::to_string(elapsedMin)).append(":")
        .append(std::to_string(elapsedSec)).append(":")
        .append(std::to_string(elapsedMilli))
        .append(levelTag);

        // Print result
        printf("%s", prefix.c_str());
        printf(format.c_str(), params...);
        printf("\033[0m\n");
    }
};
