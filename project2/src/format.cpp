#include <string>
#include <sstream>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  std::ostringstream result;
  long hours, minutes;
  minutes = seconds / 60;
  hours = minutes / 60;
  minutes = minutes%60;
  seconds = seconds%60;
  if (hours < 10)
    result << "0";
  result << hours << ":";
  if (minutes < 10)
    result << "0";
  result << minutes << ":";
  if (seconds < 10)
    result << "0";
  result << seconds;
  return result.str();
}
