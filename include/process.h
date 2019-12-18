#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "processor.h"


/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const &b)     ;  // TODO: See src/process.cpp
  Process(int);

  // TODO: Declare any necessary private members
 private:
  int pid; 
  Processor cpu;
};

#endif