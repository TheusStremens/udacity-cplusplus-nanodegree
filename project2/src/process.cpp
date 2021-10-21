#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process() {}

int Process::Pid() const { return pid_; }

float Process::CpuUtilization() const { return cpu_utilization_; }

string Process::Command() const { return command_; }

string Process::Ram() const { return ram_; }

string Process::User() const { return user_; }

long int Process::UpTime() const { return uptime_; }

//----------------------------------------------

void Process::Pid(const int &value) { pid_ = value; }

void Process::User(const std::string &value) { user_ = value; }

void Process::Command(const std::string &value) { command_ = value; }

void Process::CpuUtilization(const float &value) { cpu_utilization_ = value; }

void Process::Ram(const std::string &value) { ram_ = value; }

void Process::UpTime(const long &value) { uptime_ = value; }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const &a) const {
  return (std::stoi(ram_) > std::stoi(a.Ram()));
}
