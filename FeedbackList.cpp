#include "FeedbackList.h"

FeedbackList::FeedbackList() {
    length = 0;
    head = NULL;
    tail = NULL;
}

//using the `tail`
void FeedbackList::insertAtEnd(string content, tm* feedback_time, string replied_admin, string reply_content, tm* reply_time, string cust_uname) {
    //Initialize a new node
    Feedback* newnode = new Feedback;
    newnode->feedbackID = length + 1;// Assuming no deletion of feedbacks
    newnode->content = content;
    newnode->feedback_time = feedback_time;
    newnode->replied_admin = replied_admin;
    newnode->reply_content = reply_content;
    newnode->reply_time = reply_time;
    newnode->cust_uname = cust_uname;
    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL) {// if empty list
        head = newnode;
        tail = newnode;
    } else {
        tail->next = newnode;
        newnode->prev = tail;
        tail = tail->next;   
    }
    length++;
}

void FeedbackList::PrintList() {
    if (head == NULL) {
        cout << "List is empty!" << endl;
        return;
    }
    int length = 0;
    Feedback* current = head;
    while (current != NULL) {
        cout << "*****Node " << length << "*****" << endl;
        cout << "Feedback ID = " << current->feedbackID << endl;
        cout << "Content = " << current->content << endl;
        cout << "Cust uname = " << current->cust_uname << endl;
        cout << "***************" << endl << endl;
        current = current->next;
        length++;
    }
}

Feedback* FeedbackList::MoveBackAndForth(Feedback* current, char action) {
    // 0 - move back, 1 - move forth
    if (action == '0') {
        if (current->prev != NULL) {
            current = current->prev;
            system("cls");            
        }
        else {
            cout << "That is the earliest feedback! Cannot read further!" << endl;
        }
    }
    else if (action == '1') {
        if (current->next != NULL) {
            current = current->next;
            system("cls");
        }
        else {
            cout << "That is the latest feedback! Cannot read further!" << endl;
        }
    } else {
        cout << "Invalid input, please try again!" << endl;
    }
    //seems like needa return the address of the node, this func shud receive adr of node as arg/class attribute shud keep
    return current;
}

Feedback* FeedbackList::getTail() {
    return tail;
}

void FeedbackList::Reply(Feedback* feedback, string replied_admin) {
    // rmb to update the replied admin
    string reply;
    tm* new_current_time = new tm; 
    cout << "Enter your reply: ";
    getline(cin, reply);
    feedback->reply_content = reply;
    time_t replied_now = time(0);
    tm* current_time = localtime(&replied_now);
    if (feedback->reply_time == NULL) {
        // if no reply before, just assign all those attributes
        new_current_time->tm_hour = current_time->tm_hour;
        new_current_time->tm_min = current_time->tm_min;
        new_current_time->tm_sec = current_time->tm_sec;
        new_current_time->tm_year = current_time->tm_year;
        new_current_time->tm_mon = current_time->tm_mon;
        new_current_time->tm_mday = current_time->tm_mday;
        feedback->reply_time = new_current_time;
    } else {
        // if there is a reply, delete the pointer to `reply_time` first
        tm* temp = feedback->reply_time;
        delete temp;
        new_current_time->tm_hour = current_time->tm_hour;
        new_current_time->tm_min = current_time->tm_min;
        new_current_time->tm_sec = current_time->tm_sec;
        new_current_time->tm_year = current_time->tm_year;
        new_current_time->tm_mon = current_time->tm_mon;
        new_current_time->tm_mday = current_time->tm_mday;
        feedback->reply_time = new_current_time;
    }
    feedback->replied_admin = replied_admin;
}