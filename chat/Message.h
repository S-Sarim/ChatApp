#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include "IRecord.h"

#include <iomanip>
#include <iostream>
#include <time.h>

class Message : public IRecord {
private:
    const string &getTable() const override {
        return TableName;
    }
    const string &insertColumns() const override {
        static const string columns = "Sender, Recipient, Body, Timestamp";
        return columns;
    }
    string insertValues() const override {
        return build(sender, recipient, message, timestamp);
    }
    string updateValues() const override {
        static const vector<string> columns = {"Sender", "Recipient", "Body",
                                               "Timestamp"};
        return build(columns, sender, recipient, message, timestamp);
    }
    vector<Condition> updateConditions() const override {
        return {Condition::Impossible};
    }
    vector<Condition> removeConditions() const override {
        return {{"Sender", sender, E},
                {"Recipient", recipient, E},
                {"Body", message, E},
                {"Timestamp", timestamp, E}};
    }
    string sender;
    string recipient;
    string message;
    time_t timestamp;
    int pad;

public:
    static const string TableName;
    Message(string sender, string recipient, string message) :
        sender(sender), recipient(recipient), message(message),
        timestamp(time(nullptr)), pad(0) {
        insert();
    }
    Message(const vector<string> &values) :
        sender(values.at(0)), recipient(values.at(1)), message(values.at(2)),
        timestamp(stoll(values.at(3))), pad(0) {}
    bool operator<(const Message &other) const {
        return timestamp < other.timestamp;
    }
    string getTimeString() const {
        return ctime(&timestamp);
    }
    string getSender() const {
        return sender;
    }
    void setPad(int x = 60) {
        pad = x;
    }
    friend ostream &operator<<(ostream &out, const Message &msg) {
        int i = 0;
                out << '\n' << std::setw(msg.pad) << "";
        for (char ch : msg.message) {
            out << ch;
            ++i;
            if (i == 20) {
                i = 0;
                out << '\n' << std::setw(msg.pad) << "";
            }
        }
        return out << '\n' << std::setw(msg.pad) << "" << msg.getTimeString();
    }
};

const string Message::TableName = "Messages";

/*
CREATE TABLE Messages(
    Sender    TEXT NOT NULL,
    Recipient TEXT NOT NULL,
    Body      TEXT NOT NULL,
    Timestamp INT  NOT NULL
);
*/
#endif // __MESSAGES_H__