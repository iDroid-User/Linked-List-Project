#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

#include "LetterFrequency.h"

const int TESTING_LEVEL = 1;

// Add your main function here
int main()
{ 
    if (TESTING_LEVEL == 0) {
        LetterFrequencyList lfl;
        lfl.append('A');
        //lfl.insertInOrder('B');
        lfl.print();
        lfl.append('B');
        //lfl.insertInOrder('A');
        lfl.print();
        lfl.append('C');
        //lfl.insertInOrder('C');
        lfl.print();
        lfl.append('A');
        lfl.print();
    }
    else {
        ifstream inputFile;
        string infilename;

        cout << "Enter the input file name: \n";
        getline(cin, infilename);
        
        char sorted;
        cout << "Build sorted list? (y/n): \n";
        cin >> sorted;
        
        
        // Open the file.
        inputFile.open(infilename);
    
        if (!inputFile)
        {
            cout << "Failed to open " << infilename << " for reading.\n";
        }
        else 
        {
            LetterFrequencyList fileList; // class: LetterFrequencyList
            char ch;
            while (inputFile >> ch) {

                if (TESTING_LEVEL > 3) {
                    cout << "Read character " << ch << endl;
                }

                if (isalpha(ch)) {
                    ch = toupper(ch); // Capitalizes the letter to case-desensitize
                    if(sorted == 'y') {
                        fileList.insertInOrder(ch); // Method: insertInOrder(char)
                    }
                    else {
                        fileList.append(ch); // Method: append(char)
                    }
                    //cout << ch; 
                }
            }

            inputFile.close();

            fileList.print();
        }
    }
    return 0;
}