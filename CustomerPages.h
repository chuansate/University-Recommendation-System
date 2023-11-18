#ifndef CUSTOMERPAGES_H
#define CUSTOMERPAGES_H
#include <iostream>
#include <string>
#include <limits>
#include "SavedUniList.h"
#include "UniArray.h"
#include "FavUniList.h"
#include "FeedbackList.h"
using namespace std;
string tm2string(tm*);
void CustHomePage(string, SavedUniList*, UniArray*, FeedbackList*);
void SortUni(UniArray*);
void SaveUni(UniArray*, SavedUniList*, string);
void CheckSavedUniList(SavedUniList*);
void CheckAndDeleteFavUni(string, SavedUniList*);
void SearchUniBasedOnScores(UniArray*);
void SendFeedback(FeedbackList*, string);
void ReadFeedback(FeedbackList*, string);
#endif