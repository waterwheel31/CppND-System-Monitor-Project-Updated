#include <string>

#include "format.h"



using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    int hour, minute, second; 
    hour = seconds / 3600;
    minute = (seconds - hour * 3600) / 60;
    second = seconds - hour * 3600 - minute * 60; 

    //string ret;
    //sprintf(ret, "%04d - %02d - %02d", std::to_string(hour), std::to_string(minute), std::to_string(second));

    string ret = std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second); 
    return ret; 

}