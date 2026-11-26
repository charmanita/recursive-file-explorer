// utilities.cpp - Implementation for some useful utilities used
// in a group project during my third C++ programming course at Grayson College.
// Credits to Aidan Head & Jesse Boney for the implementation and header.
#include "utilities.h"
#include <iostream>
#include <string>
using namespace std;

// Centers text within width characters.
void centerText(string text, int width)
{

    int padding = (width - text.length()) / 2;

    if (padding < 0)
    {
        padding = 0;
    }

    cout << string(padding, ' ') << text << endl;
}

// Prints a horizontal bar.
void printBar(int width)
{

    cout << string(width, '=') << endl;
}

// Prompts user for a valid int.
int getIntegerInput(string prompt)
{

    int input;

    while (true)
    {

        cout << prompt;

        if (cin >> input)
        {
            cin.ignore(10000, '\n');
            return input;
        }

        cout << "Invalid input. Please enter a number from 1-9.\n";

        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Displays menu
void displayMenu()
{

    cout << "1. Print File Tree.\n";
    cout << "2. Show total size of folder.\n";
    cout << "3. Search by name.\n";
    cout << "4. Open another folder.\n";
    cout << "5. Refresh\n";
    cout << "6. Add file or folder.\n";
    cout << "7. Delete file or folder.\n";
    cout << "8. Help\n";
    cout << "9. Exit\n";
}