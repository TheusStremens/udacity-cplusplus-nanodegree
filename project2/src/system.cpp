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

System::System() {
  operating_system_ = LinuxParser::OperatingSystem();
  kernel_ = LinuxParser::Kernel();
}

Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  auto pids = LinuxParser::Pids();
  for (auto pid : pids) {
    Process new_process;
    new_process.Pid(pid);
    new_process.Command(LinuxParser::Command(pid));
    new_process.User(LinuxParser::User(pid));
    new_process.Ram(LinuxParser::Ram(pid));
    new_process.UpTime(LinuxParser::UpTime(pid));
    processes_.push_back(new_process);
  }
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

std::string System::Kernel() { return kernel_; }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return operating_system_; }

int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

long System::UpTime() {
  return LinuxParser::UpTime();
}
