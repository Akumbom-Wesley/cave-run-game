#include "../gui/renderers/CharacterRenderer.h"

CharacterRenderer::CharacterRenderer(sf::RenderWindow* window, sf::Font* font, int cellSize,
                                     Player* player, Monster* monster, Map* map, int offsetY)
    : Renderer(window, font, cellSize), player(player), monster(monster),
      map(map), gridOffsetY(offsetY) {}

void CharacterRenderer::render() {
    drawPlayer();
    drawMonster();
}

void CharacterRenderer::drawPlayer() {
    Position* pos = player->getCurrentRoom();

    float baseX = (pos->getX() - 1) * cellSize + cellSize;
    float baseY = (map->getHeight() - pos->getY()) * cellSize + cellSize + gridOffsetY;

    float charSize = cellSize / 2.5f;
    float offsetX = (cellSize - charSize) / 2.f;
    float offsetY = (cellSize - charSize) / 2.f;

    // Body (blue shirt)
    sf::RectangleShape body(sf::Vector2f(charSize, charSize * 0.6f));
    body.setPosition(baseX + offsetX, baseY + offsetY + charSize * 0.3f);
    body.setFillColor(sf::Color(52, 152, 219));
    body.setOutlineThickness(1);
    body.setOutlineColor(sf::Color::Black);
    window->draw(body);

    // Head (skin tone)
    sf::RectangleShape head(sf::Vector2f(charSize * 0.7f, charSize * 0.4f));
    head.setPosition(baseX + offsetX + charSize * 0.15f, baseY + offsetY);
    head.setFillColor(sf::Color(255, 220, 177));
    head.setOutlineThickness(1);
    head.setOutlineColor(sf::Color::Black);
    window->draw(head);

    // Eyes
    sf::CircleShape eye1(2);
    eye1.setPosition(baseX + offsetX + charSize * 0.25f, baseY + offsetY + charSize * 0.15f);
    eye1.setFillColor(sf::Color::Black);
    window->draw(eye1);

    sf::CircleShape eye2(2);
    eye2.setPosition(baseX + offsetX + charSize * 0.55f, baseY + offsetY + charSize * 0.15f);
    eye2.setFillColor(sf::Color::Black);
    window->draw(eye2);
}

void CharacterRenderer::drawMonster() {
    Position* pos = monster->getCurrentRoom();

    float baseX = (pos->getX() - 1) * cellSize + cellSize;
    float baseY = (map->getHeight() - pos->getY()) * cellSize + cellSize + gridOffsetY;

    float monsterSize = cellSize / 2.2f;
    float offsetX = (cellSize - monsterSize) / 2.f;
    float offsetY = (cellSize - monsterSize) / 2.f;

    // Monster body (dark red)
    sf::RectangleShape monsterBody(sf::Vector2f(monsterSize, monsterSize * 0.8f));
    monsterBody.setPosition(baseX + offsetX, baseY + offsetY + monsterSize * 0.2f);
    monsterBody.setFillColor(sf::Color(180, 0, 0));
    monsterBody.setOutlineThickness(2);
    monsterBody.setOutlineColor(sf::Color::Black);
    window->draw(monsterBody);

    // Monster head (bright red)
    sf::RectangleShape monsterHead(sf::Vector2f(monsterSize * 0.8f, monsterSize * 0.3f));
    monsterHead.setPosition(baseX + offsetX + monsterSize * 0.1f, baseY + offsetY);
    monsterHead.setFillColor(sf::Color(220, 20, 20));
    monsterHead.setOutlineThickness(2);
    monsterHead.setOutlineColor(sf::Color::Black);
    window->draw(monsterHead);

    // Eyes
    sf::RectangleShape eye1(sf::Vector2f(6, 8));
    eye1.setPosition(baseX + offsetX + monsterSize * 0.25f, baseY + offsetY + monsterSize * 0.35f);
    eye1.setFillColor(sf::Color::White);
    window->draw(eye1);

    sf::RectangleShape eye2(sf::Vector2f(6, 8));
    eye2.setPosition(baseX + offsetX + monsterSize * 0.6f, baseY + offsetY + monsterSize * 0.35f);
    eye2.setFillColor(sf::Color::White);
    window->draw(eye2);
}
