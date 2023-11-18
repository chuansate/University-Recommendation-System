#include "SavedUniList.h"

SavedUniList::SavedUniList() {
    length = 0;
    head = NULL;
    tail = NULL;
}

void SavedUniList::insertAtEnd(string saved_uni_name, string cust_uname) {
    //Initialize a new node
    SavedUniRec* newnode = new SavedUniRec;
    newnode->saved_uniname = saved_uni_name;
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

void SavedUniList::PrintList() {
    if (head == NULL) {
        cout << "List is empty!" << endl;
        return;
    }
    int length = 0;
    SavedUniRec* current = head;
    while (current != NULL) {
        cout << length << ". ";
        cout  << current->saved_uniname << ", ";
        cout << current->cust_uname << endl;
        current = current->next;
        length++;
    }
}

SavedUniRec* SavedUniList::getTail() {
    return tail;
}

// return TRUE if the uni was ady saved by the customer
// otherwise return FALSE
bool SavedUniList::UniWasSaved(string cus_uname, string saved_uni_name) {
    SavedUniRec* current = head;
    while (current != NULL) {
        if (current->cust_uname == cus_uname && current->saved_uniname == saved_uni_name) {
            return true;
        }
        current = current->next;
    }
    return false;
}

SavedUniRec* SavedUniList::getHead() {
    return head;
}

void SavedUniList::DeleteSavedUni(string saved_uni_name, string cust_uname) {
    if (head == NULL) {
        cout << "Linked list is empty, unable to delete!" << endl;
        return;
    }
    SavedUniRec* current = head;
    SavedUniRec* temp;
    SavedUniRec* temp2;
    while (current != NULL) {
        if (current->saved_uniname == saved_uni_name && current->cust_uname == cust_uname) {
            if (current->next == NULL) {
            // delete node at the end
                if (current->prev == NULL) {// length of list == 1
                    head = NULL;
                    tail = NULL;
                    delete current;
                } else { //length of list != 1
                    temp = current->prev;
                    temp->next = NULL;
                    tail = temp;
                    delete current;
                }
            } else if (current->prev == NULL) {
            // delete node at the front (no need to consider length of list anymore becoz even if length of list == 1, it will be treated as node at the end)
                head = current->next;
                head->prev = NULL;
                delete current;
            } else {
            // delete node is before node(s)
                temp = current->prev;
                temp2 = current->next;
                temp->next = temp2;
                temp2->prev = temp;
                delete current;
            }
            length--;
            return;
        }
        current = current->next;
    }
    cout << "Record not found, unable to delete!" << endl;
}

PreferredUniQueue* SavedUniList::countNumOfSavedByUni() {
    PreferredUniQueue* preuniq = new PreferredUniQueue;
    UniCount counts_by_uni[1422];
    int length = 0;
    SavedUniRec* current = head;
    bool found;
    while (current != NULL) {
        found = false;
        for (int i = 0; i < length; i++) {
            if (counts_by_uni[i].uniname == current->saved_uniname) {
                counts_by_uni[i].count++;
                found = true;
                break;
            }   
        }
        if (!found) {
            length++;
            counts_by_uni[length-1].uniname = current->saved_uniname;
            counts_by_uni[length-1].count = 1;
        }
        current = current->next;
    }

    // cout << "Before sorting (for debugging purposes): " << endl;
    // for (int i=0; i<length; i++){
    //     cout << i + 1 << ". " << counts_by_uni[i].uniname << ", " << counts_by_uni[i].count << endl;
    // }
    
    for (int i=0; i<length; i++){
        preuniq->push(counts_by_uni[i].uniname, counts_by_uni[i].count);
    }
    return preuniq;
}