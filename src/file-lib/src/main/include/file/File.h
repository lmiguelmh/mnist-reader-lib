//
// Created by adun on 30/04/2016.
//

#ifndef FILE_LIB_FILE_H
#define FILE_LIB_FILE_H

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

namespace file {

class File {
public:
  /** throws */
  static void read(std::string const path, std::vector<char> &data) {
    std::ifstream in = std::ifstream(path, std::ios::in | std::ios::binary);
    if (in.is_open()) {
      //std::string contents;
      in.seekg(0, std::ios::end);
      data.resize((unsigned int) in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&data[0], data.size());
      in.close();
    } else {
      throw std::runtime_error("file couldn't be opened");
    }
  }
};

}

#endif //FILE_LIB_FILE_H
