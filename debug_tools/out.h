#ifndef OUT_H
#define OUT_H

#include <iostream>

using namespace std;

inline void error(std::string str)
{
    cout << "ERROR: " <<  str << endl;
    std::terminate();
}

inline void warning(std::string str)
{
    cout << "WARNING: " << str << endl;
}
inline void debug(std::string str)
{
    cout << "DEBUG: " << str << endl;
}
inline void info(std::string str)
{
    cout << "INFO: " << str << endl;
}

#endif // OUT_H
