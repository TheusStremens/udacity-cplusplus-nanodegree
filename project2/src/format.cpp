#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

std::string Format::ElapsedTime(long seconds)
{
  std::ostringstream result;
  long hours, minutes;
  minutes = seconds / 60;
  hours = minutes / 60;
  minutes = minutes % 60;
  seconds = seconds % 60;
  // We need to check if is needed to add an extra '0' in hours, minutes, and seconds
  // before display it
  result << std::setw(2) << std::setfill('0') << hours     // HH
         << std::setw(1) << ":"                            // :
         << std::setw(2) << std::setfill('0') << minutes   // MM
         << std::setw(1) << ":"                            // :
         << std::setw(2) << std::setfill('0') << seconds;  // SS
  return result.str();
}
