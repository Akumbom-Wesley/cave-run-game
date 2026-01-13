#ifndef ROOMRENDERER_H
#define ROOMRENDERER_H

#include "Renderer.h"
#include "../../world/Map.h"

class RoomRenderer : public Renderer {
private:
    Map* map;
    int gridOffsetY;
    
    sf::Color getRoomColor(Room* room);
    
public:
    RoomRenderer(sf::RenderWindow* window, sf::Font* font, int cellSize, Map* map, int offsetY = 80);
    void render() override;
};

#endif
