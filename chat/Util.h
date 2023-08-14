#ifndef UTIL_H
#define UTIL_H

#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
using namespace string_literals; // For string literal operator ""s

template <typename T>
inline string quote(const T &num) {
    return to_string(num);
}

template <>
inline string quote(const string &str) {
    return "'" + str + "'";
}

/*
 * This overlaod is needed only for compile time linking, it is never called
 * during execution.
 */
string build(const vector<string> & = {});

template <typename T, typename... Ts>
string build(T current, Ts... next) {
    return quote(current) + (sizeof...(next) == 0 ? "" : ", " + build(next...));
}

template <typename T, typename... Ts>
string build(const vector<string> &vec, T current, Ts... next) {
    return vec.at(vec.size() - sizeof...(next) - 1) + " = " + quote(current) +
           (sizeof...(next) == 0 ? "" : ", " + build(vec, next...));
}

void clear() {

}

#endif // UTIL_H