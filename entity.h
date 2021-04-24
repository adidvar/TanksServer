#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <vector2f.h>

class entity
{
    Vector2f position;
    float rotation = 0;
public:
    entity() = default;
    /**
     * @brief оновлює стан системи
     * @param delta_time зміна часу
     */
    virtual void update(unsigned delta_time){};
    /**
     * @brief Записує стан в текстовий документ
     * @param s текстовий поток для запису
     */
    void write_state(std::stringstream &s , char sep);

    const static unsigned write_count = 3;
};

#endif // ENTITY_H
