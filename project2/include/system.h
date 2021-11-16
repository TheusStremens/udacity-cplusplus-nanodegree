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
   * @brief Return the system's aggregated CPU (the first one in cpus_ container).
   *
   * @return Processor&
   */
  Processor &Cpu();

  /**
   * @brief Return the corresponding CPU.
   *
   * @param cpu_number
   * @return Processor&
   */
  Processor &Cpu(uint cpu_number);

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

  /**
   * @brief Return the number of CPUs of the system.
   *
   * @return uint
   */
  uint numberOfCPUs();

private:
  /// Container with contains information about each CPU. The first one contains the
  /// aggregated information of them.
  std::vector<Processor> cpus_ = {};
  /// All the process running in the system.
  std::vector<Process> processes_ = {};
  /// Stores the OS because it won't change at runtime.
  std::string operating_system_ = {};
  /// Stores the Kernel because it won't change at runtime.
  std::string kernel_ = {};
};

#endif
