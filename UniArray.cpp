#include "UniArray.h"

UniArray::UniArray(int size) {
    maxSize = size;
    uniCount = 0;
    universities = new Uni[maxSize];
    index_of_first_uni_on_print = 0;
    sorted = false;
}

UniArray::~UniArray() {
    delete[] universities;
}

void UniArray::setIndexOfFirstUniOnPrint(int index) {
    index_of_first_uni_on_print = index;
};

void UniArray::insert(const Uni& uni) {
    if (uniCount < maxSize) {
        universities[uniCount] = uni;
        uniCount++;
    }
    
}

int UniArray::getSize() const {
    return uniCount;
}

int UniArray::getMaxSize() {
    return maxSize;
}

bool UniArray::getSorted() {
    return sorted;
}

Uni UniArray::getUniversity(int index) {
    return universities[index];
}

void UniArray::sortUniversitiesByName(int left, int right) {
    if (left < right) {
        int pivotIndex = partition(left, right);
        sortUniversitiesByName(left, pivotIndex - 1);
        sortUniversitiesByName(pivotIndex + 1, right);
    }
}

int UniArray::binarySearch(string targetName, int left, int right) {
    if (right >= left) {
        int middle = left + (right - left) / 2;

        if (universities[middle].inst_name == targetName)
            return middle;

        if (universities[middle].inst_name > targetName)
            return binarySearch(targetName, left, middle - 1);
            
        return binarySearch(targetName, middle + 1, right);
    }
    return -1;
}

int UniArray::partition(int left, int right) {
    Uni pivot = universities[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
        if (universities[j].inst_name <= pivot.inst_name) {
            i++;
            customSwap(universities[i], universities[j]);
        }
    }

    customSwap(universities[i + 1], universities[right]);
    return i + 1;
}

void UniArray::PrintTwentyUnis(char action) {
    if (action == '1') {
        if (index_of_first_uni_on_print == 0) {
            cout << "There is no more preceeding universities!" << endl;
            return;
        }
        index_of_first_uni_on_print -= 20;
    } else if (action == '2') {
        if (index_of_first_uni_on_print + 20 > maxSize) {
            cout << "There is no more following universities!" << endl;
            return;
        }
        index_of_first_uni_on_print += 20;
    }
    system("cls");
    cout << "**********Displaying All Universities Information**********" << endl;
    cout << "|  No. |Rank|" << string(36, ' ') << "University" << string(36, ' ') << "|" << string(12, ' ') << "Location" << string(12, ' ') << "|Location Code|ARScore|FSRScore|ERScore|"<< endl;
    for (int i = 0; i < 20; i++) {
        if ((index_of_first_uni_on_print + i) == maxSize) {
            break;
        }
        cout << "|" << index_of_first_uni_on_print+i+1 << "." << string(5-to_string(index_of_first_uni_on_print+i+1).length(), ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].rank << string(4-universities[index_of_first_uni_on_print+i].rank.length(), ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].inst_name << string(82-universities[index_of_first_uni_on_print+i].inst_name.length(), ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].loc << string(32-universities[index_of_first_uni_on_print+i].loc.length(), ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].loc_code << string(11, ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].arcode << string(7-universities[index_of_first_uni_on_print+i].arcode.length(), ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].fsrscore << string(8-universities[index_of_first_uni_on_print+i].fsrscore.length(), ' ') << "|";
        cout << universities[index_of_first_uni_on_print+i].erscore << string(7-universities[index_of_first_uni_on_print+i].erscore.length(), ' ') << "|" << endl;
    }
}


bool UniArray::compareByScoresAND(const Uni& a, const Uni& b) {
    float a_arcode, a_fsrscore, a_erscore, b_arcode, b_fsrscore, b_erscore;
    a_arcode = stof(a.arcode);
    b_arcode = stof(b.arcode);
    a_fsrscore = stof(a.fsrscore);
    b_fsrscore = stof(b.fsrscore);
    a_erscore = stof(a.erscore);
    b_erscore = stof(b.erscore);
    if (a_arcode == b_arcode && a_fsrscore == b_fsrscore) {
        return a_erscore > b_erscore;
    }
    if (a_arcode == b_arcode) {
        return a_fsrscore > b_fsrscore;
    }
    return a_arcode > b_arcode;
}

void UniArray::quickSortByScoresAND(int left, int right) {
    if (left < right) {
        int pivotIndex = partitionByScoresAND(left, right);
        quickSortByScoresAND(left, pivotIndex - 1);
        quickSortByScoresAND(pivotIndex + 1, right);
    }
    sorted = true;
}

int UniArray::partitionByScoresAND(int left, int right) {
    Uni pivot = universities[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; j++) {
        if (compareByScoresAND(universities[j], pivot)) {
            i++;
            customSwap(universities[i], universities[j]);
        }
    }

    customSwap(universities[i + 1], universities[right]);
    return i + 1;
}

void UniArray::printSortedUniversities() {
    cout << "Universities sorted by scores:" << endl;
    cout << "No. | AR Score | FSR Score | ER Score | Uni_name " << endl;
    for (int i = 0; i < uniCount; i++) {
        Uni uni = universities[i];
        cout << i + 1 << " | " << uni.arcode << " | " << uni.fsrscore << " | " << uni.erscore << " | " << uni.inst_name << endl;
    }
}

