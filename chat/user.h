#ifndef __USER_H__
#define __USER_H__

#include "IRecord.h"
#include "Message.h"

class User : public IRecord {
private:
    const string &getTable() const override {
        return TableName;
    }
    const string &insertColumns() const override {
        static const string columns =
            "Username, Password, Name, About, Gender, Friends";
        return columns;
    }
    string insertValues() const override {
        return build(username, password, name, about, gender,
                     getFriendString());
    }
    string updateValues() const override {
        static const vector<string> columns = {"Password", "Name", "About",
                                               "Gender", "Friends"};
        return build(columns, password, name, about, gender, getFriendString());
    }
    vector<Condition> updateConditions() const override {
        return {{"Username", username, E}};
    }
    vector<Condition> removeConditions() const override {
        return {{"Username", username, E}};
    }
    string getFriendString() const {
        string friendString;
        for (int i = 0; i < friends.size(); ++i) {
            friendString.append(friends.at(i));
            friendString.push_back(';');
        }
        return friendString;
    }
    string username;
    string password;
    string name;
    string about;
    string gender;
    vector<string> friends;

public:
    static const string TableName;
    User(string username, string password) :
        username(username), password(password) {
        insert();
    }
    User(const vector<string> &values) :
        username(values.at(0)), password(values.at(1)), name(values.at(2)),
        about(values.at(3)), gender(values.at(4)) {
        string friendString = values.at(5);
        int prev = 0;
        while (prev < friendString.length()) {
            int last = friendString.find_first_of(';', prev);
            friends.push_back(friendString.substr(prev, last - prev));
            prev = last + 1;
        }
    }
    bool addFriend(string friendName) {
        if (exists(friendName)) {
            friends.push_back(friendName);
            update();
            return true;
        }
        return false;
    }
    bool removeFriend(string friendName) {
        for (auto it = friends.begin(); it != friends.end(); ++it) {
            if (*it == friendName) {
                friends.erase(it);
                update();
                return true;
            }
        }
        return false;
    }
    bool isfriend(string friendname) {
        for (auto frnd : friends) {
            if (frnd == friendname) {
                return true;
            }
        }
        return false;
    }
    const std::vector<std::string> & getFriends() const {
        return friends;
    }
    string getName() const {
        return username;
    }
    void setName(string name) {
        this->name = name;
        update();
    }
    void setPassword(string password) {
        this->password = password;
        update();
    }
    void setAbout(string about) {
        this->about = about;
        update();
    }
    void setGender(string gender) {
        this->gender = gender;
        update();
    }
    string getPassword() const {
        return password;
    }
    static bool exists(string username) {
        return !IRecord::select<User>({{"Username", username, E}}).empty();
    }
};
/*
CREATE TABLE Users(
    Username TEXT PRIMARY KEY NOT NULL,
    Password TEXT NOT NULL,
    Name     TEXT NOT NULL,
    About    TEXT NOT NULL,
    Gender   TEXT NOT NULL,
    Friends  TEXT NOT NULL
);
*/

const string User::TableName = "Users";

#endif // __USER_H__
