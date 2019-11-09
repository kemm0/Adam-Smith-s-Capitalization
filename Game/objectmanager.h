#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <../CourseLib/core/gameobject.h>
#include <../CourseLib/tiles/grassland.h>
#include "map.h"

class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = nullptr);
    void readObjectsFromMap(std::vector<std::vector<int>>& ObjectMap);
private:
    std::vector<std::vector<std::shared_ptr<Course::GameObject>> gameObjects;
    std::vector<std::vector<int>> vMap;

signals:

public slots:
};

#endif // OBJECTMANAGER_H
