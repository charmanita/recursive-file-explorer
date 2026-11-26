// help.cpp - Implementation for a help menu used
// in a group project during my third C++ programming course at Grayson College.
// I was the one who made the help.cpp as well as help.h.
#include "help.h"
#include <fstream>
#include <iostream>
using namespace std;

void help()
{

  // string for fstream
  string fName = "help.txt";

  ifstream inFile(fName);

  if (!inFile)
  {
    cerr << "Error opening file... did you make the file?" << endl;
    return;
  }

  // Reading each word and placing in line.
  string line;

  while (getline(inFile, line))
  {
    cout << line << endl;
  }

  // Close the file.
  inFile.close();
};