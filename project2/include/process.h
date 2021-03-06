#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#define MAX_COMMAND_LENGTH 50

/**
 * @brief Basic class for Process representation It contains relevant attributes as
 * shown below. This class works like a container, who will set its values is the System
 * class through the set methods.
 *
 */
class Process
{
public:
  Process();
  Process(const int &pid,
          const std::string &command,
          const std::string &user,
          const std::string &ram,
          const long &uptime,
          const float &cpu_utilization);

  // Gets.
  int Pid() const;
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  std::string Ram() const;
  long int UpTime() const;

  // Sets.
  void Pid(const int &value);
  void User(const std::string &value);
  void Command(const std::string &value);
  void CpuUtilization(const float &value);
  void Ram(const std::string &value);
  void UpTime(const long &value);

  // Overload the "less than" comparison operator for Process objects.
  bool operator<(Process const &a) const;

private:
  int pid_{0};
  std::string command_{};
  std::string user_{};
  std::string ram_{};
  long uptime_{0};
  float cpu_utilization_{0.0};
};

#endif
