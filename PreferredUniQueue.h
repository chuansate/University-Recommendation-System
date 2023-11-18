#ifndef PREFERREDUNIQUEUE_H
#define PREFERREDUNIQUEUE_H
#include <iostream>
#include <string>
#include <limits>
using namespace std;
typedef struct PREFERRED_UNI {
    string uniname;
    int count;
    PREFERRED_UNI* next;
}PreferredUni;

class PreferredUniQueue {
private:
    PreferredUni* head;
public:
    PreferredUniQueue();
    ~PreferredUniQueue();
    void push(string, int);
    PreferredUni* createNewNode(string, int);
    void printQueue();
};

#endif