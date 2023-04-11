#ifndef FEEDBACKLIST_H
#define FEEDBACKLIST_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

typedef struct FEEDBACK {
    int feedbackID;
    string content;
    tm* feedback_time;
    string replied_admin;
    string reply_content;
    tm* reply_time;
    string cust_uname;
    FEEDBACK* next;
    FEEDBACK* prev;
}Feedback;

class FeedbackList {
private:
    int length;
    Feedback* head;
    Feedback* tail;  // keeping reference to tail, so that insertion at end takes O(1)
public:
    FeedbackList();
    void insertAtEnd(string, tm*, string, string, tm*, string);
    void PrintList();
    Feedback* MoveBackAndForth(Feedback*, char);
    Feedback* getTail();
    void Reply(Feedback*, string);
};


#endif