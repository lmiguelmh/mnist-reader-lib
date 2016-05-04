//
// Created by adun on 30/04/2016.
//

#ifndef MNIST_READER_LIB_READER_H
#define MNIST_READER_LIB_READER_H

#include <string>
#include <vector>
#include <direct.h>
#include <file/File.h>
#include <coutlogger/coutlogger.h>

namespace mnist {
class Matrix {
public:
  int rows;
  int cols;
  std::vector<char> data;

  Matrix() : rows(0), cols(0), data(0) { }
};

class Digit {
public:
  int digit;
  Matrix image;

  Digit() : digit(0), image() { }
};

class Reader {
protected:
  static uint32_t readInt32(char *buffer) {
    uint32_t v = *reinterpret_cast<uint32_t *>(buffer);
    return (v << 24) | ((v << 8) & 0x00FF0000) | ((v >> 8) & 0X0000FF00) | (v >> 24);
  }

  static uint32_t readInt32(char *buffer, int pos) {
    uint32_t v = *(reinterpret_cast<uint32_t *>(buffer) + pos);
    return (v << 24) | ((v << 8) & 0x00FF0000) | ((v >> 8) & 0X0000FF00) | (v >> 24);
  }

  static bool isValidIdx(char const *data) {
    return data[0] == 0x00 && data[1] == 0x00;
  }

  static bool isValidType(char const *data, char type, char dimension) {
    return data[0] == type && data[1] == dimension;
  }

  static void parseIdxHeader(std::vector<char> const &data, char type, char dimensions, std::vector<int> &size) {
    LOGT("idx data file size " << data.size());
    int const MNIST_HEADER_SIZE = 0x4;
    if (data.size() < MNIST_HEADER_SIZE) {
      throw std::runtime_error("invalid idx data file");
    }
    if (!isValidIdx(&data[0])) {
      throw std::runtime_error("invalid idx data file");
    }
    if (!isValidType(&data[2], type, dimensions)) {
      throw std::runtime_error("invalid idx data file");
    }

    int totalSize = 1;
    size = std::vector<int>(dimensions);
    for (int i = 0; i < dimensions; ++i) {
      size[i] = readInt32((char *) &data[4], i);
      totalSize *= size[i];
    }
    if (data.size() != MNIST_HEADER_SIZE + dimensions * sizeof(uint32_t) + totalSize) {
      throw std::runtime_error("invalid idx data file");
    }
  }

public:
  static void parse(std::vector<char> const &images, std::vector<char> const &labels, std::vector<Digit> &digits) {
    std::vector<int> imagesSize;
    parseIdxHeader(images, 0x08, 0x03, imagesSize);
    LOGI("idx images file contains " << imagesSize[0] << " images of " << imagesSize[1] << "x" << imagesSize[2]);

    std::vector<int> labelsSize;
    parseIdxHeader(labels, 0x08, 0x01, labelsSize);
    LOGI("idx labels file contains " << labelsSize[0] << " elements");

    if (labelsSize[0] != imagesSize[0]) {
      throw std::runtime_error("images and labels size are not equal");
    }

    int imageCount = imagesSize[0];
    int rows = imagesSize[1];
    int cols = imagesSize[2];
    digits = std::vector<Digit>(imageCount);
    for (int image = 0; image < imageCount; ++image) {
      digits[image].digit = labels[8 + image];
      digits[image].image.data = std::vector<char>(&images[16 + image * rows * cols],
                                                   &images[16 + (image + 1) * rows * cols]);
      digits[image].image.rows = rows;
      digits[image].image.cols = cols;
    }

    if (digits.size() != imageCount) {
      throw std::runtime_error("all images from file cant be loaded");
    }
  }

  static void read(std::string const imagesFile, std::string const labelsFile, std::vector<Digit> &digits) {
    std::vector<char> images;
    std::vector<char> labels;
    file::File::read(imagesFile, images);
    file::File::read(labelsFile, labels);
    LOGT("database files read, "<<images.size()<<" elements");

    parse(images, labels, digits);
    LOGT("database files parsed, "<<digits.size() <<" digits");
  }

  static void writeP5(std::string const path, std::vector<char> const &pgm, int rows, int cols, int colors = 256) {
    LOGT("file '" << path << "' " << pgm.size() << " bytes ready to be written");
    if (colors != 256 || pgm.size() != rows * cols) {
      throw std::runtime_error("unsupported pgm");
    }

    std::ofstream file(path);
    if (file.is_open()) {
      file << "P2" << std::endl;
      file << rows << ' ' << cols << std::endl;
      file << 255 << std::endl;
      for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
          unsigned char pixel = (unsigned char) pgm[r * cols + c];
          file << (int) pixel << ' ';
        }
        file << std::endl;
      }
      file.close();
    } else {
      throw std::runtime_error("file cannot be opened for writing");
    }
  }
};

}

#endif //MNIST_READER_LIB_READER_H
