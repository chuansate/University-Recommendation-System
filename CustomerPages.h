#ifndef CUSTOMERPAGES_H
#define CUSTOMERPAGES_H
#include <iostream>
#include <string>
#include <limits>
#include "SavedUniList.h"
#include "UniArray.h"
#include "FavUniList.h"
using namespace std;

void CustHomePage(string, SavedUniList*, UniArray*);
void SortUni();
void SaveUni(UniArray*, SavedUniList*, string);
void CheckSavedUniList(SavedUniList*);
void CheckAndDeleteFavUni(string, SavedUniList*);

#endif