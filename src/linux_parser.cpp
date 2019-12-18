#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, kernel2;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> kernel2;
  }
  kernel = kernel + " " + kernel2; 
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  
  
  string uptime, line; 
  
  string path =  kProcDirectory + "/uptime";
  std::ifstream filestream(path);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> uptime;
    }
  }
  
  return std::stol(uptime); 

}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {"0.2"}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  vector<int> idVec = LinuxParser::Pids() ;
  int numProcess = idVec.size();

  return numProcess; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    
  vector<int> idVec = LinuxParser::Pids() ;
  vector<int> idVec_running; 

  for (int pid: idVec){
     int memory_usage = std::stoi(LinuxParser::Ram(pid));
     if (memory_usage >0){
       idVec_running.push_back(pid);
     }
  }

  int numProcess_running = idVec_running.size();

  return numProcess_running; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  
  string cmd = "n.a."; 
  string line;

  string path =  kProcDirectory + "/" + std::to_string(pid) + "/cmdline";
  std::ifstream filestream(path);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> cmd;
    }
  }
  return cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
  string line;
  string key;
  string value = std::to_string(0);
  string path =  kProcDirectory + "/" + std::to_string(pid) + "/status";

  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmRSS") {
          //std::cout<< " match!" << std::to_string(pid) << " \n";
          return std::to_string(std::stoi(value)/1024);
        }
      }
    }
  }
  return std::to_string(0);
  
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  
  string line;
  string key;
  string value;
  string path =  kProcDirectory + "/" + std::to_string(pid) + "/status";

  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
  string uid = LinuxParser::Uid(pid); 
  string uname = "USER";

  string line;
  string username, x, id;
 
  string path =  "/etc/passwd";

  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >>  x >> id) {
        if (id == uid) {
          uname = username;
        }
      }
    }
  }
  return uname;
}


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) { 
  
  //std::cout <<"pid:" << pid << "\n"; 
  string line;
  string v;
  string path =  kProcDirectory + "/" + std::to_string(pid) + "/stat";

  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v >> v;
      //std::cout << "value:" << v <<"\n"; 
      if (std::all_of(v.begin(), v.end(), isdigit)) {
        return std::stol(v)/sysconf(_SC_CLK_TCK);
        
      }
    }
  }
  return 0;
  
}