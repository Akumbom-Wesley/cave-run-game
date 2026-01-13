#ifndef POWERUPROOM_H
#define POWERUPROOM_H

#include "Room.h"

class PowerUpRoom : public Room {
public:
    PowerUpRoom(Position* pos);
    void visit(Player* player) override;
    string getRoomType() const override;
};

#endif
