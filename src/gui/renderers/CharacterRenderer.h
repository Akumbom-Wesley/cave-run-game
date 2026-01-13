#ifndef CHARACTERRENDERER_H
#define CHARACTERRENDERER_H

#include "Renderer.h"
#include "../../entities/Player.h"
#include "../../entities/Monster.h"
#include "../../world/Map.h"

class CharacterRenderer : public Renderer {
private:
    Player* player;
    Monster* monster;
    Map* map;
    int gridOffsetY;

    void drawPlayer();
    void drawMonster();

public:
    CharacterRenderer(sf::RenderWindow* window, sf::Font* font, int cellSize,
                     Player* player, Monster* monster, Map* map, int offsetY = 80);
    void render() override;
};

#endif
