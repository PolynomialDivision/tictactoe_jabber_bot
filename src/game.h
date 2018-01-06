#ifndef GAME_H
#define GAME_H

#include "field.h"
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>



class Game
{
public:
    Game();
    int setField(int x,int y);
    void resetFields(void);
    gloox::JID player_one;
    gloox::JID player_two;
    Field* world;
    bool isStroke(gloox::JID);


private:
    int switch_player(int player);
    int player;
};

#endif // GAME_H
