#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

class NotificationManager {
private:
    std::string notificationText;
    sf::Clock notificationClock;
    bool showingNotification;
    float displayDuration;
    
public:
    NotificationManager(float duration = 3.0f);
    ~NotificationManager();

    void show(const std::string& message);
    void hide();
    bool isShowing() const;
    
    void render(sf::RenderWindow* window, sf::Font* font, int windowWidth, int windowHeight);
};

#endif
