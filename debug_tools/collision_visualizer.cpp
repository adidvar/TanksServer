#include "collision_visualizer.h"

collision_visualizer::collision_visualizer()
{
    th = new  std::thread(&collision_visualizer::render,this);
    th->detach();
};

void collision_visualizer::render()
{
    window = new sf::RenderWindow(sf::VideoMode(1280,720),"Coll");
    window->setActive(true);
    window->setFramerateLimit(60);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        sf::VertexArray array;
        array.setPrimitiveType(sf::PrimitiveType::Lines);

        float scale =10;
        float delta = 100;

        l_mutex.lock();
        for(auto x : lines)
        {
            array.append(sf::Vertex({scale*x.end.x + delta,scale*x.end.y + delta}));
            array.append(sf::Vertex({scale*x.begin.x + delta,scale*x.begin.y + delta}));
        }
        l_mutex.unlock();

        window->clear();

        window->draw(array);

        window->display();
    }
}

void collision_visualizer::set_lines(std::vector<line> lines)
{
    l_mutex.lock();
    this->lines = lines;
    l_mutex.unlock();
}
