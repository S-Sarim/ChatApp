#ifndef CONDITION_H
#define CONDITION_H

#include "Util.h"

#include <numeric> // For accumulate
#include <string>
#include <vector>

enum Comparator { E, NE, L, LE, G, GE };

class Condition {
private:
    static const string &getString(Comparator comp) {
        static const vector<string> comparatorStrings = {
            " = ", " != ", " < ", " <= ", " > ", " >= "};
        return comparatorStrings.at(comp);
    }
    string column;
    string comparatorString;
    string value;

public:
    static string unpack(const vector<Condition> &conditions) {
        if (conditions.empty()) {
            return "";
        }
        return "WHERE " +
               accumulate(
                   conditions.cbegin(), conditions.cend() - 1, ""s,
                   [](const string &accumulator, const Condition &condition) {
                       return accumulator + condition.str() + " AND ";
                   }) +
               conditions.back().str();
    }
    template <typename T>
    Condition(const string &column, const T &value, Comparator comp) :
        column(column), value(quote(value)), comparatorString(getString(comp)) {
    }
    string str() const {
        return column + comparatorString + value;
    }
    static const Condition Impossible;
};

const Condition Condition::Impossible("0", 1, Comparator::E);

#endif // CONDITION_H