#include "container.h"

#include "out.h"
#include "collision.h"

Container::Container()
#ifdef SCREEN
    :
    visual(new collision_visualizer)
#endif
{
}

void Container::Push(const std::shared_ptr<Object> &obj)
{
    objects.emplace_back(obj);
}

void Container::Remove(std::shared_ptr<Object> obj)
{
    error("Remove");
}

void Container::Update()
{
    if(objects.size() == 0)
        return;

    auto t = std::remove_if(objects.begin(),objects.end(),[](const std::shared_ptr<Object> &o){return o.use_count()==1;});
    objects.erase(t,objects.end());

    objects.sort([](shared_ptr<Object> o1 , shared_ptr<Object> o2){return o1->Active() < o2->Active();});
    auto active_end = objects.begin();

    while(active_end!= objects.end())
    {
        if( (*active_end)->Active() == 0 )
            break;
        ++active_end;
    }
#undef SCREEN
#ifdef SCREEN
    std::vector<MultiPointShape> col;
#endif
    for(auto first = objects.begin() ; first != active_end && first != objects.end() ; ++first)
    {
        for(auto second = std::next(first) ; second != objects.end() ; ++second)
        {
            if(ExecuteCollision(first->get(),second->get()))
            {
#ifdef SCREEN
                col.push_back(first->get()->Poligon());
                col.push_back(second->get()->Poligon());
#endif
            }
        }
    }

#ifdef SCREEN
        {
            visual->clear();
            for(const auto &x : this->objects)
                visual->push(x->Poligon());
             for(const auto &x : col)
                visual->pushCollision(x);
        }
#endif
    for(const auto& x : objects)
        x->Update();
}
