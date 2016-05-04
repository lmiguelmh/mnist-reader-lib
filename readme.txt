MNIST digits database reader in C++. Project for PUCP/mi/ml. Uses CLion, MAVEN NAR plugin and VS2015 Community Edition.

INSTRUCTIONS FOR RUNNING THE READER
Download and install VS2015 redistributable from https://www.microsoft.com/en-us/download/details.aspx?id=48145. This is not needed if you have VS2015 installed.

INSTRUCTIONS FOR COMPILING THE PROJECT
This project uses CLion, MAVEN NAR plugin and VS2015 Community Edition.
1. Install VS2015
2. Install Maven
3. From a command line
 - Use `mvn install` to compile and install file-lib and coutlogger-lib libraries
 - Use `mvn test` to generate the test file for mnist-reader-lib
4. mnist-reader-lib-test.exe will be generated in mnist-reader-lib\target\test-nar\bin\x86-Windows-msvc
