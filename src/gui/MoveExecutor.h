#ifndef MOVEEXECUTOR_H
#define MOVEEXECUTOR_H

#include "Game.h"
#include "GameOverHandler.h"
#include "NotificationManager.h"
#include "TurnManager.h"

class MoveExecutor {
private:
    Game* game;
    GameOverHandler* gameOverChain;
    NotificationManager* notificationManager;
    TurnManager* turnManager;
    
    void showRoomNotification(Room* room);
    
public:
    MoveExecutor(Game* game, GameOverHandler* chain, 
                 NotificationManager* notifManager, TurnManager* turnMgr);
    ~MoveExecutor();
    
    void executeMove(int dx, int dy);
};

#endif
