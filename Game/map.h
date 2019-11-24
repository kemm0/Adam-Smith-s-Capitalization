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
#include "Tiles/grasstile.h"
#include "player.h"
#include "QGraphicsColorizeEffect"
#include "gamemapgenerator.h"

namespace Game{

class Map : public QGraphicsScene
{
        Q_OBJECT

    public:
        Map(QObject *parent = nullptr,
            std::shared_ptr<Game::GameEventHandler> eventHandler = nullptr,
            std::shared_ptr<Game::GameObjectManager> objManager = nullptr,
            std::shared_ptr<Game::GameMapGenerator> mapGenerator = nullptr);

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
        void drawMap();

    private:
        int tileSize;
        int mapWidth;
        int mapHeight;
        QGraphicsItem* selectedTile;
        std::shared_ptr<Game::GameEventHandler> eventHandler_;
        std::shared_ptr<Game::GameObjectManager> objManager_;
        std::shared_ptr<Game::GameMapGenerator> mapGenerator_;
        void showTileMovableEffect(QGraphicsItem* targetTile);
        void showTileHighlightEffect(QGraphicsItem* targetTile);
    signals:
        void scrollOut();
        void scrollIn();
    public slots:
        //void zoom();
    };
}

#endif // MAP_H