void UniArray::linearSearchUni(float targetAR, float targetFSR, float targetER)  {
    bool found = false;
    float currentAR = 0.0, currentFSR = 0.0, currentER = 0.0;
    cout << "|  No. |Rank|" << string(36, ' ') << "University" << string(36, ' ') << "|" << string(12, ' ') << "Location" << string(12, ' ') << "|Location Code|ARScore|FSRScore|ERScore|"<< endl;
    for (int i = 0; i < maxSize; i++) {
        Uni currentUni = universities[i];
        currentAR = std::stof(currentUni.arcode);
        currentFSR = std::stof(currentUni.fsrscore);
        currentER = std::stof(currentUni.erscore);

        if (targetAR != -1 && currentAR == targetAR) {
            Uni foundUni = getUniversity(i);
            cout << "|" << i + 1 << "." << string(5-to_string(i+1).length(), ' ') << "|";
            cout << foundUni.rank << string(4-foundUni.rank.length(), ' ') << "|";
            cout << foundUni.inst_name << string(82-foundUni.inst_name.length(), ' ')<< "|";
            cout << foundUni.loc << string(32-foundUni.loc.length(), ' ') << "|";
            cout << foundUni.loc_code << string(11, ' ') << "|";
            cout << foundUni.arcode << string(7-foundUni.arcode.length(), ' ') << "|";
            cout << foundUni.fsrscore << string(8-foundUni.fsrscore.length(), ' ') << "|";
            cout << foundUni.erscore << string(7-foundUni.erscore.length(), ' ') << "|" << endl;
            found = true;
        } else if (targetFSR != -1 && currentFSR == targetFSR) {
            Uni foundUni = getUniversity(i);
            cout << "|" << i + 1 << "." << string(5-to_string(i+1).length(), ' ') << "|";
            cout << foundUni.rank << string(4-foundUni.rank.length(), ' ') << "|";
            cout << foundUni.inst_name << string(82-foundUni.inst_name.length(), ' ')<< "|";
            cout << foundUni.loc << string(32-foundUni.loc.length(), ' ') << "|";
            cout << foundUni.loc_code << string(11, ' ') << "|";
            cout << foundUni.arcode << string(7-foundUni.arcode.length(), ' ') << "|";
            cout << foundUni.fsrscore << string(8-foundUni.fsrscore.length(), ' ') << "|";
            cout << foundUni.erscore << string(7-foundUni.erscore.length(), ' ') << "|" << endl;
            found = true;
        } else if (targetER != -1 && currentER == targetER) {
            Uni foundUni = getUniversity(i);
            cout << "|" << i + 1 << "." << string(5-to_string(i+1).length(), ' ') << "|";
            cout << foundUni.rank << string(4-foundUni.rank.length(), ' ') << "|";
            cout << foundUni.inst_name << string(82-foundUni.inst_name.length(), ' ')<< "|";
            cout << foundUni.loc << string(32-foundUni.loc.length(), ' ') << "|";
            cout << foundUni.loc_code << string(11, ' ') << "|";
            cout << foundUni.arcode << string(7-foundUni.arcode.length(), ' ') << "|";
            cout << foundUni.fsrscore << string(8-foundUni.fsrscore.length(), ' ') << "|";
            cout << foundUni.erscore << string(7-foundUni.erscore.length(), ' ') << "|" << endl;
            found = true;
        }
    } // No matching university found
    if (!found) {
        cout << "No matching universities found!" << endl;
    }
}

int UniArray::binarySearchUni(float targetAR, int left, int right) {
    int middle;
    int first_index;// first uni matching that criteria
    // binary search will cut array into halves, and stop at the middle if there r multiple matched unis
    // hence once the match uni is found, needa move the index to the front until there is no more match uni
    if (left <= right) {
        middle = left + (right - left) / 2;

        if (stof(universities[middle].arcode) == targetAR) {
            first_index = middle - 1;
            while (stof(universities[first_index].arcode) == targetAR && first_index > 0) {
                if (first_index != 0) {
                    first_index--;
                }
            }
            if (first_index == 0) {
                return first_index;
            }
            first_index++;
            return first_index;
        }

        if (stof(universities[middle].arcode) > targetAR) {
            return binarySearchUni(targetAR, middle+1, right);
        }

        return binarySearchUni(targetAR, left, middle-1);
    }
    return -1;//target not found
}

void UniArray::searchUniversity(float targetAR, float targetFSR, float targetER) {
    //if the target value here is -1, it means the filter is not being applied
    int index;
    
    if (sorted && targetAR != -1) {
        // if the array has been sorted AND targetAR is the search key
        //cout << "Binary search happening..." << endl;
        index = binarySearchUni(targetAR, 0, maxSize-1);
        
        if (index != -1) {
            Uni foundUni = getUniversity(index);
            cout << "|  No. |Rank|" << string(36, ' ') << "University" << string(36, ' ') << "|" << string(12, ' ') << "Location" << string(12, ' ') << "|Location Code|ARScore|FSRScore|ERScore|"<< endl;
            while (stof(foundUni.arcode) == targetAR) {
                cout << "|" << index + 1 << "." << string(5-to_string(index+1).length(), ' ') << "|";
                cout << foundUni.rank << string(4-foundUni.rank.length(), ' ') << "|";
                cout << foundUni.inst_name << string(82-foundUni.inst_name.length(), ' ')<< "|";
                cout << foundUni.loc << string(32-foundUni.loc.length(), ' ') << "|";
                cout << foundUni.loc_code << string(11, ' ') << "|";
                cout << foundUni.arcode << string(7-foundUni.arcode.length(), ' ') << "|";
                cout << foundUni.fsrscore << string(8-foundUni.fsrscore.length(), ' ') << "|";
                cout << foundUni.erscore << string(7-foundUni.erscore.length(), ' ') << "|" << endl;
                index++;
                foundUni = getUniversity(index);
            }
        } else {
            cout << "No university found with the given search criteria." << endl;
        }
    } else {
        //otherwise use linear search
        //cout << "Linear search happening..." << endl;
        linearSearchUni(targetAR, targetFSR, targetER);
    }
}

template <typename T>

void UniArray::customSwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


















