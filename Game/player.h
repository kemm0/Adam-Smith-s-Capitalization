#ifndef PLAYER_H
#define PLAYER_H

#include "../CourseLib/core/playerbase.h"
#include "../CourseLib/core/gameobject.h"
#include "QGraphicsPixmapItem"
namespace Game{

class Player : public Course::PlayerBase
{
public:
    Player(const Course::Coordinate &coord,
           const std::string& name = "Adam Smith",
           const std::vector<std::shared_ptr<Course::GameObject> > objects = {});
    QGraphicsPixmapItem * sprite;

    ~Player();
    std::unique_ptr<Course::Coordinate> coord_;

private:

};
}

#endif // PLAYER_H
