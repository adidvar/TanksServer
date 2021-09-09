#include "container.h"
#include <algorithm>
#include "debug_tools/out.h"

Container::Container()
{

}

void Container::Push(std::shared_ptr<Object> obj)
{
    objects.push_back(obj);
}

void Container::Remove(std::shared_ptr<Object> obj)
{
    error("Remove");
}

void Container::Update()
{

    auto t = std::remove_if(objects.begin(),objects.end(),[](const std::shared_ptr<Object> &o){return o.unique();});
    objects.erase(t,objects.end());

    sort(objects.rbegin(),objects.rend(),[](shared_ptr<Object> o1 , shared_ptr<Object> o2){return o1->Active() < o2->Active();});
    auto active_end = objects.begin();

    while(active_end!= objects.end())
    {
        if( (*active_end)->Active() == 0 )
            break;
        ++active_end;
    }
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
            visual.lock();
            visual.clear();
            for(const auto &x : this->objects)
                visual.push(x->Poligon());
             for(const auto &x : col)
                visual.pushCollision(x);
            visual.unlock();
        }
#endif


    for(const auto& x : objects)
        x->Update();
}
