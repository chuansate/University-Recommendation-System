#ifndef FAVUNILIST_H
#define FAVUNILIST_H
#include <iostream>
#include <string>
#include <limits>
#include "SavedUniList.h"
using namespace std;

typedef struct FAV_UNI {
    SavedUniRec* saved_uni_rec; // storing pointer to SavedUniRec, all these favourite unis r from the same customer
    FAV_UNI* next;
}FavUni;

class FavUniList {
private:
    int length;
    FavUni* head;
    FavUni* tail; // keeping reference to tail, so that insertion at end takes O(1)

public:
    FavUniList();
    ~FavUniList();
    void insertAtEnd(SavedUniRec*);
    void PrintList();
    FavUni* getTail();
    int getLength();
    void deleteFavUni(int index);
    string getUniName(int index);
};

#endif