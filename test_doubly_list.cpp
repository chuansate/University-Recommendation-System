#include <string>
#include <iostream>
#include <ctime>
#include <limits>
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

FeedbackList::FeedbackList() {
    length = 0;
    head = NULL;
    tail = NULL;
}
//REFERENCES: https://www.youtube.com/watch?v=LDMF8iqO8pg&list=PLBlnK6fEyqRg7pacSDMgPn7vDVhz3N1uf&index=4&ab_channel=NesoAcademy
//not utilizing the `tail`
/*
void FeedbackList::insertAtEnd(int feedbackID, string content, tm* feedback_time, string replied_admin, string reply_content, tm* reply_time, string cust_uname) {
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
    Feedback* current = head;
    while (current->next != NULL) {
        //`current` stops at the last node of current list
        current = current->next;
    }
    current->next = newnode;
    newnode->prev = current;
    //`temp` in yt == `newnode` here
    //`tp` in yt == `current` here
}
*/

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
    }
    else {
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
        //cout << "prev = " << current->prev << endl;
        //cout << "next = " << current->next << endl;
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
    cout << "Enter your reply: ";
    getline(cin, reply);
    feedback->reply_content = reply;
    time_t replied_now = time(0);
    tm* replied_time = localtime(&replied_now);
    feedback->reply_time = replied_time;
    feedback->replied_admin = replied_admin;
}

int main() {
    FeedbackList fList;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    //int feedbackID, string content, tm* feedback_time, string replied_admin, string reply_content, tm* reply_time, string cust_uname
    
    fList.insertAtEnd("This is good", ltm, "", "", NULL, "Low");
    fList.insertAtEnd("Awful", ltm, "", "", NULL, "Mustard");
    fList.insertAtEnd("Satisfied", ltm, "", "", NULL, "Chilli");
    fList.insertAtEnd("Meh", ltm, "", "", NULL, "Chilli");
    
    fList.PrintList();
    
    char res;
    Feedback* current = fList.getTail();
    cout << "*****Display Feedbacks Page*****" << endl;
    while (true) {
        cout << "=====Feedback " << current->feedbackID << "=====" << endl;
        cout << current->cust_uname << " asked : " << current->content << " on " << asctime(current->feedback_time);
        if (current->replied_admin == "") {
            cout << "No admin has replied yet." << endl;
        } else {
            cout << current->replied_admin << " replied : " << current->reply_content << " on " << asctime(current->reply_time);
        }
        cout << "====================" << endl;
        cout << "Choose your actions:" << endl;
        cout << "0. Read previous feedback" << endl;
        cout << "1. Read next feedback" << endl;
        cout << "2. Reply to this feedback" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter the number: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '0') {
            current = fList.MoveBackAndForth(current, res);
        }
        else if (res == '1') {
            current = fList.MoveBackAndForth(current, res);     
        } else if (res == '2') {
            fList.Reply(current, "Admin01");
        } else if (res == '3') {
            cout << "Going back to main page..." << endl;
            break;
        } else {
            cout << "Invalid input, please try again!" << endl;
        }
    }
    
    return 0;
}