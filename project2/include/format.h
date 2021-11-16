#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format
{

  /**
   * @brief Convert seconds to HH:MM:SS string
   *
   * @param times Long int measuring seconds
   * @return std::string HH:MM:SS
   */
  std::string ElapsedTime(long times);

}; // namespace Format

#endif
