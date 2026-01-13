#include "../NotificationManager.h"

NotificationManager::NotificationManager(float duration)
    : showingNotification(false), displayDuration(duration), notificationText("") {}

NotificationManager::~NotificationManager() {}

void NotificationManager::show(const std::string& message) {
    notificationText = message;
    showingNotification = true;
    notificationClock.restart();
}

void NotificationManager::hide() {
    showingNotification = false;
}

bool NotificationManager::isShowing() const {
    return showingNotification && 
           notificationClock.getElapsedTime().asSeconds() < displayDuration;
}

void NotificationManager::render(sf::RenderWindow* window, sf::Font* font, 
                                 int windowWidth, int windowHeight) {
    if (!isShowing()) {
        return;
    }
    
    // Semi-transparent background
    sf::RectangleShape background(sf::Vector2f(400.f, 100.f));
    background.setPosition(windowWidth / 2.f - 200.f, windowHeight / 2.f - 50.f);
    background.setFillColor(sf::Color(0, 0, 0, 200));
    window->draw(background);
    
    // Notification text
    sf::Text notifText;
    notifText.setFont(*font);
    notifText.setCharacterSize(25);
    notifText.setFillColor(sf::Color::White);
    notifText.setString(notificationText);
    
    // Center the text
    sf::FloatRect textBounds = notifText.getLocalBounds();
    notifText.setPosition(windowWidth / 2.f - textBounds.width / 2.f,
                         windowHeight / 2.f - textBounds.height / 2.f);
    window->draw(notifText);
}
