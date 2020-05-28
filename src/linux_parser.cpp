#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>


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
  string os, version,kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version>> kernel;
  }
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

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  
  std::map<std::string, long> data_map;
  std::string key,value,unit;
  long total_memory_used = 0;
  
  string line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {

      std::istringstream linestream(line);
      while (linestream >>key>>value>>unit) {
      data_map.insert(std::pair<std::string,long>(key,stol(value, nullptr, 10))); 
      }
    }
  }

  total_memory_used = data_map["MemTotal:"] -  data_map["MemFree:"];
  return (float) total_memory_used/data_map["MemTotal:"]; 
  
  }

// DONE: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime, time_on_ideal_process;
  long return_uptime=0;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> time_on_ideal_process;
  }
  return_uptime = stol(uptime, nullptr, 10);
  return return_uptime;

 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
std::stringstream ss_pid;
  ss_pid<< pid;
  std::string value;
  long utime = 0;
  long stime = 0;
  long cutime = 0;
  long cstime = 0;
  //long starttime = 0;

  string line;
  std::ifstream filestream(kProcDirectory + ss_pid.str()+kStatFilename);
  
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    int i=1;
    while (linestream >>value) 
    {
      if (i==14)
      {
        utime = stol(value, nullptr, 10);  
      }else if (i==15)
      {
        stime = stol(value, nullptr, 10);  
      }else if (i==16)
      {
        cutime = stol(value, nullptr, 10);  
      }else if (i==17)
      {
        cstime = stol(value, nullptr, 10);  
      }

      i++;
    }
 }

 return (utime + stime + cutime + cstime);

 }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuUtilize_values{};
  string key;
  string value1;string value2;string value3;string value4;string value5;string value6;string value7;
  string value8;string value9;string value10;

  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >>key>>value1>>value2>>value3>>value4>>value5>>value6>>value7>>value8>>value9>>value10) {
        if (key == "cpu")
        {
          cpuUtilize_values.push_back(value1);
          cpuUtilize_values.push_back(value2);
          cpuUtilize_values.push_back(value3);
          cpuUtilize_values.push_back(value4);
          cpuUtilize_values.push_back(value5);
          cpuUtilize_values.push_back(value6);
          cpuUtilize_values.push_back(value7);
          cpuUtilize_values.push_back(value8);
          cpuUtilize_values.push_back(value9);
          cpuUtilize_values.push_back(value10);

          return cpuUtilize_values;

        }
      }
    }
  }
  return cpuUtilize_values;

 }

// DONE: Read and return the total number of processes
// TODO:This function can be redefined with one private function that can be used for Process-count and Running-process-count 
int LinuxParser::TotalProcesses() { 

  std::string key; int value;

  int return_total_process=0;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {

      std::istringstream linestream(line);
      while (linestream >>key>>value) {
        if (key == "processes")
        {
          return_total_process = value;
        }
      //TODO(MM): can be optimized
      }
    }
  }

  return return_total_process;

 }

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {   
  
  std::string key; int value;
  
  int return_total_process=0;
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {

      std::istringstream linestream(line);
      while (linestream >>key>>value) {
        if (key == "procs_running")
        {
          return_total_process = value;
        }
      //TODO(MM): can be optimized
      }
    }
  }

  return return_total_process; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 

  std::stringstream ss_pid;
  ss_pid<< pid;

  string command;
  string line;
  std::ifstream filestream(kProcDirectory + ss_pid.str()+kCmdlineFilename);
  
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> command; 
  }

  return command;
  
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 

  std::string memory{""};
  std::string key{""};
  std::stringstream ss_pid;
  ss_pid<< pid;
  string line;
  std::ifstream filestream(kProcDirectory + ss_pid.str()+ kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >>key>>memory) {
        if (key == "VmSize:")
        {
          return memory ;
        }
      
      }
    }
  }

  return memory;

 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 

  std::string uid{""};
  std::string key{""};
  std::stringstream ss_pid;
  ss_pid<< pid;
  string line;
  std::ifstream filestream(kProcDirectory + ss_pid.str()+ kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >>key>>uid) {
        if (key == "Uid:")
        {
          return uid ;
        }
      
      }
    }
  }

  return uid;

 }

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::string user="";
  string line;
  std::string uid = LinuxParser::Uid(pid);
 
  std::ifstream filestream(kPasswordPath);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
     
      std::size_t loc = line.find("x:"+uid+":");
      if (loc!=std::string::npos)
      {
        return line.substr (0,loc-1);
      }
      
      }
    }
    return user;
  }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::stringstream ss_pid;
  ss_pid<< pid;
  std::string value;
  long uptime = 0;
  string line;
  std::ifstream filestream(kProcDirectory + ss_pid.str()+kStatFilename);
  
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    int i=1;
    while (linestream >>value) 
    {
      if (i==22)
      {
        uptime = stol(value, nullptr, 10);
        break;  
      }
      i++;
    }

    //if (pid==3799)
    //std::cout<<uptime<<"Clock"<<sysconf(_SC_CLK_TCK)<<"\n";
 }


 return uptime/sysconf(_SC_CLK_TCK);
}