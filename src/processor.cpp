#include "processor.h"
#include "linux_parser.h"
#include "assert.h"
// TODO: Return the aggregate CPU utilization

float Processor::Utilization() { 

  long total=0;
  long idle = 0;
  long Nonidle = 0;

  long total_delta = 0;
  long idle_delta = 0;

  auto parsed_values = LinuxParser::CpuUtilization();
  assert(parsed_values.size() == 10);

  //idle = idle_ + iowait_; 
   idle =  stol(parsed_values.at(3), nullptr, 10) + 
         stol(parsed_values.at(4), nullptr, 10);

   Nonidle =  stol(parsed_values.at(0), nullptr, 10)+ 
         stol(parsed_values.at(1), nullptr, 10)+
         stol(parsed_values.at(2), nullptr, 10)+
         stol(parsed_values.at(5), nullptr, 10)+
         stol(parsed_values.at(6), nullptr, 10)+
         stol(parsed_values.at(7), nullptr, 10);

   total =  idle + Nonidle;

   total_delta = total - this->previousTotal_;
   idle_delta  = idle - this->PreviousIdle_;
   this->previousTotal_ = total;
   this->PreviousIdle_ = idle;



   return (float) (total_delta - idle_delta)/total_delta;



 }