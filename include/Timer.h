#ifndef INCLUDE_TIMER_H
#define INCLUDE_TIMER_H

#include <chrono>

/**
 * Class to handle time differentials
 * Construct the timer object with no parameters which will automatically reset the data
 * calling any of the functions nanoseconds(), microseconds(), milliseconds(), seconds() will return the time passed since the last call of reset
 * calling reset clears the data in the timer 
 * @author Bryce Young 2017
 * */
class Timer{
    public:
        Timer(){
            reset();
        }

        ~Timer(){}

        inline void reset(){
            this->prevTP = std::chrono::high_resolution_clock::now();
        }

        inline long nanoseconds(){
            auto now = std::chrono::high_resolution_clock::now();
            return (long)std::chrono::duration_cast<std::chrono::nanoseconds>(now - prevTP).count();
        }

        inline long microseconds(){
            auto now = std::chrono::high_resolution_clock::now();
            return (long)std::chrono::duration_cast<std::chrono::microseconds>(now - prevTP).count();
        }

        inline long milliseconds(){
            auto now = std::chrono::high_resolution_clock::now();
            return (long)std::chrono::duration_cast<std::chrono::milliseconds>(now - prevTP).count();
        }

        inline long seconds(){
            auto now = std::chrono::high_resolution_clock::now();
            return (long)std::chrono::duration_cast<std::chrono::seconds>(now - prevTP).count();
        }

    private:
        std::chrono::high_resolution_clock::time_point prevTP;
};

#endif