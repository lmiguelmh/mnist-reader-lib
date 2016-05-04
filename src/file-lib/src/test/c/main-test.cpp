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
using namespace std;

int main(int argc, char **argv) {

    /* log4z: initialize logger
    ILog4zManager::getRef().setLoggerName(LOG4Z_MAIN_LOGGER_ID, "file-lib-test");
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

    cout << "file-lib-test: Hello World from Maven NAR Project Test with CLion IDE!" << endl;
    return 0;
}