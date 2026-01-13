#include "../gui/renderers/Renderer.h"

Renderer::Renderer(sf::RenderWindow* window, sf::Font* font, int cellSize)
    : window(window), font(font), cellSize(cellSize) {}

Renderer::~Renderer() {}
