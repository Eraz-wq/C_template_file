#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "c_template_functions.h"
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argc + argv};
  if (command_line.size() < 2) {
    std::cerr << "invalid argument count " << std::endl;
    return 1;
  }

  fs::path fpath = std::getenv("HOME");

  std::string user_create_folder{command_line.at(1)};
  fs::create_directories(fpath / user_create_folder);

  std::string user_create_file{command_line.at(2)};
  std::ofstream output_f{user_create_file+".cc"};

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

  std::string file_current{"C_template_file/"+user_create_file+".cc"};
  std::string file_destination{user_create_folder+"/"+user_create_file+".cc"};

  fs::rename(fpath / file_current, fpath /file_destination);



  return 0;
}