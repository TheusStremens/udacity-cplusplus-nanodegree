#ifndef PROCESSOR_H
#define PROCESSOR_H

// Just save some spaces in the code.
using longest_int = unsigned long long int;

class Processor
{
public:
  /**
   * @brief Return the aggregate CPU utilization
   *
   * @return float
   */
  float Utilization();

private:
  /**
   * @brief Open the /proc/stat, parse the first line and set the time members.
   *
   */
  void ReadCPUTimeVariables();

  /// Basic time variables present in /proc/stat. For more details see the section 1.8
  /// at https://www.kernel.org/doc/Documentation/filesystems/proc.txt
  longest_int user_time_, nice_time_, system_time_, idle_time_;
  longest_int io_wait_, irq_, soft_irq_, steal_, guest_, guest_nice_;

  /// Accumulated previous times.
  longest_int previous_total_time_{0}, previous_total_idle_time_{0};

  /// Accumulated actual times.
  longest_int actual_total_time_, actual_total_idle_time_;
  longest_int actual_total_system_time_, actual_total_virtual_time_;
};

#endif
