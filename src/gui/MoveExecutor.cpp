#include "MoveExecutor.h"

MoveExecutor::MoveExecutor(Game* game, GameOverHandler* chain,
                           NotificationManager* notifManager, TurnManager* turnMgr)
    : game(game), gameOverChain(chain), notificationManager(notifManager),
      turnManager(turnMgr) {}

MoveExecutor::~MoveExecutor() {}

void MoveExecutor::executeMove(int dx, int dy) {
    Player* player = game->getPlayer();
    Map* map = game->getMap();
    Position* current = player->getCurrentRoom();
    
    int newX = current->getX() + dx;
    int newY = current->getY() + dy;
    
    // Validate move
    if (!map->isValidPosition(newX, newY) || !player->canMove()) {
        return;
    }
    
    // Execute move
    delete player->getCurrentRoom();
    Position* newPos = new Position(newX, newY);
    player->setCurrentRoom(newPos);
    
    Room* room = map->getRoomAt(newPos);
    player->visitRoom(room);
    player->decrementMoves();
    player->update();
    
    // Check game over
    if (gameOverChain->handle(game)) {
        return;
    }
    
    // Show notification
    showRoomNotification(room);
    
    // Check if turn ends
    if (!player->canMove()) {
        turnManager->handleEndOfPlayerTurn();
    }
}

void MoveExecutor::showRoomNotification(Room* room) {
    std::string roomType = room->getRoomType();
    if (roomType != "Normal" && room->isVisited()) {
        notificationManager->show("Entered " + roomType + " Room!");
    }
}
