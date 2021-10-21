#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process
{
public:
  Process();

  // Gets.
  int Pid() const;
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  std::string Ram() const;
  long int UpTime() const;

  // Sets.
  void Pid(const int& value);
  void User(const std::string& value);
  void Command(const std::string& value);
  void CpuUtilization(const float& value);
  void Ram(const std::string& value);
  void UpTime(const long& value);

  bool operator<(Process const &a) const;

private:
  int pid_ {0};
  std::string user_ {std::string()};
  std::string command_ {std::string()};
  float cpu_utilization_ {0.0};
  std::string ram_ {std::string()};
  long uptime_ {0};
};

#endif
