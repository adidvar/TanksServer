#ifndef GAMESIGNAL_H
#define GAMESIGNAL_H

#include <any>

enum struct Sourse 
{
    System = 0,
    Module = 1,
    Object = 2
};

class GameSignal
{
    Sourse from;
    std::any data;
public:
    std::any Data() { return data; }
    Sourse Sourse() { return from; }
};

#endif 
