#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "c_template_functions.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argc + argv};
  if (command_line.size() < 2) {
    std::cerr << "invalid argument count " << std::endl;
    return 1;
  }

  std::string user_input_file{command_line.at(1)};
  std::ofstream output_f{user_input_file + ".cc"};

  if (!output_f) {
    std::cerr << "file could not be opened" << std::endl;
    return 1;
  }

  output_f << "#include <iostream>\n#include <string>\n\n\n";
  // RepeatTyped(2, output_f, " \n");

  output_f << "int main(int argc, char* argv[]) {\n\n";
  output_f << "  return 0;\n";
  output_f << "}";

  if (output_f.bad() || output_f.fail()) {
    std::cerr << "error" << std::endl;
    return 1;
  }
  output_f.close();

  return 0;
}