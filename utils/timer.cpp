#include "timer.h"

#include <stdexcept>

void Timer::start() {
    if(ticking_){
        throw std::runtime_error("Timer already started.");
    }
    ti = std::chrono::high_resolution_clock::now();
    ticking_ = true;
}

duration Timer::stop(){
    tf = std::chrono::high_resolution_clock::now();

    if(!ticking_){
        throw std::runtime_error("Timer not started.");
    }
    ticking_ = false;
    return std::chrono::duration_cast<duration>(tf - ti);
}

bool Timer::ticking() const noexcept{
    return ticking_;
}
