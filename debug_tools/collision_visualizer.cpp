#include "collision_visualizer.h"
#include <algorithm>

/// Швидкість маштабування колесиком миші
#define SCALE_SPEED 0.1

/// Швидкість маштабування клавішами P O
#define KEY_SCALE_SPEED 2

const double scrool_speed = SCALE_SPEED;
const double key_scale_delta = KEY_SCALE_SPEED;

const float  width = 1280.0f , height = 720.0f;

float  scale_screen_width(float current_position);
float  scale_screen_height(float current_position);
float  scale_screen_base(float current_position);

float get_real_x(unsigned screen_x);
float get_real_y(unsigned screen_y);
float scale_real(float num);

void load_scale_factor(float scale);

void movement_event(sf::Event &e);


struct epos
{
    float x , y;
};

epos eposition[2] = {{-width, -height },{width,height}};

inline float transform_p(float current_position , float max_position , float proect_max_pos)
{
    return current_position / max_position * proect_max_pos;
};
float scale_screen_width(float current_position)
{
    return transform_p(current_position - eposition[0].x , eposition[1].x-eposition[0].x , width );
};
float scale_screen_height(float current_position)
{
    return transform_p(current_position - eposition[0].y , eposition[1].y-eposition[0].y , height );
};
float scale_screen_base(float current_position)
{
    return transform_p(current_position , eposition[1].y-eposition[0].y , height );
};

#include <iostream>

void movement_event(sf::Event &e)
{
    static bool move_mode = false;
    static int last_x = 0;
    static int last_y = 0;

    float delta_x = eposition[1].x - eposition[0].x;
    float delta_y = eposition[1].y - eposition[0].y;

    if(e.type == sf::Event::MouseWheelScrolled)
    {
        eposition[0].x -= -delta_x * scrool_speed * e.mouseWheelScroll.delta;
        eposition[0].y -= -delta_y  * scrool_speed * e.mouseWheelScroll.delta;
        eposition[1].x += -delta_x * scrool_speed * e.mouseWheelScroll.delta;
        eposition[1].y += -delta_y * scrool_speed * e.mouseWheelScroll.delta;
    }

    if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::O)
    {
        eposition[0].x -= transform_p( key_scale_delta  , scrool_speed , delta_x);
        eposition[0].y -= transform_p( key_scale_delta  , scrool_speed , delta_y);
        eposition[1].x += transform_p( key_scale_delta  , scrool_speed , delta_x);
        eposition[1].y += transform_p( key_scale_delta  , scrool_speed , delta_y);
    }
    if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::P)
    {
        eposition[0].x -= transform_p( -key_scale_delta  , scrool_speed , delta_x);
        eposition[0].y -= transform_p( -key_scale_delta  , scrool_speed , delta_y);
        eposition[1].x += transform_p( -key_scale_delta  , scrool_speed , delta_x);
        eposition[1].y += transform_p( -key_scale_delta  , scrool_speed , delta_y);
    }

    if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
    {
        move_mode = true;
        last_x = e.mouseButton.x ;
        last_y = e.mouseButton.y ;
    }
    if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
        move_mode = false;

    if(e.type == sf::Event::MouseMoved && move_mode)
        {
            eposition[0].x -= transform_p( (e.mouseMove.x - last_x ) , width , delta_x);
            eposition[0].y -= transform_p( (e.mouseMove.y - last_y ) , height , delta_y);
            eposition[1].x -= transform_p( (e.mouseMove.x - last_x ) , width , delta_x);
            eposition[1].y -= transform_p( (e.mouseMove.y - last_y ) , height , delta_y);
            last_x = e.mouseMove.x ;
            last_y = e.mouseMove.y ;
        }

    if(e.type == sf::Event::MouseMoved)
    {
        last_x = e.mouseMove.x ;
        last_y = e.mouseMove.y ;
    }

}

void load_scale_factor(float  scale)
{
    eposition[0] = {-width*scale, -height*scale };
    eposition[1] = { width *scale, height*scale };
}

float  get_real_x(unsigned screen_x)
{
   return eposition[0].x + (eposition[1].x - eposition[0].x)*((long double)screen_x / width);
}

float  get_real_y(unsigned screen_y)
{
   return eposition[0].y + (eposition[1].y - eposition[0].y)*((long double)screen_y / height);
}

float  scale_real(float  num)
{
    return (eposition[1].y - eposition[0].y)*((long double)num / height);
}

collision_visualizer::collision_visualizer()
{
    th = new  std::thread(&collision_visualizer::render,this);
    th->detach();
};

void collision_visualizer::render()
{
    window = new sf::RenderWindow(sf::VideoMode(width,height),"visual");
    window->setActive(true);
    window->setFramerateLimit(60);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            movement_event(event);
            if (event.type == sf::Event::Closed)
                window->close();
        }
        sf::VertexArray array;
        array.setPrimitiveType(sf::PrimitiveType::Lines);

        l_mutex.lock();
        for(auto x : lines)
        {
            array.append(sf::Vertex({scale_screen_width(x.end.x),scale_screen_height(x.end.y)}));
            array.append(sf::Vertex({scale_screen_width(x.begin.x),scale_screen_height(x.begin.y)}));
        }
        l_mutex.unlock();

        window->clear();

        window->draw(array);

        window->display();
    }
}

void collision_visualizer::clear()
{
    lines.clear();
}

void collision_visualizer::lock()
{
    l_mutex.lock();
}

void collision_visualizer::unlock()
{
    l_mutex.unlock();
}

void collision_visualizer::push(std::vector<line> lines)
{
    std::copy(lines.begin(),lines.end(),std::back_inserter(this->lines));
}
