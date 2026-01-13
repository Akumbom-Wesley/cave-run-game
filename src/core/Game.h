#ifndef GAME_H
#define GAME_H

#include "../world/Map.h"
#include "../entities/Player.h"
#include "../entities/Monster.h"
#include "DifficultyConfig.h"
#include <vector>
#include <string>
#include <set>

using namespace std;

enum DeathCause {
    NONE,
    MONSTER_CAUGHT,
    HEALTH_DEPLETED
};

class Game {
private:
    Map* map;
    Player* player;
    Monster* monster;
    bool gameOver;
    bool playerWon;
    int turnCount;
    DeathCause deathCause;
    Difficulty currentDifficulty;
    DifficultyConfig config;

    void setupMap();
    vector<Position*> calculateSafePath();
    void placeHazardsSmartly(vector<Position*>& safePath);
    void placeHelpfulRooms();
    Position* calculateMonsterStartPosition(vector<Position*>& safePath);

public:
    Game(int width, int height, Difficulty diff);
    ~Game();
    void run();
    void playerTurn();
    void monsterTurn();
    void checkGameOver();
    bool isGameOver() const;
    bool hasPlayerWon() const;
    Player* getPlayer() const;
    Monster* getMonster() const;
    Map* getMap() const;
    Position* getPlayerPosition() const;
    int getMistakeChance() const;
    void displayGameState() const;
    int getTurnCount() const;
    DeathCause getDeathCause() const;
    void setDeathCause(DeathCause cause);
    void incrementTurnCount();  // NEW: Increment turn counter
    Difficulty getDifficulty() const;  // NEW: Get difficulty
    string getDifficultyString() const;  // NEW: Get difficulty as string
};

#endif
