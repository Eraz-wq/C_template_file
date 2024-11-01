#include "c_template_functions.h"

#include <iostream>
#include <string>

void RepeatTyped(int num, std::ostream& ouput, const std::string& str) {
  int count{0};
  while (count <= num) {
    ouput << str;
    count++;
  }
}