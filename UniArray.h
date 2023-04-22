#ifndef UNIARRAY_H
#define UNIARRAY_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Uni {
    string rank;
    string inst_name;
    string loc_code;
    string loc;
    string arcode;
    string arrank;
    string erscore;
    string errank;
    string fsrscore;
    string fsrrank;
    string cpfscore;
    string cpfrank;
    string lfrscore;
    string lfrrank;
    string lsrscore;
    string lsrrank;
    string lrnscore;
    string lrnrank;
    string gerscore;
    string gerrank;
    string scorescaled;
};


class UniArray {
public:
    UniArray(int size);
    ~UniArray();
    void insert(const Uni& uni);
    int getSize() const;
    Uni getUniversity(int index);
    void sortUniversitiesByName(int left, int right);
    int binarySearch(string targetName, int left, int right);
    void setIndexOfFirstUniOnPrint(int index);
    void PrintTwentyUnis(char action);
    int getMaxSize();     
    bool compareByScoresAND(const Uni& a, const Uni& b);
    void quickSortByScoresAND(int left, int right);
    void printSortedUniversities();
    void searchUniversity(float, float, float);

private:
    int partition(int left, int right);
    bool sorted; //sorted based on AR score, FSR score, and ER score 
    int partitionByScoresAND(int left, int right);
    Uni* universities;
    int uniCount;
    int maxSize;
    int index_of_first_uni_on_print; // while displaying all unis info, cmd will display 20 unis only
    int binarySearchUni(float targetAR, int left, int right);
    void linearSearchUni(float targetAR, float targetFSR, float targetER);
    template <typename T>
    void customSwap(T& a, T& b);
};

#endif








