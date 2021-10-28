#ifndef OUT_H
#define OUT_H

#include <iostream>

using namespace std;

inline void error(std::string str)
{
    std::cout << "ERROR: " <<  str << std::endl;
    std::exit(1);
}

inline void warning(std::string str)
{
    std::cout << "WARNING: " << str << std::endl;
}
inline void debug(std::string str)
{
    std::cout << "DEBUG: " << str << std::endl;
}
inline void info(std::string str)
{
    std::cout << "INFO: " << str << std::endl;
}

#endif // OUT_H
