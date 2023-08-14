#ifndef __CHATAPP_H__
#define __CHATAPP_H__

#include "Message.h"
#include "User.h"
#include "conversation.h"

#include <iostream>
using namespace std;

class ChatApp {
private:
    User user;
    enum MenuOption { MESSAGES = 1, FRIENDS, EDIT_PROFILE, EXIT };
    static std::ostream &out;
    static std::istream &in;
    void messages() {
        string message, fname;
        int opt = menu({"Inbox", "Write a message"}), opt2;
        switch (opt) {
            case 1:
                opt2 = menu(user.getFriends());
                out << Conversation(user.getName(),
                                    user.getFriends().at(opt2 - 1))
                    << '\n';
                break;
            case 2:
                out << "Enter the message: " << '\n';
                getline(in, message);
                fflush(stdin);
                out << "Enter your friend's user name: " << '\n';
                getline(in, fname);
                fflush(stdin);
                while (!user.isfriend(fname)) {
                    out << "This user is not your friend, please check username"
                        << '\n';
                    in >> fname;
                }
                Message(user.getName(), fname, message);
                break;
            default:
                break;
        }
    }
    void friends() {
        string fuser;
        int opt = menu({"Add a friend", "Remove a friend"});
        switch (opt) {
            case 1:
                out << "Enter a username to add: ";
                in >> fuser;
                if (user.addFriend(fuser)) {
                    out << "Friend request sent to" << fuser << '\n';
                } else {
                    out << fuser << "is no a user." << '\n';
                }
                break;
            case 2:
                out << "Enter a username to unfriend: ";
                in >> fuser;
                if (user.removeFriend(fuser)) {
                    out << fuser << "has been unfriened." << '\n';
                } else {
                    out << fuser << "is not a friend of yours." << '\n';
                }
                break;
            default:
                break;
        }
    }
    void editProfile() {
        string input;
        int opt = menu({"Name", "About", "Gender", "Password"});
        switch (opt) {
            case 1:
                out << "Enter your name to be displayed: ";
                getline(in, input);
                user.setName(input);
                out << "Name successfully updated" << '\n';
                break;
            case 2:
                out << "Enter something about yourself: ";
                getline(in, input);
                user.setAbout(input);
                out << "About updated!" << '\n';
                break;
            case 3:
                out << "Enter your gender: ";
                in >> input;
                user.setGender(input);
                break;
            case 4:
                out << "Enter your new password: ";
                in >> input;
                user.setPassword(input);
                out << "Password updated!" << '\n';
                break;
            default:
                break;
        }
    }

public:
    ChatApp(const User &user) : user(user) {}
    void run() {
        for (int opt = menu({"Messages", "Friends", "Edit profile", "Exit"});
             opt != EXIT;
             opt = menu({"Messages", "Friends", "Edit profile", "Exit"})) {
            switch (opt) {
                case MESSAGES:
                    messages();
                    break;
                case FRIENDS:
                    friends();
                    break;
                case EDIT_PROFILE:
                    editProfile();
                    break;
                default:
                    break;
            }
        }
    }
    static int menu(const vector<string> &options) {
        for (int i = 0; i < options.size(); ++i) {
            out << i + 1 << ". " << options.at(i) << '\n';
        }
        int opt;
        in >> opt;
        fflush(stdin);
        return opt;
    }

    ~ChatApp() {}
};

std::ostream &ChatApp::out = std::cout;
std::istream &ChatApp::in = std::cin;

#endif // __CHATAPP_H__
