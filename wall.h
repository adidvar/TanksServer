#ifndef WALL_H
#define WALL_H
#include <sstream>
#include <vector2f.h>

class wall
{
    Vector2f positions = {0,0};
    Vector2f size = {0,0};
    float rotation;

public:
    wall() = default;
    /**
     * @brief оновлює стан системи
     * @param delta_time зміна часу
     */
    void update(unsigned delta_time){};
    /**
     * @brief Записує стан в текстовий документ
     * @param s текстовий поток для запису
     */
    void write_state(std::stringstream &s , char sep);

    const static unsigned write_count = 5;
};

#endif // WALL_H
