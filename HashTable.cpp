#include "HashTable.h"

InactiveCustsList::InactiveCustsList() {
    head = NULL;
    tail = NULL;
}

void InactiveCustsList::append(string uname) {
    if (head == NULL) {
        InactiveCust* newnode = new InactiveCust;
        newnode->uname = uname;
        newnode->next = NULL;
        head = newnode;
        tail = newnode;
    } else {
        InactiveCust* newnode = new InactiveCust;
        newnode->uname = uname;
        newnode->next = NULL;
        tail->next = newnode;
        tail = newnode;
    }
}

InactiveCust* InactiveCustsList::getHead() {
    return head;
}

InactiveCustsList::~InactiveCustsList() {
    InactiveCust* current = head;
    InactiveCust* delete_node = NULL;
    if (head != NULL) {
        while (current != NULL) {
            delete_node = current;
            current = current->next;
            //cout << "Deleting node = " << delete_node->uname << "....." << endl;
            delete delete_node;
        }
    }
}

// for debugging purposes
void InactiveCustsList::printInactiveCusts() {
    if (head == NULL) {
        cout << "No inactive customers so far!" << endl;
        return;
    }
    InactiveCust* current = head;
    int index = 1;
    while (current != NULL) {
        cout << index << ". " << current->uname << endl;
        current = current->next;
        index++;
    }
    //cout << "| head = " << head->uname << ", tail = " << tail->uname;
    cout << endl;
}

Hash_Table::Hash_Table(tm* default_time){
    for (int i=0; i<tableSize; i++) {
        HashTable[i] = new UserAcc;
        HashTable[i]->uname = "empty";
        HashTable[i]->password = "empty";
        HashTable[i]->last_active_time = default_time;
        HashTable[i]->next = NULL;
    }
}

//Hash function
int Hash_Table::Hash(string key) {
    int hash_sum = 0;
    int index;
    for (int i=0; i<key.length(); i++) {
        hash_sum = hash_sum + (int) key[i];
    }
    index = hash_sum % tableSize;
    return index;
}

int Hash_Table::getTableSize() {
    return tableSize;
}

UserAcc* Hash_Table::getBucketAtIndex(int index) {
    return HashTable[index];
}

void Hash_Table::AddUserAcc(string uname, string password, tm* last_active_time){
    int index = Hash(uname);
    if (HashTable[index]->uname == "empty") {
        HashTable[index]->uname = uname;
        HashTable[index]->password = password;
        HashTable[index]->last_active_time = last_active_time;
    }else {
        //here is for solving hash collision, append nodes to the linked lists on the bucket
        UserAcc* ptr = HashTable[index];
        UserAcc* n = new UserAcc;
        n->uname = uname;
        n->password = password;
        n->last_active_time = last_active_time;
        n->next = NULL;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = n;
    }
};

int Hash_Table::NumberOfUserAccInIndex(int index){
    int count = 0;
    if (HashTable[index]->uname == "empty"){
        return count;
    }
    UserAcc* ptr = HashTable[index];
    while(ptr->next != NULL) {
        ptr = ptr->next;
        count++;
    }
    count++;
    return count;
};

void Hash_Table::PrintTable(){
    int number;
    for (int i=0; i<tableSize; i++) {
        number = NumberOfUserAccInIndex(i);
        cout << "-----------------------------" << endl;
        cout << "First user acc at index = " << i << endl;
        cout << HashTable[i]->uname << endl;
        cout << HashTable[i]->password << endl;
        cout << tm2string(HashTable[i]->last_active_time) << endl;
        cout << "# of total user accs at index "<< i << " = " << number << endl;
        cout << "-----------------------------" << endl;
    }
};

void Hash_Table::PrintUserAccInIndex(int index){
    cout << "----------START--------------" << endl;
    cout << "User Acc 1 at index = " << index << endl;
    cout << HashTable[index]->uname << endl;
    cout << HashTable[index]->password << endl;
    cout << tm2string(HashTable[index]->last_active_time) << endl;
    cout << endl;
    int count = 2;
    UserAcc* ptr = HashTable[index];
    while (ptr->next != NULL) {
        ptr = ptr -> next;
        cout << "UserAcc " << count << " at index = " << index << endl;
        cout << ptr->uname << endl;
        cout << ptr->password << endl;
        cout << tm2string(ptr->last_active_time) << endl;
        cout << endl;
        count++;
    }
    cout << "-----------END-------------" << endl << endl;
};

