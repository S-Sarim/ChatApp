#ifndef __CONVERSATION_H__
#define __CONVERSATION_H__

#include "Message.h"

#include <algorithm>

class Conversation {
private:
    vector<Message> contents;
    string pers;

public:
    Conversation(string a, string b) :
        contents(
            IRecord::select<Message>({{"Sender", a, E}, {"Recipient", b, E}})),
        pers(a) {
        auto rest =
            IRecord::select<Message>({{"Sender", b, E}, {"Recipient", a, E}});
        for (auto msg : rest) {
            contents.push_back(msg);
        }
        sort(contents.begin(), contents.end());
    }
    friend ostream &operator<<(ostream &out, const Conversation &convo) {
        for (auto msg : convo.contents) {
            if (msg.getSender() == convo.pers) {
                msg.setPad(60);
                out << msg;
            } else {
                out << msg;
            }
        }
        return out;
    }
};

#endif // __CONVERSATION_H__
