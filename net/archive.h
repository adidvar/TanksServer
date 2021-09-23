#ifndef ARCHIVE_H
#define ARCHIVE_H
#include <string>
#include <sstream>
#include <vector>

/**
 * @brief Серіалізатор
 */
class archive
{
    std::stringstream stream;
public:
    archive()
    {
        stream.precision(10);
    };

    template<typename T>
    void write(T data)
    {
        stream << data << ';';
    }
	void packend()
	{
		stream << ':';
	}

    std::string text()
	{
		return stream.str();
	};
};

#endif // ARCHIVE_H
