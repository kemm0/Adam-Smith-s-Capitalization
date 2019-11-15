#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include "../Course/CourseLib/tiles/forest.h"
#include "grasstile.h"


class Map : public QGraphicsScene
{
    Q_OBJECT

public:
    Map(QObject *parent = nullptr,
                 std::shared_ptr<GameObjectManager> objectsManager = nullptr,
                 std::shared_ptr<GameEventHandler> eventsHandler = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    int tileSize;
    int mapWidth;
    int mapHeight;
    std::vector<std::vector<int>> vMap;
    void drawMap();
    std::vector<QGraphicsPixmapItem*> sprites;
    std::vector<Course::GameObject> gameObjects;
    QGraphicsPixmapItem* player;
    std::shared_ptr<GameObjectManager> objectManager_;
    std::shared_ptr<GameEventHandler> eventHandler_;

signals:

public slots:
    //void zoom();
};

#endif // MAP_H
