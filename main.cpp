#include <iostream>
#include <limits>
#include "HashTable.h"
#include "RedBlackTree.h"
#include "CustomerPages.h"
#include "AdminPages.h"
#include "FeedbackList.h"
#include "UniArray.h"
#include "SavedUniList.h"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <string> 
using namespace std::chrono;
using namespace std;

tm* default_time = new tm;
string tm2string(tm* time) {
    string hour = to_string(time->tm_hour);
    string min = to_string(time->tm_min);
    string sec = to_string(time->tm_sec);
    string year = to_string(time->tm_year + 1900);
    string month = to_string(time->tm_mon + 1);
    string day = to_string(time->tm_mday);
    return day + "/" + month + "/" + year + "-"  + hour + ":" + min + ":" + sec; 
}

void DisplayUniInfo(UniArray* uniArray) {
    system("cls");
    char res;
    cout << "**********Displaying All Universities Information**********" << endl;
    cout << "| Rank | Uni_name | Location | Location_code |" << endl;
    for (int i = 0; i < 20; i++) {
        cout << i + 1 << ". "<< uniArray->getUniversity(i).rank << ", ";
        cout << uniArray->getUniversity(i).inst_name << ", ";
        cout << uniArray->getUniversity(i).loc << ", ";
        cout << uniArray->getUniversity(i).loc_code << endl;
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

void SearchIndividualUni(RedBlackTree* rbt, UniArray* uniArray) {
    string uni_name;
    system("cls");
    cout << "**********Search University Page**********" << endl;
    while (true) {
        cout << "Enter the university name, enter Q to quit: ";
        getline(cin, uni_name);
        if (uni_name == "Q") {
            return;
        }
        auto start_rbt_search = high_resolution_clock::now();
        NodePtr uni_ptr = rbt->searchTree(uni_name);
        auto stop_rbt_search = high_resolution_clock::now();
        long long duration_rbt_search = duration_cast<microseconds>(stop_rbt_search - start_rbt_search).count();
        auto startTime = std::chrono::high_resolution_clock::now();
        int index = uniArray->binarySearch(uni_name, 0, uniArray->getSize() - 1);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration_bin_search = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        if (uni_ptr == rbt->getTNULL() && index == -1) { // UNI NOT FOUND
            cout << "The university is not found, please try again!" << endl;
        } else {
            cout << "Red Black Tree Search took " << duration_rbt_search << " microseconds." << endl;
            cout << "The university has been found! Here are the informations about the university:" << endl;
            // NEED SOME DECORATIONS WHILE DISPLAYING INFO ABT UNI
            cout << "Rank = " << uni_ptr->univ.rank << endl;
            cout << "Name = " << uni_ptr->univ.inst_name << endl;
            cout << "Location code = " << uni_ptr->univ.loc_code << endl << endl;

            cout << "Binary Search took " << duration_bin_search << " microseconds." << endl;
            cout << "The university has been found! Here are the informations about the university:" << endl;
            // NEED SOME DECORATIONS WHILE DISPLAYING INFO ABT UNI
            cout << "Rank = " << uniArray->getUniversity(index).rank << endl;
            cout << "Name = " << uniArray->getUniversity(index).inst_name << endl;
            cout << "Location code = " << uniArray->getUniversity(index).loc_code << endl << endl;    
        }
    }
}

void RegisterAsCustomer(Hash_Table* cus_acc_hs) {
    system("cls");
    time_t now = time(0);
    tm* current_time = localtime(&now);
    cout << "**********Register Page**********" << endl;
    string uname;
    string pwd;
    cout << "Enter your username: ";
    cin >> uname;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter your password: ";
    cin >> pwd;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cus_acc_hs->AddUserAcc(uname, pwd, current_time);
    char res;
    while (true) {
        cout << "Registered successfully! Enter Q to quit: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (res == 'Q') {
            return;
        } else {
            cout << "Invalid input, please try again!" << endl;
        }
    }
}

void LoginAsAdmin(Hash_Table* admin_acc_hs, FeedbackList* fList, Hash_Table* cus_acc_hs) {
    system("cls");
    time_t now;
    tm* current_time;
    tm* new_current_time = new tm;
    cout << "**********Admin Login Page**********" << endl;
    string uname;
    string pwd;
    string pwd_real;
    bool log_out = false;
    while (true) {
        if (log_out) {
            break;
        }
        cout << "Enter your username: ";
        cin >> uname;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pwd_real = admin_acc_hs->SearchForUname(uname);
        if (pwd_real == "NULL") {
            cout << "Username not found. Please try again!" << endl;
        } else {
            while (true) {
                cout << "Enter your password: ";
                cin >> pwd;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (pwd == pwd_real) {
                    now = time(0);
                    current_time = localtime(&now);
                    new_current_time->tm_hour = current_time->tm_hour;
                    new_current_time->tm_min = current_time->tm_min;
                    new_current_time->tm_sec = current_time->tm_sec;
                    new_current_time->tm_year = current_time->tm_year;
                    new_current_time->tm_mon = current_time->tm_mon;
                    new_current_time->tm_mday = current_time->tm_mday;
                    cus_acc_hs->UpdateLastActive(uname, new_current_time);
                    AdminHomePage(uname, fList, cus_acc_hs);
                    log_out = true;
                    break;
                } else {
                    cout << "Wrong password. Please try again!" << endl;
                } 
            }   
        }
    }
}

void LoginAsCust(Hash_Table* cus_acc_hs, SavedUniList* savedUniList, UniArray* uniArray) {
    system("cls");
    time_t now;
    tm* current_time;
    tm* new_current_time = new tm; 
    cout << "**********Customer Login Page**********" << endl;
    string uname;
    string pwd;
    string pwd_real;
    bool log_out = false;
    while (true) {
        if (log_out) {
            break;
        }
        cout << "Enter your username: ";
        cin >> uname;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pwd_real = cus_acc_hs->SearchForUname(uname);
        if (pwd_real == "NULL") {
            cout << "Username not found. Please try again!" << endl;
        } else {
            while (true) {
                cout << "Enter your password: ";
                cin >> pwd;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (pwd == pwd_real) {
                    ///  NEW
                    now = time(0);
                    current_time = localtime(&now);
                    new_current_time->tm_hour = current_time->tm_hour;
                    new_current_time->tm_min = current_time->tm_min;
                    new_current_time->tm_sec = current_time->tm_sec;
                    new_current_time->tm_year = current_time->tm_year;
                    new_current_time->tm_mon = current_time->tm_mon;
                    new_current_time->tm_mday = current_time->tm_mday;
                    cus_acc_hs->UpdateLastActive(uname, new_current_time);
                    //  NEW
                    CustHomePage(uname, savedUniList, uniArray);  
                    log_out = true;
                    break;
                } else {
                    cout << "Wrong password. Please try again!" << endl;
                } 
            }   
        }   
    }
}

void performBinarySearch(UniArray* uniArray, string targetName) {
    auto startTime = std::chrono::high_resolution_clock::now();
    int index = uniArray->binarySearch(targetName, 0, uniArray->getSize() - 1);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    if (index != -1) {
        std::cout << "University found at index: " << index << std::endl;
    } else {
        std::cout << "University not found." << std::endl;
    }
    std::cout << "Binary search took " << duration << " microseconds." << std::endl;
}

void performQuickSort(UniArray* uniArray) {
    auto startTime = std::chrono::high_resolution_clock::now();
    uniArray->sortUniversitiesByName(0, uniArray->getSize() - 1);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    cout << "Quick sort took " << duration << " microseconds." << endl;
}

void NormalUsersHomePage(Hash_Table* cus_acc_hs, Hash_Table* admin_acc_hs, RedBlackTree* rbt, FeedbackList* fList, SavedUniList* savedUniList, UniArray* uniArray) {
    char res;
    bool invalid_input = false;
    
    while (true) {
        if (!invalid_input) {
            system("cls");
        } 
        
        cout << "**********Welcome to University Recommendation System**********" << endl;
        cout << "**********Normal User Home Page**********" << endl;
        cout << "You are now browsing the system as a normal user, select action by entering corresponding number: " << endl;
        cout << "0. Exit system" << endl;
        cout << "1. Display all universities' information" << endl;
        cout << "2. Search individual university details" << endl;
        cout << "3. Register as a customer of the education exhibition" << endl;
        cout << "4. Login as a MoHE admin" << endl;
        cout << "5. Login as a customer" << endl;
        cout << "Enter your action: ";
        cin >> res;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (res == '0') {
            cout << "Exiting system..." << endl;
            invalid_input = false;
            break;
        } else if (res == '1') {
            DisplayUniInfo(uniArray);
            invalid_input = false;
        } else if (res == '2') {
            SearchIndividualUni(rbt, uniArray);
            invalid_input = false;
        } else if (res == '3') {
            RegisterAsCustomer(cus_acc_hs);
            invalid_input = false;
        } else if (res == '4') {
            LoginAsAdmin(admin_acc_hs, fList, cus_acc_hs);
            invalid_input = false;
        } else if (res == '5') {
            LoginAsCust(cus_acc_hs, savedUniList, uniArray);
            invalid_input = false;
        } else {
            cout << "Invalid input, please try again!" << endl << endl;
            invalid_input = true; 
        }    
    }
}

int main() {
    
    default_time->tm_hour = 0;   default_time->tm_min = 0; default_time->tm_sec = 0;
    default_time->tm_year = 0; default_time->tm_mon = 0; default_time->tm_mday = 1;
    Hash_Table* cus_acc_hs = new Hash_Table(default_time);
    //Initializations of data (pretending we are loading data from files...)
    /*
    tm_mon = 0 (Jan), 1 (Feb), 2(March), ...
    tm_year = 0 (1900), 1(1901), ...
    */
    tm* date1 = new tm; tm* date2 = new tm; tm* date3 = new tm; tm* date_1 = new tm; tm* date_2 = new tm;
    date1->tm_hour = 0;   date1->tm_min = 0; date1->tm_sec = 0;
    date1->tm_year = 122; date1->tm_mon = 0; date1->tm_mday = 1;
    date2->tm_hour = 13;   date2->tm_min = 28; date2->tm_sec = 34;
    date2->tm_year = 123; date2->tm_mon = 2; date2->tm_mday = 5;
    date3->tm_hour = 15;   date3->tm_min = 10; date3->tm_sec = 4;
    date3->tm_year = 123; date3->tm_mon = 2; date3->tm_mday = 6;
    date_1->tm_hour = 0;   date_1->tm_min = 0; date_1->tm_sec = 0;
    date_1->tm_year = 122; date_1->tm_mon = 0; date_1->tm_mday = 1;
    date_2->tm_hour = 0;   date_2->tm_min = 13; date_2->tm_sec = 0;
    date_2->tm_year = 122; date_2->tm_mon = 2; date_2->tm_mday = 1;
    cus_acc_hs->AddUserAcc("Low", "Low123", date1);// inactive for more than 1 year
    cus_acc_hs->AddUserAcc("Woo", "Woo456", date2);
    cus_acc_hs->AddUserAcc("Jon", "Jon@123", date3);
    cus_acc_hs->AddUserAcc("Mustard", "Must123", date_1);// inactive for more than 1 year
    cus_acc_hs->AddUserAcc("woL", "woL123", date_2);// inactive for more than 1 year

    Hash_Table* admin_acc_hs = new Hash_Table(default_time);
    tm* date4 = new tm; tm* date5 = new tm; tm* date6 = new tm;
    date4->tm_hour = 0;   date4->tm_min = 0; date4->tm_sec = 0;
    date4->tm_year = 122; date4->tm_mon = 0; date4->tm_mday = 1;
    date5->tm_hour = 13;   date5->tm_min = 28; date5->tm_sec = 34;
    date5->tm_year = 123; date5->tm_mon = 2; date5->tm_mday = 5;
    date6->tm_hour = 15;   date6->tm_min = 10; date6->tm_sec = 4;
    date6->tm_year = 123; date6->tm_mon = 0; date6->tm_mday = 6;
    admin_acc_hs->AddUserAcc("admin01", "admin123", date4);
    admin_acc_hs->AddUserAcc("admin02", "admin456", date5);
    admin_acc_hs->AddUserAcc("admin03", "admin789", date6);

    RedBlackTree* rbt = new RedBlackTree; 
    UniArray* uniArray = new UniArray(1422);
    ifstream file("2023 QS World University Rankings.csv");
    long long rbt_sort_duration = 0;

    int col_index = 0;
    string uni_data[21];
    string line, entry, temp;
    int row_count = 0;
    while (getline(file, line)) {
        col_index = 0;
        if (row_count == 0) {// skipping row 0 of CSV, becoz it is abt col names
            row_count++;
            continue;
        }
     
        // used for breaking words
        stringstream s(line);
        while (!s.eof()) {
            getline(s, entry, ',');
            uni_data[col_index] = entry;
            col_index++;
        }

        Uni uni{uni_data[0], uni_data[1], uni_data[2], uni_data[3], uni_data[4], uni_data[5], uni_data[6], uni_data[7], uni_data[8], uni_data[9], uni_data[10], uni_data[11], uni_data[12],
        uni_data[13], uni_data[14], uni_data[15], uni_data[16], uni_data[17], uni_data[18], uni_data[19], uni_data[20]};
        uniArray->insert(uni);

        auto start_rbt_sort = high_resolution_clock::now();
        rbt->insert(uni_data[0], uni_data[1], uni_data[2], uni_data[3], uni_data[4], uni_data[5], uni_data[6], uni_data[7], uni_data[8], uni_data[9], uni_data[10], uni_data[11], uni_data[12], uni_data[13], uni_data[14], uni_data[15], uni_data[16], uni_data[17], uni_data[18], uni_data[19], uni_data[20]);
        auto stop_rbt_sort = high_resolution_clock::now();
        long long duration = duration_cast<microseconds>(stop_rbt_sort - start_rbt_sort).count();
        rbt_sort_duration = rbt_sort_duration + duration;
        row_count++;        
    }
    file.close();

    FeedbackList* fList = new FeedbackList;
    
    //int feedbackID, string content, tm* feedback_time, string replied_admin, string reply_content, tm* reply_time, string cust_uname
    tm* date7 = new tm; tm* date8 = new tm; tm* date9 = new tm; tm* date10 = new tm;
    date7->tm_hour = 1;   date7->tm_min = 20; date7->tm_sec = 10;
    date7->tm_year = 122; date7->tm_mon = 0; date7->tm_mday = 1;
    date8->tm_hour = 13;   date8->tm_min = 28; date8->tm_sec = 34;
    date8->tm_year = 122; date8->tm_mon = 2; date8->tm_mday = 5;
    date9->tm_hour = 2;   date9->tm_min = 50; date9->tm_sec = 14;
    date9->tm_year = 122; date9->tm_mon = 1; date9->tm_mday = 6;
    date10->tm_hour = 1;   date10->tm_min = 13; date10->tm_sec = 30;
    date10->tm_year = 122; date10->tm_mon = 1; date10->tm_mday = 5;

    fList->insertAtEnd("How much is tuition fee at Peking University?", date7, "", "", NULL, "Low");
    fList->insertAtEnd("Hi, may I ask something?", date8, "", "", NULL, "Woo");
    fList->insertAtEnd("When will be the campus tour of MIT?", date9, "", "", NULL, "Jon");
    fList->insertAtEnd("Where can I get the campus view of Standard Uni?", date10, "", "", NULL, "Woo");
    
    SavedUniList* savedUniList = new SavedUniList;
    savedUniList->insertAtEnd("Massachusetts Institute of Technology (MIT)", "Mustard");
    savedUniList->insertAtEnd("EPFL", "Low");
    savedUniList->insertAtEnd("Yale University", "Woo");
    savedUniList->insertAtEnd("Massachusetts Institute of Technology (MIT)", "Woo");
    savedUniList->insertAtEnd("Fudan University", "Low");
    savedUniList->insertAtEnd("Massachusetts Institute of Technology (MIT)", "Low");
    savedUniList->insertAtEnd("Fudan University", "Jon");
    savedUniList->insertAtEnd("Peking University", "Mustard");
    savedUniList->insertAtEnd("Peking University", "Low");
    savedUniList->insertAtEnd("Massachusetts Institute of Technology (MIT)", "woL");
    savedUniList->insertAtEnd("AGH University of Science and Technology", "Low");

    /* CODES TO DISPLAY TIME TAKEN FOR RED BLACK TREE TO COMPLETE SORTING */
    cout << "Sorting in Red Black Tree took " << rbt_sort_duration << " microseconds." << endl;

    /* CODES TO DISPLAY A LIST OF SORTED UNIVERSITIES, FOR CHECKING PURPOSES 
    cout << "Here is a list of sorted universities in ascending order based on names: " << endl;
    rbt.inOrderPrint();
    */
    
    performQuickSort(uniArray);
    /*CODES TO DISPLAY A LIST OF SORTED UNIVERSITIES, FOR CHECKING PURPOSES
    cout << "******************UNI ARRAY SORTED********************" << endl;
    for (int i = 0; i < uniArray.getSize(); ++i) {
        cout << uniArray.getUniversity(i).inst_name << endl;
    }    
    */ 

    char anything;
    cout << "Two sorting algorithms had been performed, input anything to continue: ";
    cin >> anything;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    NormalUsersHomePage(cus_acc_hs, admin_acc_hs, rbt, fList, savedUniList, uniArray);

    return 0;
}


