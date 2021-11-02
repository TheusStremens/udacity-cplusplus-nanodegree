#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System()
{
  // Those fields wont't change so, we can retrieve them in the constructor.
  operating_system_ = LinuxParser::OperatingSystem();
  kernel_ = LinuxParser::Kernel();
}

Processor &System::Cpu() { return cpu_; }

vector<Process> &System::Processes()
{
  processes_.clear();
  auto pids = LinuxParser::Pids();
  for (auto pid : pids)
  {
    // Create a process and fill its fields using the linux parser with the
    // corresponding pid.
    Process new_process;
    new_process.Pid(pid);
    new_process.Command(LinuxParser::Command(pid));
    new_process.User(LinuxParser::User(pid));
    new_process.Ram(LinuxParser::Ram(pid));
    new_process.UpTime(LinuxParser::UpTime(pid));
    new_process.CpuUtilization(LinuxParser::CpuUtilization(pid, UpTime()));
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

int System::RunningProcesses()
{
  return LinuxParser::RunningProcesses();
}

int System::TotalProcesses()
{
  return LinuxParser::TotalProcesses();
}

long System::UpTime()
{
  return LinuxParser::UpTime();
}
