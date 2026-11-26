// Recursive File Explorer - Main program
// This is where all of the user interface lives.
#include <filesystem>
#include <iostream>
#include "FileNode.h"
#include "utilities.h" // Used for CenterText & printBar

using namespace std;
namespace fs = filesystem; // Using fs as a shortcut for filesystem header.

// Builds a new tree for target. Returns nullptr if the path can't be used.
Node *loadTree(const fs::path &target)
{
    error_code ec;
    fs::path clean = fs::canonical(target, ec); // Absolute and clean, fails if not found.
    if (ec)
    {
        cout << "Path not found: " << target << endl;
        return nullptr;
    }
    return buildFromPath(clean);
}

// Prints a message and reads one line. Returns false when input ends, this is for the menu.
bool prompt(const string &message, string &input)
{
    cout << message;
    return static_cast<bool>(getline(cin, input));
}

int main(int argc, char *argv[])
{
    fs::path target = (argc > 1) ? argv[1] : "test_folder";

    Node *root = loadTree(target);
    if (root == nullptr)
        return 1;
    target = fs::canonical(target);

    // Holds choice
    int choice;
    // Making menu
    do
    {
        printBar(50);
        centerText("RECURSIVE FILE EXPLORER - Hunter Roberson (Charmanita)");
        printBar(50);
    }
}