#include <string>
#include <sstream>
#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    long hour,minutes,sec;
    std::ostringstream str_stream_formated{""};

    minutes = seconds/60;
    sec = seconds % 60;
    hour = minutes/60;
    minutes = minutes % 60;

    
    str_stream_formated << hour << ":"<<minutes<<":"<<sec;

    return str_stream_formated.str(); 
    
    }