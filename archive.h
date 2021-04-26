#ifndef ARCHIVE_H
#define ARCHIVE_H
#include <string>
#include <sstream>

/**
 * @brief Серіалізатор
 */
class archive
{
    std::stringstream stream;
public:
    archive() = default;

    template<typename T>
    void write(T data)
    {
        stream << data << ";";
    }

    std::string text(){return stream.str();};
};

#endif // ARCHIVE_H
