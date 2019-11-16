#ifndef PLAYER_H
#define PLAYER_H

#include "../CourseLib/core/playerbase.h"
#include "../CourseLib/core/gameobject.h"
#include "QGraphicsPixmapItem"
namespace Game{

class Player : public Course::PlayerBase
{
public:
    Player(const std::string&,
           const std::vector<std::shared_ptr<Course::GameObject> > objects = {});
    QGraphicsPixmapItem * sprite;

    ~Player();


private:

};
}

#endif // PLAYER_H
