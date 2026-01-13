#ifndef GAMEOVERHANDLER_H
#define GAMEOVERHANDLER_H

#include "../core/Game.h"

class GameOverHandler {
protected:
    GameOverHandler* nextHandler;

public:
    GameOverHandler() : nextHandler(nullptr) {}
    virtual ~GameOverHandler() { delete nextHandler; }

    void setNext(GameOverHandler* handler) {
        nextHandler = handler;
    }

    virtual bool handle(Game* game) {
        if (nextHandler) {
            return nextHandler->handle(game);
        }
        return false;  // No game over condition met
    }
};

// Check if player reached exit
class ExitReachedHandler : public GameOverHandler {
public:
    bool handle(Game* game) override {
        if (game->getMap()->isExitRoom(game->getPlayer()->getCurrentRoom())) {
            game->checkGameOver();  // Trigger game over in Game class
            return true;  // Game over - player won
        }
        return GameOverHandler::handle(game);
    }
};

// Check if player collided with monster
class MonsterCollisionHandler : public GameOverHandler {
public:
    bool handle(Game* game) override {
        if (game->getPlayer()->getCurrentRoom()->equals(
            game->getMonster()->getCurrentRoom())) {
            // Set HP to 0 and mark death by monster
            game->getPlayer()->damage(game->getPlayer()->getHealth());
            game->setDeathCause(MONSTER_CAUGHT);  // Set cause before checkGameOver
            game->checkGameOver();
            return true;  // Game over - player lost
            }
        return GameOverHandler::handle(game);
    }
};

// Check if player died from room effects
class PlayerDeathHandler : public GameOverHandler {
public:
    bool handle(Game* game) override {
        if (game->getPlayer()->isDead()) {
            game->setDeathCause(HEALTH_DEPLETED);  // Set cause before checkGameOver
            game->checkGameOver();
            return true;  // Game over - player died
        }
        return GameOverHandler::handle(game);
    }
};

#endif
