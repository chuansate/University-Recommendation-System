#ifndef SAVEDUNILIST_H
#define SAVEDUNILIST_H
#include <iostream>
#include <string>
#include <limits>
using namespace std;

typedef struct SAVED_UNI_REC {
    string saved_uniname;
    string cust_uname;
    SAVED_UNI_REC* next;
    SAVED_UNI_REC* prev;
}SavedUniRec;

class SavedUniList {
private:
    int length;
    SavedUniRec* head;
    SavedUniRec* tail; // keeping reference to tail, so that insertion at end takes O(1)

public:
    SavedUniList();
    void insertAtEnd(string, string);
    void PrintList();
    SavedUniRec* getTail();
    bool UniWasSaved(string, string);
    SavedUniRec* getHead();
    void DeleteSavedUni(string, string);
};

#endif