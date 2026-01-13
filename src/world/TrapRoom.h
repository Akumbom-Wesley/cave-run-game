#ifndef TRAPROOM_H
#define TRAPROOM_H

#include "Room.h"

class TrapRoom : public Room {
private:
    int damage;

public:
    TrapRoom(Position* pos, int damage);
    
    void visit(Player* player) override;
    string getRoomType() const override;
};

#endif