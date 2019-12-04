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
#include "algorithm"
#include "../../Course/CourseLib/exceptions/illegalaction.h"

namespace Game{
/**
 * @brief The Map class draws the map with tiles and player
 */
class Map : public QGraphicsScene
{
Q_OBJECT

    public:
        Map(QObject *parent = nullptr,
            std::shared_ptr<Game::GameEventHandler> eventHandler = nullptr,
            std::shared_ptr<Game::GameObjectManager> objManager = nullptr,
            std::shared_ptr<Game::GameMapGenerator> mapGenerator = nullptr);
        /**
         * @brief mouseMoveEvent highligts the tile that is pointed with cursor
         * @param event different colored highlight when building or searching
         *  depending on event
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        /**
         * @brief mousePressEvent moves player, builds a house,
         * searches and hires workers
         * @param mouseEvent a click
         */
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        /**
         * @brief drawMap draw correct tiles spesified by gamemapgenerator
         */
        void drawMap();
        QGraphicsPixmapItem* player;

    private:
        int tileSize;
        int mapWidth;
        int mapHeight;
        bool onRange;
        QGraphicsItem* selectedTile;
        std::shared_ptr<Game::GameEventHandler> eventHandler_;
        std::shared_ptr<Game::GameObjectManager> objManager_;
        std::shared_ptr<Game::GameMapGenerator> mapGenerator_;
        /**
         * @brief showTileMovableEffect hihglight tiles green if they are
         * valid for selected action and red if they are not
         * @param targetTile where cursor is, action that defines validity of
         * tiles
         */
        void showRangeEffect(QGraphicsItem* targetTile,
                                   std::string action);
        /**
         * @brief showTileHighlightEffect white highlight effect for tiles
         * under cursor when the player is not doing any action
         * @param targetTile where cursor is
         */
        void showTileHighlightEffect(QGraphicsItem* targetTile);
    signals:
        /**
         * @brief robberFound
         * emitted when player encounters a robber
         */
        void robberFound();
        /**
         * @brief treasureFound
         * emitted when player encounters a treasure
         */
        void treasureFound();
        /**
         * @brief nothingFound
         * emitted when player searches an empty tile
         */
        void nothingFound();
        /**
         * @brief built
         * emitted when player has built a building
         */
        void built();
        /**
         * @brief inspectTile sends the tile's type when emitted
         * @param info
         */
        void inspectTile(std::string info);
    };
}

#endif // MAP_H