string Hash_Table::SearchForUname(string uname){
    int index = Hash(uname);
    int found = 0;
    UserAcc* ptr = HashTable[index];
    string pwd;
    while (ptr != NULL){
        if (ptr->uname == uname) {
            found = 1;
            pwd = ptr -> password;
            break;
        }
        ptr = ptr->next;
    }

    if (!found) {
        return "NULL";
    } else {
        return pwd;
    }
};

int Hash_Table::UpdatePwd(string uname){
    string new_pwd;
    int index = Hash(uname);
    int found = 0;
    UserAcc* ptr = HashTable[index];
    string pwd;
    while (ptr != NULL){
        if (ptr->uname == uname) {
            found = 1;
            cout << "Enter new password: ";
            cin >> new_pwd;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ptr->password = new_pwd;
            cout << "Password has been updated successfully!" << endl;
            break;
        }
        ptr = ptr->next;
    }
    return found;
}

void Hash_Table::UpdateLastActive(string uname, tm* last_active_time){
    int index = Hash(uname);
    int found = 0;
    UserAcc* ptr = HashTable[index];
    string pwd;
    while (ptr != NULL){
        if (ptr->uname == uname) {
            found = 1;
            pwd = ptr -> password;
            break;
        }
        ptr = ptr->next;
    }

    if (!found) {
        cout << "Username not found!" << endl;
    } else {
        tm* temp = ptr->last_active_time;
        delete temp;
        ptr->last_active_time = last_active_time;
    }
};

void Hash_Table::RemoveUserAcc(string uname){
    tm* default_time = new tm;
    default_time->tm_hour = 0;   default_time->tm_min = 0; default_time->tm_sec = 0;
    default_time->tm_year = 0; default_time->tm_mon = 0; default_time->tm_mday = 1;
    int index = Hash(uname);
    UserAcc* delPtr;
    UserAcc* P1;
    UserAcc* P2;
    //Case 0 - bucket is empty
    if (HashTable[index] -> uname == "empty" && HashTable[index] -> uname == "empty") {
        cout << uname << " wasn't found in the Hash Table!" << endl;
    }
    //Case 1 - only 1 item contained in bucket and that item has matching name
    else if (HashTable[index] -> uname == uname && HashTable[index] -> next == NULL) {
        HashTable[index] -> uname = "empty";
        HashTable[index] -> password = "empty";
        tm* temp = HashTable[index] -> last_active_time;
        delete temp;
        HashTable[index] -> last_active_time = default_time;
    }
    //Case 2 - match is located in the first item in the bucket but there aremore items in the bucket
    else if (HashTable[index] -> uname == uname) {
        delPtr = HashTable[index]; 
        HashTable[index] = HashTable[index] -> next;
        delete delPtr;
    }
    //Case 3 - Bucket contains items but first item is not a match
    else {
        P1 = HashTable[index] -> next;
        P2 = HashTable[index];
        while (P1 != NULL && P1 -> uname != uname) {
            P2 = P1;
            P1 = P1 -> next;
        }
        //Case 3.1 - no match
        if (P1 == NULL) {
            cout << uname << " wasn't found in the Hash Table!" << endl;
        }
        //Case 3.2 - match is found 
        else {
            delPtr = P1;
            P1 = P1 -> next;
            P2 -> next = P1;
            delete delPtr;
        }
    }   
};

void Hash_Table::PrintUserAccsInTableForm() {
    UserAcc* current = NULL;
    bool printed = false;
    for (int i=0; i<tableSize; i++) {
        if (HashTable[i]->uname != "empty") {
            cout <<  "|" << HashTable[i]->uname << string(16 - HashTable[i]->uname.length(), ' ');
            cout << "|" << HashTable[i]->password << string(16 - HashTable[i]->password.length(), ' ');
            cout << "|" << tm2string(HashTable[i]->last_active_time) << string(21 - tm2string(HashTable[i]->last_active_time).length(), ' ')  << "|" << endl;
            printed = true;
            current = HashTable[i]->next;
            while (current != NULL) {
                cout <<  "|" << current->uname << string(16 - current->uname.length(), ' ');
                cout << "|" << current->password << string(16 - current->password.length(), ' ');
                cout << "|" << tm2string(current->last_active_time) << string(21 - tm2string(current->last_active_time).length(), ' ') << "|" << endl;
                current = current-> next;
            }
            current = NULL;
        } else {
            continue;
        }
    }
    if (!printed) {
        cout << "Hash Table is empty!" << endl;
    }
}