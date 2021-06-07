#include <iostream>
#include <game.h>

using namespace std;

int main()
{
    game g;
    g.loop();


    Vector2f vect;
    cout << lines_collision({{-1, 0},{1, 0}},{{-1, 1},{1, -1}},vect)  << ":" << vect.x << ":" << vect.y << endl;

    return 0;
}
