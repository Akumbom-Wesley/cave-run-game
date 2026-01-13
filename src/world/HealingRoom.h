#ifndef HEALINGROOM_H
#define HEALINGROOM_H

#include "Room.h"

class HealingRoom : public Room {
private:
    int healAmount;

public:
    HealingRoom(Position* pos, int healAmount);
    
    void visit(Player* player) override;
    string getRoomType() const override;
};

#endif