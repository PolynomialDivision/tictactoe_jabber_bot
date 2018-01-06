#include "bot.h"
#include <string.h>
#include <boost/lexical_cast.hpp>

void Bot::handleMessage( const Message& stanza,
                               MessageSession* session ){

    if(list.size() >= 2 && !isJidinGame(stanza.from())){
        Message msg(Message::Chat, stanza.from(), "Game is full!");
        j->send( msg );
        return;
    }

    bool inList;
    for(JID tmp : list){
        if(tmp == stanza.from())
            inList = true;
    }

    if(!inList){
        it = list.end();
        list.insert(it,stanza.from());
        string a = "You are the : " + boost::lexical_cast<std::string>(list.size()) + " Player";
        Message msg(Message::Chat, stanza.from(),a);
        j->send( msg );
        if(list.size() == 1){
            game->player_one = stanza.from();
        } else if(list.size() == 2){
            game->player_two = stanza.from();
            Message msg_canstart(Message::Chat, game->player_one, "Second Player Joined!\nThe Game can now start!");
            j->send( msg_canstart );
        }
    }

    int x;
    int y;
    int ret_setfield;
    string command = parseString(stanza.body(),&x,&y);
    if(command.compare("set") == 0){

        if(game->isStroke(stanza.from())){
            ret_setfield = game->setField(x,y);
            Message msg_printfield(Message::Chat,game->player_one,game->world->getField());
            j->send( msg_printfield );
            Message msg_printfield_two(Message::Chat,game->player_two,game->world->getField());
            j->send( msg_printfield_two );
            if(ret_setfield == -1){
                Message msg_won(Message::Chat,game->player_one,"You won!");
                Message msg_loose(Message::Chat,game->player_two,"You loose!");
                j->send( msg_won );
                j->send( msg_loose );
            }
            if(ret_setfield == -2){
                Message msg_won(Message::Chat,game->player_two,"You won!");
                Message msg_loose(Message::Chat,game->player_one,"You loose!");
                j->send( msg_won );
                j->send( msg_loose );
            }

        } else {
            Message msg_printfield(Message::Chat,stanza.from(),"Not your turn!");
            j->send( msg_printfield );
        }

    }

    if(command.compare("help") == 0){
        Message msg_help(Message::Chat,stanza.from(),"Help Message");
        j->send( msg_help );
    }

}

bool Bot::isJidinGame(JID player){
    if(game->player_one == player || game->player_two == player){
        return true;
    }
    return false;
}

string Bot::parseString(string str, int* x, int* y){
    int first = str.find_first_of('(');
    if(first == 0){
        first = str.find_first_of('\n');
    }
    int last = str.find_last_of(')');
    cout <<  str.substr(0,first) << endl;
    //cout << str << endl;
    cout << str[first+1] << endl;
    cout <<  str[last-1]   << endl;

    string command = str.substr(0,first);

    if(command.compare("set") == 0){
        *x = std::stoi( str.substr(first+1,first+1) );
        *y = std::stoi( str.substr(last-1,last-1) );
    }

    return command;
}
