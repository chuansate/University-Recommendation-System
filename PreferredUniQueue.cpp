#include "PreferredUniQueue.h"

PreferredUniQueue::PreferredUniQueue() {
    head = NULL;
}

PreferredUniQueue::~PreferredUniQueue() {
    PreferredUni* current = head;
    PreferredUni* delete_node = NULL;
    if (head != NULL) {
        while (current != NULL) {
            delete_node = current;
            current = current->next;
            cout << "Deleting node = " << delete_node->uniname << "....." << endl;
            delete delete_node;
        }
    }
}

PreferredUni* PreferredUniQueue::createNewNode(string uniname, int count) {
    PreferredUni* newnode = new PreferredUni;
    newnode->uniname = uniname;
    newnode->count = count;
    newnode->next = NULL;
    return newnode;
}

void PreferredUniQueue::push(string uniname, int count) {
    PreferredUni* newnode = createNewNode(uniname, count); 
    //newnode == temp
    if (head == NULL) {
        head = newnode;
        return;
    }
    PreferredUni* current = head;// current == start
    if (head->count < newnode->count) {
        newnode->next = head;
        head = newnode;
    } else {
        while (current->next != NULL && current->next->count >= newnode->count) {
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }
}

void PreferredUniQueue::printQueue() {
    if (head == NULL) {
        cout << "No one has saved universities so far!" << endl;
        return;
    }
    PreferredUni* current = head;
    int index = 1;
    cout << "|  No. |" << string(36, ' ') << "University" << string(36, ' ') << "|No. of Saves|"<< endl;

    while (current != NULL) {
        cout << "|" << index << string(6 - to_string(index).length(), ' ') << "|" << current->uniname << string(82 - current->uniname.length(), ' ') << "|" << current->count << string(12 - to_string(current->count).length(), ' ') << "|" << endl;
        current = current->next;
        index++;
    }
    cout << endl;
}