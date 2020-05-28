#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 
    long total_time = LinuxParser::ActiveJiffies(this->pid_);
    long process_uptime_jffer = LinuxParser::UpTime(this->pid_);
    long startTime = LinuxParser::UpTime();
    long hearz = sysconf(_SC_CLK_TCK);
    float process_cpu_use = 0;
    long total_elaspsed_sec = startTime - ( process_uptime_jffer/hearz);
    
    total_time *=100;

    if (total_elaspsed_sec>0)
        process_cpu_use = (float) total_time/(hearz*total_elaspsed_sec);
    return process_cpu_use;
    }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command (this->pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    long used_ram_kb = 0; 
    float used_ram_mb = 0;
    string str_used_ram_kb = LinuxParser::Ram( this->pid_);
    if (str_used_ram_kb!="")
    {
        used_ram_kb = stol(str_used_ram_kb, nullptr, 10); 
    }
    
    used_ram_mb = (float) (used_ram_kb/1024.0);
    
    
    std::stringstream ss_used_ram_mb;
    ss_used_ram_mb<< used_ram_mb;

    return  ss_used_ram_mb.str();
    }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User( this->pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return (this->CpuUtilization()> a.CpuUtilization());
    }