#ifndef UIRENDERER_H
#define UIRENDERER_H

#include "Renderer.h"
#include "../../core/Game.h"

class UIRenderer : public Renderer {
private:
    Game* game;
    bool isPlayerTurn;
    int windowWidth;
    int windowHeight;
    
    void drawGameTitle();
    void drawStatusBar();
    
public:
    UIRenderer(sf::RenderWindow* window, sf::Font* font, Game* game, 
              int winWidth, int winHeight);
    void render() override;
    void setPlayerTurn(bool isPlayer);
};

#endif
