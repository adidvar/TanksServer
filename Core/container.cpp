#include "container.h"

#include "out.h"
#include "collision.h"

#include <algorithm>

Container::Container()
#ifdef SCREEN
    :
    visual(new collision_visualizer)
#endif
{
}

void Container::Push(std::shared_ptr<Object> object)
{
    objects.push_back(object);
}

void Container::Remove(std::shared_ptr<Object> obj)
{
    error("Remove");
}

void Container::Update(unsigned delta_time)
{
    if(objects.size() == 0)
        return;

    auto t = std::remove_if(objects.begin(),objects.end(),[](const std::shared_ptr<Object> &o){return o.use_count()==1;});
    objects.erase(t,objects.end());

    std::sort(objects.begin(),objects.end(),[](shared_ptr<Object> o1 , shared_ptr<Object> o2){return o1->Active() > o2->Active();});
    auto active_end = objects.begin();

    while(active_end!= objects.end())
    {
        if( (*active_end)->Active() == 0 )
            break;
        ++active_end;
    }

    for(auto first = objects.begin() ; first != active_end && first != objects.end() ; ++first)
    {
        for(auto second = std::next(first) ; second != objects.end() ; ++second)
        {
            if(ExecuteCollision(first->get(),second->get()))
            {

            }

        }
    }
    for(const auto& x : objects)
        x->Update(delta_time);
}
