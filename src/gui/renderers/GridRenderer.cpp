#include "GridRenderer.h"

GridRenderer::GridRenderer(sf::RenderWindow* window, sf::Font* font, int cellSize, Map* map, int offsetY)
    : Renderer(window, font, cellSize), map(map), gridOffsetY(offsetY) {}

void GridRenderer::render() {
    for (int x = 1; x <= map->getWidth(); x++) {
        for (int y = 1; y <= map->getHeight(); y++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 4.f, cellSize - 4.f));
            cell.setPosition((x - 1) * cellSize + cellSize + 2.f,
                           (map->getHeight() - y) * cellSize + cellSize + gridOffsetY + 2.f);
            cell.setFillColor(sf::Color(60, 60, 60));
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);
            window->draw(cell);
        }
    }
}
