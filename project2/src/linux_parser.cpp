#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <filesystem>
#include <unistd.h>

#include "linux_parser.h"

template <typename T>
T LinuxParser::findValueByKey(std::string const &key_filter, std::string const &file_name)
{
  std::string line, key;
  T value;

  std::ifstream stream(kProcDirectory + file_name);
  if (stream.is_open())
  {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == key_filter)
        {
          stream.close();
          return value;
        }
      }
    }
  }
  stream.close();
  return value;
}

template <typename T>
T LinuxParser::getValueOfFile(std::string const &file_name)
{
  std::string line;
  T value;

  std::ifstream stream(kProcDirectory + file_name);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  stream.close();
  return value;
}

std::string LinuxParser::OperatingSystem()
{
  std::string line, key, value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "PRETTY_NAME")
        {
          std::replace(value.begin(), value.end(), '_', ' ');
          filestream.close();
          return value;
        }
      }
    }
  }
  filestream.close();
  return value;
}

// FIXED: return the kernal name instead of "version"
std::string LinuxParser::Kernel()
{
  std::string os, kernel, line;
  std::ifstream filestream(kProcDirectory + kVersionFilename);
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    // Get the kernel two times because the first one is just "version".
    linestream >> os >> kernel >> kernel;
  }
  filestream.close();
  return kernel;
}

std::vector<int> LinuxParser::Pids()
{
  std::vector<int> pids;
  for (const auto &entry : std::filesystem::directory_iterator(kProcDirectory))
  {
    std::string folder_name;
    std::string full_path = entry.path();
    // Replace the the / to empty space to easily get the folder name with istringstream.
    // Example: "/proc/1190" becomes "proc 1190".
    std::replace(full_path.begin(), full_path.end(), '/', ' ');
    std::istringstream pathstream(full_path);
    // Get two times because the full path is like "proc 1190".
    pathstream >> folder_name >> folder_name;
    if (std::all_of(folder_name.begin(), folder_name.end(), isdigit))
    {
      int pid = std::stoi(folder_name);
      pids.push_back(pid);
    }
  }
  return pids;
}

float LinuxParser::MemoryUtilization()
{
  unsigned int mem_total = findValueByKey<unsigned int>(kFilterMemTotalString, kMeminfoFilename);
  unsigned int mem_free = findValueByKey<unsigned int>(kFilterMemFreeString, kMeminfoFilename);
  return (mem_total - mem_free) / (float)mem_total;
}

long LinuxParser::UpTime()
{
  std::string line;
  long uptime = 0;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  filestream.close();
  return uptime;
}

uint LinuxParser::numberOfCPUs()
{
  uint result = 0;
  std::string line, key = kFilterCpu;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open())
  {
    // Skip the first line.
    std::getline(filestream, line);
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> key;
      if (key.substr(0, 3) != kFilterCpu)
      {
        filestream.close();
        return result;
      }
      result++;
    }
  }
  filestream.close();
  return result;
}

std::vector<std::string> LinuxParser::CpuUtilization()
{
  std::vector<std::string> result;
  std::string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      result.push_back(line);
    }
  }
  filestream.close();
  return result;
}

int LinuxParser::TotalProcesses()
{
  return findValueByKey<int>(kFilterProcesses, kStatFilename);
}

int LinuxParser::RunningProcesses()
{
  return findValueByKey<int>(kFilterRunningProcesses, kStatFilename);
}

std::string LinuxParser::Command(int pid)
{
  return getValueOfFile<std::string>(std::to_string(pid) + kCmdlineFilename);
}

std::string LinuxParser::Ram(int pid)
{
  int megabytes = findValueByKey<int>(kFilterProcMem, std::to_string(pid) + kStatusFilename);
  megabytes = megabytes / 1000;
  return std::to_string(megabytes);
}

std::string LinuxParser::Uid(int pid)
{
  return findValueByKey<std::string>(kFilterUID, std::to_string(pid) + kStatusFilename);
}

std::string LinuxParser::User(int pid)
{
  std::string uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  std::string user_name, value, line;
  if (filestream.is_open())
  {
    while (value != uid && std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user_name >> value >> value;
    }
    filestream.close();
    return user_name;
  }
  filestream.close();
  return std::string();
}

long LinuxParser::UpTime(int pid)
{
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::string value, line;
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    // Read the 22th value;
    for (auto i = 0; i < 22; i++)
      linestream >> value;
    long ticks = std::stol(value);
    filestream.close();
    return ticks / sysconf(_SC_CLK_TCK);
  }
  filestream.close();
  return 0;
}

float LinuxParser::CpuUtilization(int pid, long system_uptime)
{
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::string value, line;
  long utime, stime, cutime, cstime, starttime;
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (auto i = 0; i < 22; i++)
    {
      switch (i)
      {
      case 13:
        linestream >> utime;
        break;
      case 14:
        linestream >> stime;
        break;
      case 15:
        linestream >> cutime;
        break;
      case 16:
        linestream >> cstime;
        break;
      case 21:
        linestream >> starttime;
        break;

      default:
        linestream >> value;
        break;
      }
    }
    long total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    long seconds = system_uptime - (starttime / sysconf(_SC_CLK_TCK));
    if (seconds != 0)
    {
      filestream.close();
      return ((total_time / sysconf(_SC_CLK_TCK)) / (float)seconds);
    }
  }
  filestream.close();
  return 0.0;
}
