#ifndef IRECORD_H
#define IRECORD_H

#include "Condition.h"
#include "SQLite.h"
#include "Util.h"

class IRecord {
private:
    virtual const string &getTable() const = 0;
    virtual const string &insertColumns() const = 0;
    virtual string insertValues() const = 0;
    virtual string updateValues() const = 0;
    virtual vector<Condition> updateConditions() const = 0;
    virtual vector<Condition> removeConditions() const = 0;

protected:
    void insert() const {
        SQLite::run("INSERT INTO " + getTable() + " (" + insertColumns() +
                    ") VALUES (" + insertValues() + ");");
    }
    void remove() const {
        SQLite::run("DELETE FROM " + getTable() + " " +
                    Condition::unpack(removeConditions()) + ";");
    }

public:
    void update() const {
        SQLite::run("UPDATE " + getTable() + " SET " + updateValues() + " " +
                    Condition::unpack(updateConditions()) + ";");
    }

    template <class RecordType>
    static vector<RecordType> select(const vector<Condition> &conditions = {});
};

template <class RecordType>
vector<RecordType> IRecord::select(const vector<Condition> &conditions) {
    vector<RecordType> ret;
    SQLite::run(
        "SELECT * FROM " + RecordType::TableName + " " +
            Condition::unpack(conditions) + ";",
        [](void *retPtr, int columnCount, char **columnValues, char **) {
            ((vector<RecordType> *) retPtr)
                ->emplace_back(
                    vector<string>(columnValues, columnValues + columnCount));
            return 0;
        },
        &ret);
    return ret;
}

#endif // IRECORD_H