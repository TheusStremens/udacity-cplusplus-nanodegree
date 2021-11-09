#include "ncurses_display.h"
#include "system.h"
#include <iostream>

int main(int argc,  char** argv)
{
  System system;
  if (argc > 1)
  {
    int n = std::stoi(argv[1]);
    NCursesDisplay::Display(system, n);
  }
  else
    NCursesDisplay::Display(system);
}
