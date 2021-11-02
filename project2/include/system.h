#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System
{
public:
  /**
   * @brief Constructor that will initialize information that don't change at runtime.
   *
   */
  System();

  /**
   * @brief Return the system's CPU.
   *
   * @return Processor&
   */
  Processor &Cpu();

  /**
   * @brief Return a container composed of the system's processes.
   *
   * @return std::vector<Process>&
   */
  std::vector<Process> &Processes();

  /**
   * @brief Return the system's memory utilization.
   *
   * @return float
   */
  float MemoryUtilization();

  /**
   * @brief Return the number of seconds since the system started running.
   *
   * @return long
   */
  long UpTime();

  /**
   * @brief Return the total number of processes on the system.
   *
   * @return int
   */
  int TotalProcesses();

  /**
   * @brief Return the number of processes actively running on the system.
   *
   * @return int
   */
  int RunningProcesses();

  /**
   * @brief Return the system's kernel identifier (string).
   *
   * @return std::string
   */
  std::string Kernel();

  /**
   * @brief Return the operating system name.
   *
   * @return std::string
   */
  std::string OperatingSystem();

private:
  /// Processor class contains information about the CPU.
  Processor cpu_ = {};
  /// All the process running in the system.
  std::vector<Process> processes_ = {};
  /// Stores the OS because it won't change at runtime.
  std::string operating_system_ = {};
  /// Stores the Kernel because it won't change at runtime.
  std::string kernel_ = {};
};

#endif
