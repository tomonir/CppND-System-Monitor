#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor():previousTotal_(0),PreviousIdle_(0){

  } 
  float Utilization();  // TODO: See src/processor.cpp

  
 private:
    long  previousTotal_;
    float PreviousIdle_;
};

#endif