#ifndef PLAYER_H
#define PLAYER_H

#include "../CourseLib/core/playerbase.h"
#include "../CourseLib/core/gameobject.h"

class Player : public Course::PlayerBase
{
public:
    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects);

    ~Player();


private:

};

#endif // PLAYER_H
