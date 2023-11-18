#include "AdminPages.h"
#include "HashTable.h"
void AdminHomePage(string uname, FeedbackList* fList, Hash_Table* cus_acc_hs, SavedUniList* savedUniList) {
    char res;
    bool invalid_input = false;
    while (true) {
        if (!invalid_input) {
            system("cls");
        } 
        cout << "**********Admin Home Page**********" << endl;
        cout << "0. Log out" << endl;
        cout << "1. Display all customers' details" << endl;
        cout << "2. Modify a customer's details" << endl;
        cout << "3. Delete inactive customers' accounts" << endl;
        cout << "4. Read and reply feedbacks (move back and forth)" << endl;
        cout << "5. Summarize top universities" << endl;
        cout << "Enter your action: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '0') {
            invalid_input = false;
            return;
        } else if (res == '1') {
            DisplayUserDetails(cus_acc_hs);
            invalid_input = false;
        } else if (res == '2') {
            ModifyCustDetails(cus_acc_hs);
            invalid_input = false;
        } else if (res == '3') {
            DeleteCustAcc(cus_acc_hs);
            invalid_input = false;
        } else if (res == '4') {
            Read_ReplyFeedbacks(fList, uname);
            invalid_input = false;
        } else if (res == '5') {
            SummarizeTopUniPage(savedUniList);
        } else {
            cout << "Invalid input, please try again!" << endl;
            invalid_input = true; 
        }
    }       
}

void DisplayUserDetails(Hash_Table* cus_acc_hs) {
    system("cls");
    cout << "**********Customers' Details**********" << endl;
    cout << "|    Username" << string(4, ' ') << "|    Password" << string(4, ' ') << "|     Last Active     |" << endl;
    cus_acc_hs->PrintUserAccsInTableForm();
    char res;
    while (true) {    
        cout << "Enter Q to quit: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == 'Q') {
            return;
        } else {
            cout << "Invalid input, please try again!" << endl;
        }
    }
}

void ModifyCustDetails(Hash_Table* cus_acc_hs) {
    int found = 0; // not found
    char res;
    system("cls");
    cout << "*****Modify Customers' Details Page*****" << endl;
    string uname;
    while (true) {
        cout << "Enter the username of the customer you want to modify his/her password: ";
        cin >> uname;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        found = cus_acc_hs->UpdatePwd(uname);
        if (found) {
            while (true) {
                cout << "Enter Q to quit: ";
                cin >> res;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (res == 'Q') {
                    return;
                } else {
                    cout << "Invalid input, please try again!" << endl;
                }
            }  
        } else {
            cout << "Could not find the username of the customer, please try again!" << endl;
        }
    }
}

void DeleteCustAcc(Hash_Table* cus_acc_hs) {
    system("cls");
    // Hash_Table must have a method to traverse thru whole table and return address of customer who has been inactive of 1 year, append it to the linked list
    // return NULL once whole table has been traversed completely. stop the WHILE loop.
    // since we needa list out, hence we need linked list to store all users who has been inactive for 1 year 
    // (the linked list shud have a method to delete all its allocated heap memory after this function).
    // display each user, and ask if admin wanna proceed to delete all of them. If yes, then call RemoveItem(); 
    cout << "*****Delete Customers' Accounts Page*****" << endl;
    char res;
    InactiveCustsList* inactiveLi = new InactiveCustsList;
    UserAcc* current = NULL;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int diff_year;
    int diff_month;
    for (int i=0; i<cus_acc_hs->getTableSize(); i++) {
        // traverse thru each bucket
        current = cus_acc_hs->getBucketAtIndex(i);
        if (current->uname != "empty") {
            diff_year = ltm->tm_year - current->last_active_time->tm_year;
            diff_month = ltm->tm_mon - current->last_active_time->tm_mon;
            //cout << "dif year = " << diff_year << endl;
            //cout << "dif mon = " << diff_month << endl;
            if ((diff_year == 1 && diff_month >= 0) || diff_year >= 2) {
                inactiveLi->append(current->uname);
            }
            // traverse thru each linked list
            current = current->next;
            while (current != NULL) {
                diff_year = ltm->tm_year - current->last_active_time->tm_year;
                diff_month = ltm->tm_mon - current->last_active_time->tm_mon;
            
                if ((diff_year == 1 && diff_month >= 0) || diff_year >= 2) {
                    inactiveLi->append(current->uname);
                }
                current = current->next;
            }
        }
    }
    while (true) {
        cout << "Here is a list of customers who have been inactive for 1 year: " << endl;
        inactiveLi->printInactiveCusts();
        if (inactiveLi->getHead() == NULL) {
            cout << "Enter anything to quit: ";
            cin >> res;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        } else {
            cout << "Are you sure you want to delete all customers who have been inactive for at least 1 year? (Y/N): ";
            cin >> res;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (res == 'Y') {
                // delete method calling here
                InactiveCust* current = inactiveLi->getHead();
                while (current != NULL) {
                    cus_acc_hs->RemoveUserAcc(current->uname);
                    current = current->next;
                }
                cout << "All customers who have been inactive for at least 1 year have been deleted successfully!" << endl;               
                /// call the destructor before exiting this function, delete allocated spaces at heap  
                delete inactiveLi;
                char res;
                cout << "Enter anything to quit: ";
                cin >> res;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            } else if (res == 'N') {
                delete inactiveLi;
                return;
            } else {
                cout << "Invalid input, please try again!" << endl;
            }
        }
        
    }
}

void Read_ReplyFeedbacks(FeedbackList* fList, string uname) {
    char res;
    Feedback* current = fList->getTail();
    system("cls");
    cout << "*****Display Feedbacks Page*****" << endl;
    while (true) {
        cout << "=====Feedback " << current->feedbackID << "=====" << endl;
        cout << current->cust_uname << " asked : " << current->content << " (on " << tm2string(current->feedback_time) << ")" << endl;
        if (current->replied_admin == "") {
            cout << "No admin has replied yet." << endl;
        } else {
            cout << current->replied_admin << " replied : " << current->reply_content << " (on " << tm2string(current->reply_time) << ")" << endl;
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
            current = fList->MoveBackAndForth(current, res);
        }
        else if (res == '1') {
            current = fList->MoveBackAndForth(current, res);     
        } else if (res == '2') {
            fList->Reply(current, uname);
        } else if (res == '3') {
            cout << "Going back to main page..." << endl;
            break;
        } else {
            cout << "Invalid input, please try again!" << endl;
        }
    }
}

void SummarizeTopUniPage(SavedUniList* savedUniList) {
    char res;
    system("cls");
    cout << "*****Summarize Top Universities (Most Preferred) Page*****" << endl;
    PreferredUniQueue* preuniq = savedUniList->countNumOfSavedByUni();
    cout << "Printing queue: " << endl;
    preuniq->printQueue();
    cout << "Enter anything to quit...";
    cin >> res;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    delete preuniq;
}