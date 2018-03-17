// CS 3377.0W1 Programming Assignment 2
// zxv160130
// Zoraida Vences
//
// This program will receive multiple lines from input
// in addition to one of three options: -d, -f, or -b.
// If the option was -d it displays the input line that has the word 'directories'.
// If the option was -f it displays the input line that has the word 'files'.
// If the option was -b it displays the input line that has the word 'bytes'.


#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// function returns the line where
    // selected option appears
string findString(vector<string> lines, string option){
    // variables
    stringstream ss();
    char delim(' ');
    string str2;
    string result;

    // checks all lines for keyword
    for (unsigned int i = 0; i < lines.size(); i++){
        stringstream ss(lines[i]);

        // separates words by spaces, checks them for the keywords
        while (getline(ss, str2, delim))
        {
            if (str2.find("directories") != string::npos && option == "-d")
            {
                return lines[i];
            }
            else if (str2.find("files") != string::npos && option == "-f")
            {
                return lines[i];
            }
            else if (str2.find("bytes") != string::npos && option == "-b")
            {

                return lines[i];
            }
            else if (option != "-f" && option != "-b" && option != "-d")
            {
                // returns warning for incorrect option input
                result = "That option does not exist: " + option;
            }
            else
            {
                // returns warning if keyword not found
                result = "Could not find keyword anywhere";
            }
        }
    }
    // returns warnings
    return result;
}

int main(int argc, char* argv[])
{
    // variables
    vector<string> lines = vector<string>();
    string str1;
    string option;

    // determines whether argument is passed
        // during execution or after
    if (argc >= 2){
        option = argv[1];
    }
    else{
        getline(cin, option);
    }

    // reads the 3 lines necessary to find keyword
    while(lines.size() < 3){
        getline(cin, str1);
        lines.push_back(str1);
    }

    // display results
    string display;
    display = findString(lines, option);

    cout << display << endl;


}
