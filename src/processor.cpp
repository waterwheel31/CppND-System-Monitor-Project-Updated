#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>



#include "processor.h"
#include "linux_parser.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {  

    float utilization = 0.0;

    std::string line;
    std::string key;
    std::string val1, val2;
    float uptime, idletime;
    std::string path =  LinuxParser::kProcDirectory + "/uptime";

    std::ifstream filestream(path);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> val1 >> val2) {
                uptime = std::stof(val1);
                idletime = std::stof(val2);
            }
        }
    }
    
   
    utilization = (uptime - idletime) / uptime; 
    // std::cout <<"uptime: " <<uptime <<  " idletime: " << idletime << " utilization:" <<utilization << "\n";
    
    return utilization; 

}