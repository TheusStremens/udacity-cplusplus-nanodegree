#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser
{
  // Paths
  const std::string kProcDirectory{"/proc/"};
  const std::string kCmdlineFilename{"/cmdline"};
  const std::string kCpuinfoFilename{"/cpuinfo"};
  const std::string kStatusFilename{"/status"};
  const std::string kStatFilename{"/stat"};
  const std::string kUptimeFilename{"/uptime"};
  const std::string kMeminfoFilename{"/meminfo"};
  const std::string kVersionFilename{"/version"};
  const std::string kOSPath{"/etc/os-release"};
  const std::string kPasswordPath{"/etc/passwd"};

  // Fields
  const std::string kFilterProcesses("processes");
  const std::string kFilterRunningProcesses("procs_running");
  const std::string kFilterMemTotalString("MemTotal:");
  const std::string kFilterMemFreeString("MemFree:");
  const std::string kFilterCpu("cpu");
  const std::string kFilterUID("Uid:");
  const std::string kFilterProcMem("VmRSS:"); // Using physical RAM instead of virtual one.

  // -------------------
  // Helper
  // -------------------

  /**
   * @brief Generic function to open a file and get a value by a key.
   *
   * @tparam T
   * @param key_filter
   * @param file_name
   * @return T
   */
  template <typename T>
  T findValueByKey(std::string const &key_filter, std::string const &file_name);

  /**
   * @brief Generic function to open a file and return its content.
   *
   * @tparam T
   * @param file_name
   * @return T
   */
  template <typename T>
  T getValueOfFile(std::string const &file_name);

  // -------------------
  // System
  // -------------------

  /**
   * @brief Read and return the system memory utilization.
   *
   * @return float
   */
  float MemoryUtilization();

  /**
   * @brief Read and return the system uptime.
   *
   * @return long
   */
  long UpTime();

  /**
   * @brief Read and return the PIDs of all processses.
   *
   * @return std::vector<int>
   */
  std::vector<int> Pids();

  /**
   * @brief Read and return the total number of processes.
   *
   * @return int
   */
  int TotalProcesses();

  /**
   * @brief Read and return the number of running processes.
   *
   * @return int
   */
  int RunningProcesses();

  /**
   * @brief Read and return the operating system.
   *
   * @return std::string
   */
  std::string OperatingSystem();

  /**
   * @brief Read and return the kernel.
   *
   * @return std::string
   */
  std::string Kernel();

  // Note for the reviewer: I removed the enum CPUStates because it is not used.

  /**
   * @brief Read and return CPU utilization.
   *
   * @return std::vector<std::string>
   */
  std::vector<std::string> CpuUtilization();

  /**
   * @brief Return the number of CPUs of the system.
   *
   * @return uint
   */
  uint numberOfCPUs();

  // Note for the reviewer: I removed the methods Jiffies, ActiveJiffies, ActiveJiffies,
  // IdleJiffies because it's safer and more efficient to get the values at the same
  // time when I open the file. That's no sense in open a file, get a value, close the
  // file, open the same file again, and read another value. Also, split the read of
  // those values could let the code less straightforward.

  // -------------------
  // Processes
  // -------------------

  /**
   * @brief Read and return the CPU utilization by a process with corresponding pid.
   *
   * @param pid
   * @param system_uptime Used as reference in the calculation.
   * @return float
   */
  float CpuUtilization(int pid, long system_uptime);

  /**
   * @brief Read and return the command associated with a process.
   *
   * @param pid
   * @return std::string
   */
  std::string Command(int pid);

  /**
   * @brief Read and return the memory used by a process.
   *
   * @param pid
   * @return std::string
   */
  std::string Ram(int pid);

  /**
   * @brief Read and return the user ID associated with a process.
   *
   * @param pid
   * @return std::string
   */
  std::string Uid(int pid);

  /**
   * @brief Read and return the user associated with a process.
   *
   * @param pid
   * @return std::string
   */
  std::string User(int pid);

  /**
   * @brief Read and return the uptime of a process.
   *
   * @param pid
   * @return long int
   */
  long int UpTime(int pid);
}; // namespace LinuxParser

#endif
