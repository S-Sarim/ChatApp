#include "ChatApp.h"
#include "user.h"

#include <iostream>

int main() {
    cout << "1. Login" << '\n' << "2. Register" << '\n';
    int opt;
    cin >> opt;
    if (opt == 1) {
        string username;
        cout << "Enter your username: ";
        cin >> username;
        vector<User> res = IRecord::select<User>({{"Username", username, E}});
        while (res.empty()) {
            cout << "This username does not exist, please try again: ";
            cin >> username;
            res = IRecord::select<User>({{"Username", username, E}});
        }
        User current = res.at(0);
        string password;
        cout << "Enter your password: ";
        cin >> password;
        while (current.getPassword() != password) {
            cout << "Incorrect password, please try again: ";
            cin >> password;
        }
        ChatApp(current).run();
    } else if (opt == 2) {
        string username;
        cout << "Enter a username: ";
        cin >> username;
        while (!IRecord::select<User>({{"Username", username, E}}).empty()) {
            cout << "This username is already taken, please try a different "
                    "one: ";
            cin >> username;
        }
        string password;
        cout << "Enter a password: ";
        cin >> password;
        User current(username, password);
        ChatApp(current).run();
    }
}