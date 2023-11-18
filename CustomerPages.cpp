#include "CustomerPages.h"

void CustHomePage(string uname, SavedUniList* savedUniList, UniArray* uniArray, FeedbackList* fList) {
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
        cout << "5. Read feedbacks' replies" << endl;
        cout << "6. Check and delete favourite universities" << endl;
        cout << "Enter your action: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '0') {
            invalid_input = false;
            return;
        } else if (res == '1') {
            SortUni(uniArray);
            invalid_input = false;
        } else if (res == '2') {
            SearchUniBasedOnScores(uniArray);
            invalid_input = false;
        } else if (res == '3') {
            SaveUni(uniArray, savedUniList, uname);
            invalid_input = false;
        } else if (res == '4') {
            SendFeedback(fList, uname);
            invalid_input = false;
        } else if (res == '5') {
            ReadFeedback(fList, uname);
            invalid_input = false;
        } else if (res == '6') {
            CheckAndDeleteFavUni(uname, savedUniList);
            invalid_input = false;
        } else {
            cout << "Invalid input, please try again!" << endl;
            invalid_input = true; 
        }
    }       
}

void SortUni(UniArray* uniArray) {
    system("cls");
    if (uniArray->getSorted()) {
        cout << "The universities had been sorted before." << endl;
    } else {
        uniArray->quickSortByScoresAND(0, uniArray->getMaxSize()-1);
        cout << "The universities had been sorted in descending order based on AR score, FSR score, and ER score!" << endl;
    }
    char res;
    cout << "**********Displaying All Universities Information**********" << endl;
    cout << "|  No. |Rank|" << string(36, ' ') << "University" << string(36, ' ') << "|" << string(12, ' ') << "Location" << string(12, ' ') << "|Location Code|ARScore|FSRScore|ERScore|"<< endl;
    int length_uni_name;
    for (int i = 0; i < 20; i++) {
        cout << "|" << i + 1 << "." << string(5-to_string(i+1).length(), ' ') << "|";
        cout << uniArray->getUniversity(i).rank << string(4-uniArray->getUniversity(i).rank.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).inst_name << string(82-uniArray->getUniversity(i).inst_name.length(), ' ')<< "|";
        cout << uniArray->getUniversity(i).loc << string(32-uniArray->getUniversity(i).loc.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).loc_code << string(11, ' ') << "|";
        cout << uniArray->getUniversity(i).arcode << string(7-uniArray->getUniversity(i).arcode.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).fsrscore << string(8-uniArray->getUniversity(i).fsrscore.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).erscore << string(7-uniArray->getUniversity(i).erscore.length(), ' ') << "|" << endl;
    }
    while (true) {
        cout << "Select an action: " << endl;
        cout << "1. Check previous 20 universities" << endl;
        cout << "2. Check next 20 universities" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter the corresponding number: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '1') {
            uniArray->PrintTwentyUnis(res);
        } else if (res == '2'){
            uniArray->PrintTwentyUnis(res);
        } else if (res == '3'){
            uniArray->setIndexOfFirstUniOnPrint(0);
            return;
        } else {
            cout << "Invalid action, please try again." << endl;
        }
    }
}

void SearchUniBasedOnScores(UniArray* uniArray) {
    system("cls");
    char res;
    cout << "**********Search Universities Based on Scores**********" << endl;
    cout << "You can search for universities based on AR score, FSR score, or ER score." << endl;
    float targetAR, targetFSR, targetER;
    string filter_value;
    while (true) {
        cout << "Which filter do you want to apply? Enter Q to quit." << endl;
        cout << "1. AR score filter" << endl;
        cout << "2. FSR score filter" << endl;
        cout << "3. ER score filter" << endl;
        cout << "Enter corresponding number: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == '1') {
            while (true) {
                cout << "Enter AR score to filter: ";
                cin >> filter_value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try {
                    targetAR = stof(filter_value); 
                }catch (const std::invalid_argument& ia) {
                    cout << "Invalid inputs, try again!" << endl;  
                    continue;
                }
                if (targetAR <= 0) {
                    cout << "Scores cannot be negative, try again!" << endl;  
                    continue;
                }
                uniArray->searchUniversity(targetAR, -1, -1);
                cout << endl;
                cout << endl;
                break;
            }    
        } else if (res == '2') {
            while (true) {
                cout << "Enter FSR score to filter: ";
                cin >> filter_value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try {
                    targetFSR = stof(filter_value); 
                }catch (const std::invalid_argument& ia) {
                    cout << "Invalid inputs, try again!" << endl;  
                    continue;
                }
                if (targetFSR <= 0) {
                    cout << "Scores cannot be negative, try again!" << endl;  
                    continue;
                }
                uniArray->searchUniversity(-1, targetFSR, -1);
                cout << endl;
                cout << endl;
                break;
            } 
        } else if (res == '3') {   
            while (true) {
                cout << "Enter ER score to filter: ";
                cin >> filter_value;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try {
                    targetER = stof(filter_value); 
                }catch (const std::invalid_argument& ia) {
                    cout << "Invalid inputs, try again!" << endl;  
                    continue;
                }
                if (targetER <= 0) {
                    cout << "Scores cannot be negative, try again!" << endl;  
                    continue;
                }
                uniArray->searchUniversity(-1, -1, targetER);
                cout << endl;
                cout << endl;
                break;
            } 
        } else if (res == 'Q') {
            return;
        } else {
            cout << "Invalid inputs, try again!" << endl;
        }
    }
}

