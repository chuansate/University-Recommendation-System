#ifndef ADMINPAGES_H
#define ADMINPAGES_H
#include <iostream>
#include <string>
#include <limits>
#include "FeedbackList.h"
#include "HashTable.h"
using namespace std;

string tm2string(tm*);
void AdminHomePage(string, FeedbackList*, Hash_Table*);
void DisplayUserDetails(Hash_Table*);
void ModifyCustDetails(Hash_Table*);
void DeleteCustAcc(Hash_Table*);
void Read_ReplyFeedbacks(FeedbackList*, string);
#endif