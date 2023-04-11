#include <iostream>
#include <ctime>

using namespace std;

int main() {
    //current time of the system
    time_t now = time(0);
    // convert it to string
    string dt = ctime(&now);
    cout << "dt = " << dt << endl;
    /*
    cout << "******************gmtime()******************" << endl;
    //convert now to tm struct for UTC
    tm* gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout << "The UTC date and time is : " << dt << endl;
    cout << gmtm -> tm_hour << endl;
    cout << gmtm ->tm_min << endl;

    string dt2 = dt;
    dt2[0] = 'x';
    dt2[1] = 'x';
    dt2[2] = 'x';
    cout << "The UTC date and time is : " << dt2 << endl << endl;
    */
    cout << "******************localtime()******************" << endl;
    tm* ltm = localtime(&now); //get the structure, can access its attributes
    string ltm_str = asctime(ltm);
    cout << "localtime() date and time is : " << ltm_str << endl;
    cout << ltm -> tm_hour << endl;
    cout << ltm << endl;

    tm* y2k = new tm;
    cout << "y2k = " << y2k << endl;
    /*
    tm_mon = 0 (Jan), 1 (Feb), 2(March), ...
    tm_year = 0 (1900), 1(1901), ...
    */
    y2k->tm_hour = 0;   y2k->tm_min = 0; y2k->tm_sec = 0;
    y2k->tm_year = 0; y2k->tm_mon = 0; y2k->tm_mday = 1; 
    string date1 = asctime(y2k);
    cout << "date1 = " << date1 << endl;
    delete y2k;
    cout << "y2k->tm_mon = " << y2k->tm_mon << endl;



    
    
    return 0;
}