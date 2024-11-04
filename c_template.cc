#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argc + argv};
  if (command_line.size() < 2) {
    std::cerr << "invalid argument count\n";
    return 1;
  }

  const fs::path fpath{std::getenv("HOME")};

  const std::string user_create_folder{command_line.at(1)};
  fs::create_directories(fpath / user_create_folder);

  const std::string user_create_file{command_line.at(2)};
  std::ofstream output_f{user_create_file + ".cc"};

  if (!output_f) {
    std::cerr << "file could not be opened\n";
    return 1;
  }

  output_f << "#include <iostream>\n#include <string>\n\n";
  output_f << "int main(int argc, char* argv[]) { return 0; }";

  if (output_f.bad() || output_f.fail()) {
    std::cerr << "error\n";
    return 1;
  }
  output_f.close();

  const std::string file_current{"C_template_file/" + user_create_file + ".cc"};
  const std::string file_destination{user_create_folder + "/" +
                                     user_create_file + ".cc"};

  fs::rename(fpath / file_current, fpath / file_destination);

  return 0;
}