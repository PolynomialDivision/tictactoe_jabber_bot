#ifndef BOT_H
#define BOT_H

#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <string.h>
#include <iostream>
#include "game.h"

using namespace std;
using namespace gloox;

class Bot : public MessageHandler
{
 public:
   Bot()
   {
      game = new Game();
      JID jid( "XXX@XXXX/bot" );
      j = new Client( jid, "password" );
      j->registerMessageHandler( this );
      j->connect();
   }
   virtual void handleMessage( const Message& stanza,
                               MessageSession* session = 0 );
   std::list<JID> list;
   std::list<JID>::iterator it;

 private:
   string commands[3] = {"set","help"};
   bool isJidinGame(JID player);
   string parseString(string str, int* x, int* y);
   Game* game;
   Client* j;

};

#endif