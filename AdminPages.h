#ifndef ADMINPAGES_H
#define ADMINPAGES_H
#include <iostream>
#include <string>
#include <limits>
#include "FeedbackList.h"
#include "HashTable.h"
#include "SavedUniList.h"
using namespace std;

string tm2string(tm*);
void AdminHomePage(string, FeedbackList*, Hash_Table*, SavedUniList*);
void DisplayUserDetails(Hash_Table*);
void ModifyCustDetails(Hash_Table*);
void DeleteCustAcc(Hash_Table*);
void Read_ReplyFeedbacks(FeedbackList*, string);
void SummarizeTopUniPage(SavedUniList*);
#endif