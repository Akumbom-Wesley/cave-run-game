#include <iostream>
#include "src/core/Game.h"
#include "src/gui/GameGUI.h"
#include "src/core/DifficultyConfig.h"
using namespace std;

int main() {
    cout << "=== CAVE RUN GAME ===\n";
    cout << "Select Mode:\n";
    cout << "1. Console\n";
    cout << "2. GUI\n";
    cout << "Choice: ";

    int modeChoice;
    cin >> modeChoice;

    cout << "Select Difficulty:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    Difficulty diff;
    if (choice == 1) diff = EASY;
    else if (choice == 2) diff = MEDIUM;
    else diff = HARD;

    Game* game = new Game(8, 8, diff);

    if (modeChoice == 2) {
        // GUI Mode
        game->getPlayer()->startTurn(2); // Start first turn
        GameGUI* gui = new GameGUI(game);
        gui->run();
        delete gui;
    } else {
        // Console Mode
        game->run();
    }

    delete game;

    return 0;
}