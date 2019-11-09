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
#include "objectmanager.h"

class Map : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Map(QGraphicsScene *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
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

signals:

public slots:
    //void zoom();
};

#endif // MAP_H
