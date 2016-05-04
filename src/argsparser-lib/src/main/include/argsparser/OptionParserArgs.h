//
// Created by adun on 01/05/2016.
//

#ifndef ARGSPARSER_LIB_OPTIONPARSERARGS_H
#define ARGSPARSER_LIB_OPTIONPARSERARGS_H

#include <stdio.h>
#include <stdlib.h>
#include "OptionParser.h"

namespace commons {

struct Arg : public option::Arg {
  static void printError(const char *msg1, const option::Option &opt, const char *msg2) {
    fprintf(stderr, "%s", msg1);
    fwrite(opt.name, opt.namelen, 1, stderr);
    fprintf(stderr, "%s", msg2);
  }

  static option::ArgStatus Numeric(const option::Option &option, bool msg) {
    char *endptr = 0;
    if (option.arg != 0 && strtol(option.arg, &endptr, 10)) { };
    if (endptr != option.arg && *endptr == 0)
      return option::ARG_OK;

    if (msg) printError("Option '", option, "' requires a numeric argument\n");
    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus Decimal(const option::Option &option, bool msg) {
#ifdef WIN32
    char *endptr = 0;
    if (option.arg != 0 && strtol(option.arg, &endptr, 10)) { };
    if (endptr != option.arg /*&& *endptr == 0*/) //apunta a null cuando termina de leer el buffer, en este caso se detendría en "."
        return option::ARG_OK;

    if (msg) printError("Option '", option, "' requires a decimal argument\n");
    return option::ARG_ILLEGAL;
#else
    char *endptr = 0;
    if (option.arg != 0 && strtof(option.arg, &endptr)) {
    }
    if (endptr != option.arg && *endptr == 0) {
      return option::ARG_OK;
    }

    if (msg) {
      printError("Option '", option, "' requires a decimal argument\n");
    }
    return option::ARG_ILLEGAL;
#endif
  }

  static option::ArgStatus Required(const option::Option &option, bool msg) {
    if (option.arg != 0)
      return option::ARG_OK;

    if (msg) printError("Option '", option, "' requires an argument\n");
    return option::ARG_ILLEGAL;
  }
};

}


#endif //ARGSPARSER_LIB_OPTIONPARSERARGS_H
