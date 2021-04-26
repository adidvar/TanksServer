#ifndef TANK_H
#define TANK_H
#include <string>
#include <sstream>
#include <vector2f.h>

using namespace std;

class player_tank
{
    string name = "default name";
    size_t team_id = 0;
    Vector2f positions = {0,0};
    Vector2f speed = {0,0.00}; ///< x - move speed , y - rotation speed
    float rotation = 0.0;
public:
    player_tank() = default;
    /**
     * @brief оновлює стан системи
     * @param delta_time зміна часу
     */
    void update(unsigned delta_time);
    /**
     * @brief Записує стан в текстовий документ
     * @param s текстовий поток для запису
     */
    void write_state(std::stringstream &s , char sep);
    /**
     * @brief читає клієнтську інформацію з потоку
     * @param s поток для считування
     */
    void read_state(std::stringstream &s);

    const static unsigned write_count = 5;
};

#endif // TANK_H
