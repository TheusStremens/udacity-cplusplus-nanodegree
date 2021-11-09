#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

Process::Process() {}

Process::Process(const int &pid,
                 const std::string &command,
                 const std::string &user,
                 const std::string &ram,
                 const long &uptime,
                 const float &cpu_utilization)
                 :
                 pid_(pid),
                 command_(command),
                 user_(user),
                 ram_(ram),
                 uptime_(uptime),
                 cpu_utilization_(cpu_utilization) {}

int Process::Pid() const { return pid_; }

float Process::CpuUtilization() const { return cpu_utilization_; }

std::string Process::Command() const { return command_; }

std::string Process::Ram() const { return ram_; }

std::string Process::User() const { return user_; }

long int Process::UpTime() const { return uptime_; }

//----------------------------------------------

void Process::Pid(const int &value) { pid_ = value; }

void Process::User(const std::string &value) { user_ = value; }

void Process::Command(const std::string &value)
{
  if (value.size() > MAX_COMMAND_LENGTH)
  {
    command_ = value.substr(0, MAX_COMMAND_LENGTH);
    command_ += "...";
  }
  else
    command_ = value;
}

void Process::CpuUtilization(const float &value) { cpu_utilization_ = value; }

void Process::Ram(const std::string &value) { ram_ = value; }

void Process::UpTime(const long &value) { uptime_ = value; }

bool Process::operator<(Process const &a) const
{
  return (cpu_utilization_ < a.cpu_utilization_);
}
