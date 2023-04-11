#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

string tm2string(tm*);
class Hash_Table {
private:
    static const int tableSize = 10;
    typedef struct USERACC {
        string uname;
        string password;
        tm* last_active_time;
        USERACC* next;
    }UserAcc;
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
    void DeleteAllInactiveCustAcc();
};
#endif