#include "RoomRenderer.h"

RoomRenderer::RoomRenderer(sf::RenderWindow* window, sf::Font* font, int cellSize, Map* map, int offsetY)
    : Renderer(window, font, cellSize), map(map), gridOffsetY(offsetY) {}

void RoomRenderer::render() {
    for (int x = 1; x <= map->getWidth(); x++) {
        for (int y = 1; y <= map->getHeight(); y++) {
            Room* room = map->getRoomAt(x, y);
            
            // Draw colored rooms if visited
            if (room != nullptr && room->isVisited()) {
                sf::RectangleShape roomShape(sf::Vector2f(cellSize - 4.f, cellSize - 4.f));
                roomShape.setPosition((x - 1) * cellSize + cellSize + 2.f,
                                    (map->getHeight() - y) * cellSize + cellSize + gridOffsetY + 2.f);
                roomShape.setFillColor(getRoomColor(room));
                roomShape.setOutlineThickness(2);
                roomShape.setOutlineColor(sf::Color::Black);
                window->draw(roomShape);
            }
            
            // Draw exit with "EXIT" label
            if (map->isExitRoom(new Position(x, y))) {
                sf::RectangleShape exit(sf::Vector2f(cellSize - 4.f, cellSize - 4.f));
                exit.setPosition((x - 1) * cellSize + cellSize + 2.f,
                               (map->getHeight() - y) * cellSize + cellSize + gridOffsetY + 2.f);
                exit.setFillColor(sf::Color::Cyan);
                exit.setOutlineThickness(2);
                exit.setOutlineColor(sf::Color::Black);
                window->draw(exit);
                
                // "EXIT" text
                sf::Text exitText;
                exitText.setFont(*font);
                exitText.setCharacterSize(14);
                exitText.setFillColor(sf::Color::Black);
                exitText.setStyle(sf::Text::Bold);
                exitText.setString("EXIT");
                
                sf::FloatRect textBounds = exitText.getLocalBounds();
                exitText.setPosition((x - 1) * cellSize + cellSize + (cellSize - textBounds.width) / 2.f,
                                   (map->getHeight() - y) * cellSize + cellSize + 
                                   (cellSize - textBounds.height) / 2.f + gridOffsetY);
                window->draw(exitText);
            }
        }
    }
}

sf::Color RoomRenderer::getRoomColor(Room* room) {
    std::string type = room->getRoomType();
    if (type == "Poison") return sf::Color::Green;
    if (type == "Trap") return sf::Color::Red;
    if (type == "Healing") return sf::Color::White;
    if (type == "PowerUp") return sf::Color::Yellow;
    return sf::Color(60, 60, 60);
}
