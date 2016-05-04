// You should open the terminal and type: mvn test
// It is recommend to use namespaces as physical directory levels (much like Java does with packages)

#include <iostream>
using namespace std;

/* Log4z
#include <log4z/log4z.h>
using namespace zsummer::log4z;
*/

int main() {

    /*
    Log4z initialize
    ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
    ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, ".\\");
    ILog4zManager::getRef().setLoggerName(LOG4Z_MAIN_LOGGER_ID, "argsparser-lib-log");
    ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);
    ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, false);
    ILog4zManager::getRef().start();
    */

    cout << "argsparser-lib: Hello world from Maven NAR Project with CLion IDE!" << endl;
    cout << "argsparser-lib: Now you should open the terminal set your compiler path and type: mvn test or mvn install" << endl;
    return 0;
}