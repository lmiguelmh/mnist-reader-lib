// You should open the terminal and type: mvn test

/* gtest
//for msvc11 http://stackoverflow.com/a/23879731/2692914
\#define GTEST_HAS_TR1_TUPLE 0
\#define GTEST_USE_OWN_TR1_TUPLE 1
#include <gtest/gtest.h>
*/

/* log4z
#include <log4z/log4z.h>
using namespace zsummer::log4z;
*/

#include <iostream>
#include <mnist/reader.h>
#include <argsparser/OptionParser.h>
#include <argsparser/OptionParserArgs.h>

using namespace std;

enum options {
  unknown,
  usage,
  imagesFile,
  labelsFile,
  startImage,
  endImage
};

#define NAME              "mnist-reader-lib-test"
#define DEFAULT_STARTIMAGE  0
#define DEFAULT_ENDIMAGE  -1

const option::Descriptor usageArguments[] = {
    {options::unknown,    0, "",  "",            option::Arg::None,
                                                    ""
                                                        "MNIST database file reader PUCP/mi/s1/ml/t1/lmiguelmh/1.0/" __DATE__  " " __TIME__ "\n"
                                                        "Database files can be downloaded from http://yann.lecun.com/exdb/mnist/\n"
                                                        "The digits will be written in PGM format in its own directory \n"
                                                        "For displaying PGM format use ImageMagick viewer\n"
                                                        "USAGE: " NAME " [options]\n\n"
                                                        "Options:"
    },
    {options::usage,      0, "h", "help",        option::Arg::None,
                                                    "  -h, --help              \tPrint usage and exit"},
    {options::imagesFile, 0, "i", "images-file", commons::Arg::Required,
                                                    "  -i,--images-file <path> \tImages database file path"},
    {options::labelsFile, 0, "l", "labels-file", commons::Arg::Required,
                                                    "  -l,--labels-file <path> \tLabels database file path"},
    {options::startImage, 0, "s", "start-image", commons::Arg::Numeric,
                                                    "  -s,--start-image <0-?>  \tInitial image index [default 0]"},
    {options::endImage,   0, "e", "end-image",   commons::Arg::Numeric,
                                                    "  -e,--end-image <0-?>    \tLast image index [default -1]"},
    {0,                   0, 0,   0,             0, 0}
};

struct Arguments {
  std::string imagesFile;
  std::string labelsFile;
  int startImage;
  int endImage;

  Arguments()
      : imagesFile(),
        labelsFile(),
        startImage(DEFAULT_STARTIMAGE),
        endImage(DEFAULT_ENDIMAGE) { }
};

bool readArguments(int argc, char *argv[], Arguments &arguments) {
  argc -= (argc > 0);
  argv += (argc > 0); // skip program name argv[0] if present

  option::Stats stats(usageArguments, argc, argv);
#ifdef WIN32
  option::Option options[255], buffer[255];
#else
  option::Option options[stats.options_max], buffer[stats.buffer_max];
#endif
  option::Parser parse(usageArguments, argc, argv, options, buffer);

  if (parse.error()) {
    option::printUsage(std::cout, usageArguments);
    return false;
  }

  if (options[options::usage] || argc == 0 || (parse.optionsCount() != 2 && parse.optionsCount() != 4)) {
    option::printUsage(std::cout, usageArguments);
    return false;
  }

  std::string imagesFile = "";
  std::string labelsFile = "";
  int startImage = DEFAULT_STARTIMAGE;
  int endImage = DEFAULT_ENDIMAGE;
  for (int i = 0; i < parse.optionsCount(); ++i) {
    option::Option &opt = buffer[i];
    switch (opt.index()) {
      case options::labelsFile:
        labelsFile = opt.arg;
        break;

      case options::imagesFile:
        imagesFile = opt.arg;
        break;

      case options::startImage:
        startImage = std::atoi(opt.arg);
        break;

      case options::endImage:
        endImage = std::atoi(opt.arg);
        break;

      case options::usage:
        // not possible, because handled further above and exits the program
      case options::unknown:
        // not possible because Arg::Unknown returns ARG_ILLEGAL
        // which aborts the parse with an error
      default:
        break;
    }
  }

  if (startImage < 0 || (endImage != -1 && startImage > endImage)) {
    std::string message = "invalid -s / -e arg";
    std::cerr << (message);
    return false;
  }

  if (endImage < -1 || (endImage != -1 && endImage < startImage)) {
    std::string message = "invalid -s / -e arg";
    std::cerr << (message);
    return false;
  }

  if (imagesFile.empty() || !std::ifstream(imagesFile).good()) {
    std::string message = "invalid -i arg";
    std::cerr << (message);
    return false;
  }

  if (labelsFile.empty() || !std::ifstream(labelsFile).good()) {
    std::string message = "invalid -l arg";
    std::cerr << (message);
    return false;
  }

  LOGI("-i: " << imagesFile);
  LOGI("-l: " << labelsFile);
  LOGI("-s: " << startImage);
  LOGI("-e: " << endImage);

  arguments.endImage = endImage;
  arguments.startImage = startImage;
  arguments.labelsFile = labelsFile;
  arguments.imagesFile = imagesFile;
  return true;
}


