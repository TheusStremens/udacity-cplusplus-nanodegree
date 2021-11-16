#include "linux_parser.h"
#include "processor.h"
#include <iostream>

Processor::Processor(int cpu_number) : cpu_number_(cpu_number) {}

void Processor::ReadCPUTimeVariables()
{
  auto cpu_string = LinuxParser::CpuUtilization();
  std::istringstream linestream(cpu_string[cpu_number_+1]);
  std::string cpu;
  linestream >> cpu >> user_time_ >> nice_time_ >> system_time_ >> idle_time_
  >> io_wait_ >> irq_ >> soft_irq_ >> steal_ >> guest_ >> guest_nice_;
}

float Processor::Utilization()
{
  // First update the basic time members.
  ReadCPUTimeVariables();

  // Now we can make the calculations based on
  // https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  user_time_ = user_time_ - guest_;
  nice_time_ = nice_time_ - guest_nice_;

  actual_total_idle_time_ = idle_time_ + io_wait_;
  actual_total_system_time_ = system_time_ + irq_ + soft_irq_;
  actual_total_virtual_time_ = guest_ + guest_nice_;
  actual_total_time_ = user_time_ + nice_time_ + actual_total_system_time_ + actual_total_idle_time_ + steal_ + actual_total_virtual_time_;

  // In the first time we need to use the actual times to calculate.
  if (previous_total_time_ == 0)
  {
    previous_total_time_ = actual_total_time_;
    previous_total_idle_time_ = actual_total_idle_time_;
    return (previous_total_time_ - previous_total_idle_time_) / (double)previous_total_time_;
  }

  // If is not the first time we can use the difference between now - before.
  longest_int total_diff = actual_total_time_ - previous_total_time_;
  longest_int idle_diff = actual_total_idle_time_ - previous_total_idle_time_;
  // Update previous members.
  previous_total_time_ = actual_total_time_;
  previous_total_idle_time_ = actual_total_idle_time_;
  // CPU percentage.
  return (total_diff - idle_diff) / (double)total_diff;
}

