#include "FavUniList.h"

FavUniList::FavUniList() {
    length = 0;
    head = NULL;
    tail = NULL;
}

FavUniList::~FavUniList() {
    FavUni* current = head;
    FavUni* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
    cout << "Deleted the whole linked list from heap!" << endl;
}

void FavUniList::insertAtEnd(SavedUniRec* saved_uni_rec) {
    //Initialize a new node
    FavUni* newnode = new FavUni;
    newnode->saved_uni_rec = saved_uni_rec;
    newnode->next = NULL;

    if (head == NULL) {// if empty list
        head = newnode;
        tail = newnode;
    } else {
        tail->next = newnode;
        tail = tail->next;   
    }
    length++;
}


void FavUniList::PrintList() {
    if (head == NULL) {
        cout << "List is empty!" << endl;
        return;
    }
    int i = 1;
    FavUni* current = head;
    while (current != NULL) {
        cout << i << ". " << current->saved_uni_rec->saved_uniname << endl;
        current = current->next;
        i++;
    }
};

FavUni* FavUniList::getTail() {
    return tail;
};

int FavUniList::getLength() {
    return length;
}

void FavUniList::deleteFavUni(int index) {
    if (head == NULL) {
        cout << "FavUniList is empty, unable to delete!" << endl;
        return;
    }
    FavUni* prev = NULL;
    FavUni* current = head;
    
    if (index == 0) {
        // deleted node is at front of list
        if (current->next != NULL) {// there is node(s) after current node
            head = current->next;
            delete current;
        } else { // there is no node after current node
            head = NULL;
            tail = NULL;
            delete current;
        }
        length--;
        return;
    }
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    if (index == length-1) {
        // deleted node is at end of list
        prev->next = NULL;
        tail = prev;
        delete current;
        length--;
        return;
    }
    //deleted node is before node(s)
    prev->next = current->next;
    delete current;
    length--;
}

string FavUniList::getUniName(int index) {
    FavUni* current = head;
    if (index == 0) {
        return current->saved_uni_rec->saved_uniname;
    }
    if (index == length - 1) {
        return tail->saved_uni_rec->saved_uniname;
    }
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->saved_uni_rec->saved_uniname;
}
