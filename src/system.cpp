#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <algorithm>    // std::reverse


#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

#include "linux_parser.h"


// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    string os =  LinuxParser::OperatingSystem();
    return os; 
    }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    string kernel = LinuxParser::Kernel();
    return kernel;
    }

// TODO: Return the system's CPU 
Processor& System::Cpu() {  
    return cpu_; 
    }


// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float utilization;

    float totalMemoryUsage = 0;

    vector<int> idVec = LinuxParser::Pids() ;
    for (int pid : idVec){
        Process pro(pid);
        int memory_usage = std::stoi(LinuxParser::Ram(pid));
        if (memory_usage >0){
            totalMemoryUsage += memory_usage ;
        }
    } 


    string cmd = "n.a."; 
    string line, key, value;
    string path =  LinuxParser::kProcDirectory + "/meminfo";

    float memoryMax = 1;
    std::ifstream filestream(path);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "MemTotal") {
                    memoryMax = std::stoi(value)/1024;
                }
            }
        }
    }


    utilization = totalMemoryUsage / memoryMax; 

    return utilization; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    
    int runprocess = LinuxParser::RunningProcesses();
    return runprocess;
    }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    
    int ttlprocess = LinuxParser::TotalProcesses();
    return ttlprocess;
    }

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
    long uptime = LinuxParser::UpTime();
    return uptime; 
    }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    vector<int> idVec = LinuxParser::Pids() ;

    for (int pid : idVec){
        Process pro(pid);
        int memory_usage = std::stoi(LinuxParser::Ram(pid));
        if (memory_usage >0){
            processes_.push_back(pro);
        }
    } 

    std::sort(processes_.begin(), processes_.end());
    std::reverse(processes_.begin(), processes_.end());

    

    return processes_; }
