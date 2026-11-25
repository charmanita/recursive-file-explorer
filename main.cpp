// Recursive File Explorer - Main program
// This is where all of the user interface lives.
#include <filesystem>
#include <iostream>
#include "FileNode.h"

using namespace std;
namespace fs = filesystem; // Using fs as a shortcut for filesystem header.
int main(int argc, char *argv[])
{
    fs::path target = (argc > 1) ? argv[1] : "test_folder";

    // Path isn't found, print error.
    if (!fs::exists(target))
    {
        cout << "Path not found: " << target << endl;
        return 1;
    }

    target = fs::canonical(target); // Makes sure the folder path absolute and clean before building.
    Node *root = buildFromPath(target);
    printTree(root, 0);
    freeTree(root);
    return 0;
}