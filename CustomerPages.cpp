#include "CustomerPages.h"

void CustHomePage(string uname, SavedUniList* savedUniList, UniArray* uniArray) {
    char res;
    bool invalid_input = false;
    while (true) {
        if (!invalid_input) {
            system("cls");
        } 
        cout << "**********Customer Home Page**********" << endl;
        cout << "0. Log out" << endl;
        cout << "1. Sort universities in descending order based on AR score, FSR score, and ER score" << endl;
        cout << "2. Search universities based on AR score, FSR score, or ER score" << endl;
        cout << "3. Save favourite universities" << endl;
        cout << "4. Send feedbacks" << endl;
        cout << "5. Read feedbacks histories" << endl;
        cout << "6. Check and delete favourite universities" << endl;
        cout << "8. Check SavedUniList (yet to be deleted)" << endl;
        cout << "Enter your action: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '0') {
            invalid_input = false;
            return;
        } else if (res == '1') {
            SortUni();
            invalid_input = false;
        } else if (res == '2') {
            
            invalid_input = false;
        } else if (res == '3') {
            SaveUni(uniArray, savedUniList, uname);
            invalid_input = false;
        } else if (res == '4') {
            
            invalid_input = false;
        } else if (res == '5') {
            
            invalid_input = false;
        } else if (res == '6') {
            CheckAndDeleteFavUni(uname, savedUniList);
            invalid_input = false;
        } else if (res == '7') {
            
            invalid_input = false;
        } else if (res == '8') {
            CheckSavedUniList(savedUniList);  
            invalid_input = false;
        } else {
            cout << "Invalid input, please try again!" << endl;
            invalid_input = true; 
        }
    }       
}

void CheckSavedUniList(SavedUniList* savedUniList) {
    system("cls");
    savedUniList->PrintList();
    char anything;
    cout << "Input anything to quit: ";
    cin >> anything;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SortUni() {
    system("cls");
    cout << "Here is a list of sorted unis in descending order: " << endl;
    cout << "balblabllla..." << endl;
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

void SendFeedback() {
    system("cls");
    string feedback;
    cout << "**********Send Feedback Page**********" << endl;
    cout << "Send a feedback to consult further information about the universities, enter Q to quit: ";
    getline(cin, feedback);
}

void SaveUni(UniArray* uniArray, SavedUniList* savedUniList, string cus_uname) {
    system("cls");
    char res;
    string ID_uni_str;
    string saved_uni_name;
    int ID_uni;
    cout << "**********Displaying All Universities Information**********" << endl;
    cout << "| Rank | Uni_name | Location | Location_code |" << endl;
    for (int i = 0; i < 20; i++) {
        cout << i + 1<< ". "<< uniArray->getUniversity(i).rank << ", ";
        cout << uniArray->getUniversity(i).inst_name << ", ";
        cout << uniArray->getUniversity(i).loc << ", ";
        cout << uniArray->getUniversity(i).loc_code << endl;
    }
    while (true) {
        cout << "Select an action: " << endl;
        cout << "1. Check previous 20 universities" << endl;
        cout << "2. Check next 20 universities" << endl;
        cout << "3. Save university" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter the corresponding number: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '1') {
            uniArray->PrintTwentyUnis(res);
        } else if (res == '2'){
            uniArray->PrintTwentyUnis(res);
        } else if (res == '3'){
            while (true) { 
                cout << "Enter the ID of university you want to save, enter Q to quit: ";
                cin >> ID_uni_str;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (ID_uni_str == "Q") {
                    break;
                }

                try {
                    ID_uni = stoi(ID_uni_str);
                } catch (const std::invalid_argument& ia) {
                    cout << "Invalid input, please try again! Exception thrown!" << endl;
                    continue;
                }

                ID_uni--;
                if (ID_uni >= uniArray->getMaxSize() || ID_uni < 0) {
                    cout << "Invalid input, please try again! Out of bound!" << endl;
                    continue;
                }

                saved_uni_name = uniArray->getUniversity(ID_uni).inst_name;
                if (savedUniList->UniWasSaved(cus_uname, saved_uni_name)) {
                    cout << "The university was saved before!" << endl;
                } else {
                    savedUniList->insertAtEnd(saved_uni_name, cus_uname);
                    cout << "Saved the university " << saved_uni_name << " successfully!" << endl;
                }  
            }
        } else if (res == '4'){
            uniArray->setIndexOfFirstUniOnPrint(0);
            return;
        } else {
            cout << "Invalid action, please try again." << endl;
        }
    }
}

void CheckAndDeleteFavUni(string cust_uname, SavedUniList* savedUniList) {
    system("cls");
    char res;
    string ID_uni_str;
    int ID_uni;
    SavedUniRec* current_saved_uni_rec = savedUniList->getHead();
    char anything;
    int current_index = 0; // for traversing SavedUniList
    cout << "**********Saved Universities Page**********" << endl;
    // create a singly linked list to store all those pointers to those saved uni by the customer
    FavUniList* favUniList = new FavUniList;
    while (current_saved_uni_rec != NULL) {
        if (current_saved_uni_rec->cust_uname == cust_uname) {
            favUniList->insertAtEnd(current_saved_uni_rec);
        }
        current_saved_uni_rec = current_saved_uni_rec->next;
    }
    favUniList->PrintList();
    bool deleted_favUni = false;
    while (true) {
        if (deleted_favUni) {
            system("cls");
            cout << "**********Saved Universities Page**********" << endl;
            favUniList->PrintList();
            deleted_favUni = false;
        }
        cout << "Select an action: " << endl;
        cout << "1. Delete a saved university" << endl;
        cout << "2. Quit" << endl;
        cout << "Enter the corresponding number: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '1') {
            while (true) {
                cout << "Enter the ID of saved university you want to delete, enter Q to quit: ";
                cin >> ID_uni_str;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (ID_uni_str == "Q") {
                    break;
                }

                try {
                    ID_uni = stoi(ID_uni_str);
                } catch (const std::invalid_argument& ia) {
                    cout << "Invalid input, please try again! Exception thrown!" << endl;
                    continue;
                }

                ID_uni--;
                if (ID_uni >= favUniList->getLength() || ID_uni < 0) {
                    cout << "Invalid input, please try again! Out of bound!" << endl;
                    continue;
                } else {
                    cout << "ID_uni = " << ID_uni << endl;
                    cout << "Deleted uni " << favUniList->getUniName(ID_uni) << endl;
                    savedUniList->DeleteSavedUni(favUniList->getUniName(ID_uni), cust_uname);
                    favUniList->deleteFavUni(ID_uni); 
                    
                    deleted_favUni = true;
                    cout << "Deleted the saved university successfully!" << endl;
                    cout << "Enter anything to continue..." << endl;
                    cin >> anything;
                    break;
                }
                
            }
        } else if (res == '2') {
            delete favUniList; /////////////////////////////////////
            return;
        } else {
            cout << "Invalid action, please try again." << endl;
        }
    }
    
    // the singly linked list must have a destructor method to release all its heap memory after this function.

    // implement a method in SavedUniList, which takes pointer of the uni, and delete the saved uni from the SavedUniList.cpp
}