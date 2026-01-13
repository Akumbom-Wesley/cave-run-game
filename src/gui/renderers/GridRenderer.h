#ifndef GRIDRENDERER_H
#define GRIDRENDERER_H

#include "Renderer.h"
#include "../../world/Map.h"

class GridRenderer : public Renderer {
private:
    Map* map;
    int gridOffsetY;
    
public:
    GridRenderer(sf::RenderWindow* window, sf::Font* font, int cellSize, Map* map, int offsetY = 80);
    void render() override;
};

#endif
