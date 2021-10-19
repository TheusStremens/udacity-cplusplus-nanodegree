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
  if (hours < 10)
    result << "0";
  result << hours << ":" << minutes%60 << ":" << seconds%60;
  return result.str();
}
