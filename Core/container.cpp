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
    size_t active_end = 0;

    while(active_end != objects.size())
    {
        if( objects[active_end]->Active() == 0 )
            break;
        ++active_end;
    }

    for(auto &x : objects)
        x->CollisionCycleBegin();

    std::vector<MultiPointShape> colliders;
    std::vector<Vector> n1 , n2;

    for(auto &x : objects)
        colliders.push_back(x->Poligon());

    for(size_t first = 0 ; first != active_end && first != objects.size() ; ++first)
    {
        for(auto second = first+1 ; second != objects.size() ; ++second)
        {
            if(GetCollisions(colliders[first],colliders[second],n1,n2))
            {
                for(auto &x : n1){
                    objects[second]->CollisionEvent(objects[first].get(),x);
                }
                for(auto &x : n2){
                    objects[first]->CollisionEvent(objects[second].get(),x);
                }
                n1.clear();
                n2.clear();
            }

        }
    }

    for(auto &x : objects)
        x->CollisionCycleEnd();

    for(const auto& x : objects)
        x->Update(delta_time);
}
