#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

typedef struct USERACC {
    string uname;
    string password;
    tm* last_active_time;
    USERACC* next;
}UserAcc;

string tm2string(tm*);

struct InactiveCust {
    string uname;
    InactiveCust* next;
};

class InactiveCustsList {
private:
    InactiveCust* head;
    InactiveCust* tail;
public:
    InactiveCustsList();
    void append(string);
    ~InactiveCustsList();
    void printInactiveCusts();
    InactiveCust* getHead();
};

class Hash_Table {
private:
    static const int tableSize = 10;
    UserAcc* HashTable[tableSize];//each bucket store a linked list(elem of HashTable is known as bucket)
public:
    Hash_Table(tm* default_time);
    int Hash(string uname);
    void AddUserAcc(string uname, string password, tm* last_active_time);
    int NumberOfUserAccInIndex(int index);
    void PrintTable();
    void PrintUserAccInIndex(int index);
    string SearchForUname(string uname);
    void UpdateLastActive(string uname, tm* last_active_time);
    void RemoveUserAcc(string uname);
    void PrintUserAccsInTableForm();
    int UpdatePwd(string);
    int getTableSize();
    UserAcc* getBucketAtIndex(int);
};
#endif