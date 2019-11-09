#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QObject>

class GameEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit GameEventHandler(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GAMEEVENTHANDLER_H