int main(int argc, char **argv) {

  /* log4z: initialize logger
  ILog4zManager::getRef().setLoggerName(LOG4Z_MAIN_LOGGER_ID, "mnist-reader-lib-test");
  ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, ".//");
  ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
  ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, true);
  ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, true);
  ILog4zManager::getRef().start();
  */

  /* gtest: initialize and run *all* the tests
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  */

  Arguments arguments;
  if (!readArguments(argc, argv, arguments)) {
    return 0;
  }

  std::vector<mnist::Digit> digits;
  std::string idxImages = ""; //train-images.idx3-ubyte
  std::string idxLabels = ""; //train-labels.idx1-ubyte
  idxImages = arguments.imagesFile; //train-images.idx3-ubyte
  idxLabels = arguments.labelsFile; //train-labels.idx1-ubyte
  try {
    mnist::Reader::read(idxImages, idxLabels, digits);
  } catch (std::runtime_error &e) {
    LOGE(e.what());
    return 1;
  }

  int start = arguments.startImage;
  int end = arguments.endImage != -1 ? arguments.endImage : digits.size() - 1;
  if (start >= digits.size() || end >= digits.size()) {
    LOGE("invalid -s / -e arg");
    return 1;
  }

/*
  int count[10] = {0}; //counter for each digit
  for (int i = start; i <= end; ++i) {
    mnist::Digit *digit = &digits[i];
    count[digit->digit]++;
    std::string dir = std::to_string(digit->digit);
    std::string file = dir + "/" + std::to_string(count[digit->digit]) + ".pgm";
    mkdir(dir.c_str());
    mnist::Reader::writeP5(file, digit->image.data, digit->image.cols, digit->image.rows);
    LOGT("file '" << file << "' written");
  }
*/
  int count[10] = {0}; //counter for each digit
  for (int i = 0; i < digits.size(); ++i) {
    mnist::Digit *digit = &digits[i];
    if (count[digit->digit] >= start && count[digit->digit] <= end) {
      std::string dir = std::to_string(digit->digit);
      std::string file = dir + "/" + std::to_string(count[digit->digit]) + ".pgm";
      mkdir(dir.c_str());
      mnist::Reader::writeP5(file, digit->image.data, digit->image.cols, digit->image.rows);
      LOGT("file '" << file << "' written");
    }
    if (digit->digit >= 0 && digit->digit <= 9) {
      count[digit->digit]++;
    } else {
      LOGW("***" << digit->digit << " found!");
      return 1;
    }
  }
  for (int i = 0; i < 10; ++i) {
    LOGD("digit " << i << " = " << count[i]);
  }
  return 0;
}