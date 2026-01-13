#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

class Renderer {
protected:
    sf::RenderWindow* window;
    sf::Font* font;
    int cellSize;
    
public:
    Renderer(sf::RenderWindow* window, sf::Font* font, int cellSize);
    virtual ~Renderer();
    virtual void render() = 0;  // Pure virtual
};

#endif
