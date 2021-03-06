#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"


System::System()
{
  // Those fields wont't change so, we can retrieve them in the constructor.
  operating_system_ = LinuxParser::OperatingSystem();
  kernel_ = LinuxParser::Kernel();
  uint num_cpus = numberOfCPUs();
  // Add an extra for aggregated CPU information.
  cpus_.push_back(Processor(-1));
  for (uint i = 0; i < num_cpus; i++)
    cpus_.push_back(Processor(i));
}

Processor &System::Cpu() { return cpus_[0]; }

Processor &System::Cpu(uint cpu_number) { return cpus_[cpu_number+1]; }

std::vector<Process> &System::Processes()
{
  processes_.clear();
  auto pids = LinuxParser::Pids();
  for (auto pid : pids)
  {
    // Create a process and fill its fields using the linux parser with the
    // corresponding pid.
    std::string command = LinuxParser::Command(pid);
    std::string user = LinuxParser::User(pid);
    std::string ram = LinuxParser::Ram(pid);
    long uptime = LinuxParser::UpTime(pid);
    float cpu_utilization = LinuxParser::CpuUtilization(pid, UpTime());
    Process new_process(pid, command, user, ram, uptime, cpu_utilization);
    processes_.push_back(new_process);
  }
  // Sort the process by cpu utilization.
  std::sort(processes_.begin(), processes_.end());
  // Reverse the order because we want the ones with highest cpu utilization
  std::reverse(processes_.begin(), processes_.end());
  return processes_;
}

std::string System::Kernel() { return kernel_; }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return operating_system_; }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long System::UpTime() { return LinuxParser::UpTime(); }

uint System::numberOfCPUs() { return LinuxParser::numberOfCPUs(); }
