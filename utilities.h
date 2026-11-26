// utilities.h - Header file for some useful utilities used
// in a group project during my third C++ programming course at Grayson College.
// Credits to Aidan Head & Jesse Boney for the implementation and header.
#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
using namespace std;

// Centers text within width characters.
void centerText(string text, int width);

// Prints a bar of = characters.
void printBar(int width);

// Prompt the user and checks if they inputed int instead of text
int getIntegerInput(string prompt);

// Display the menu in main
void displayMenu();

#endif