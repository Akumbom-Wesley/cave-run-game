#ifndef POISONROOM_H
#define POISONROOM_H

#include "Room.h"

class PoisonRoom : public Room {
public:
    PoisonRoom(Position* pos);
    
    void visit(Player* player) override;
    string getRoomType() const override;
};

#endif