void SendFeedback(FeedbackList* fList, string uname) {
    char res;
    time_t now;
    tm* current_time;
    tm* new_current_time = new tm;
    system("cls");
    string feedback;
    cout << "**********Send Feedback Page**********" << endl;
    while (true) {
        cout << "Send a feedback to consult further information about the universities, enter Q to quit: ";
        getline(cin, feedback);
        if (feedback == "Q") {
            return;
        } else {
            now = time(0);
            current_time = localtime(&now);
            new_current_time->tm_hour = current_time->tm_hour;
            new_current_time->tm_min = current_time->tm_min;
            new_current_time->tm_sec = current_time->tm_sec;
            new_current_time->tm_year = current_time->tm_year;
            new_current_time->tm_mon = current_time->tm_mon;
            new_current_time->tm_mday = current_time->tm_mday;
            fList->insertAtEnd(feedback, new_current_time, "", "", NULL, uname);
            cout << "The feedback has been added successfully! Enter anything to quit..." << endl;
            cin >> res;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
    }
    
    
}

void ReadFeedback(FeedbackList* fList, string uname) {
    system("cls");
    cout << "**********Read Feedback Page**********" << endl;
    int feedback_index = 1;
    char res;
    cout << "The following feedbacks are displayed from latest to earliest:" << endl;
    Feedback* current_feedback = fList->getTail();
    while (current_feedback != NULL) {
        if (current_feedback->cust_uname == uname) {
            cout << "==========Feedback " << feedback_index << "==========" << endl;
            cout << current_feedback->cust_uname << " asked : " << current_feedback->content << " (on " << tm2string(current_feedback->feedback_time) << ")" << endl;
            if (current_feedback->replied_admin == "") {
                cout << "No admin has replied yet." << endl;
            } else {
                cout << current_feedback->replied_admin << " replied : " << current_feedback->reply_content << " (on " << tm2string(current_feedback->reply_time) << ")" << endl;
            }
            feedback_index++;
        }
        current_feedback = current_feedback->prev;
    }
    cout << "Enter anything to quit...";
    cin >> res;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SaveUni(UniArray* uniArray, SavedUniList* savedUniList, string cus_uname) {
    system("cls");
    char res;
    string ID_uni_str;
    string saved_uni_name;
    int ID_uni;
    cout << "**********Displaying All Universities Information**********" << endl;
    cout << "|  No. |Rank|" << string(36, ' ') << "University" << string(36, ' ') << "|" << string(12, ' ') << "Location" << string(12, ' ') << "|Location Code|ARScore|FSRScore|ERScore|"<< endl;
    int length_uni_name;
    for (int i = 0; i < 20; i++) {
        cout << "|" << i + 1 << "." << string(5-to_string(i+1).length(), ' ') << "|";
        cout << uniArray->getUniversity(i).rank << string(4-uniArray->getUniversity(i).rank.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).inst_name << string(82-uniArray->getUniversity(i).inst_name.length(), ' ')<< "|";
        cout << uniArray->getUniversity(i).loc << string(32-uniArray->getUniversity(i).loc.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).loc_code << string(11, ' ') << "|";
        cout << uniArray->getUniversity(i).arcode << string(7-uniArray->getUniversity(i).arcode.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).fsrscore << string(8-uniArray->getUniversity(i).fsrscore.length(), ' ') << "|";
        cout << uniArray->getUniversity(i).erscore << string(7-uniArray->getUniversity(i).erscore.length(), ' ') << "|" << endl;
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
                    // cout << "ID_uni = " << ID_uni << endl;
                    cout << "Deleted " << favUniList->getUniName(ID_uni) << " from favourite list!" << endl;
                    savedUniList->DeleteSavedUni(favUniList->getUniName(ID_uni), cust_uname);
                    favUniList->deleteFavUni(ID_uni); 
                    
                    deleted_favUni = true;
                    cout << "Enter anything to continue..." << endl;
                    cin >> anything;
                    break;
                }
                
            }
        } else if (res == '2') {
            delete favUniList;
            return;
        } else {
            cout << "Invalid action, please try again." << endl;
        }
    }
}