// Recursive File Explorer - Main program
// This is where all of the user interface lives.
#include <filesystem>
#include <fstream> // Using fstream to modify files or folders.
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
        centerText("RECURSIVE FILE EXPLORER - Hunter Roberson (Charmanita)", 50);
        printBar(50);

        displayMenu(); // Displays menu using utilities.

        // Receive user input with input validation from utilities.
        choice = getIntegerInput("Please choose a menu option:\n");

        // Menu choices
        switch (choice)
        {
        case 1:
            // Prints file tree
            printTree(root, 0);
            break;

        case 2:
            cout << totalSize(root) << " bytes" << endl;
            break;

        case 3:
        {
            string term;
            if (prompt("Name contains: ", term) && !term.empty() && search(root, term, root->name) == 0)
                cout << "Well, looks like there's no matches, you may have typed it incorrectly. Please try again." << endl;
            break;
        }
        case 4:
        {
            string input;
            if (!prompt("Path: ", input) || input.empty())
                break;
            fs::path next = target / input; // Absolute input replaces target.
            Node *newRoot = loadTree(next);
            if (newRoot != nullptr)
            {
                freeTree(root);
                root = newRoot;
                target = fs::canonical(next);
            }
            break;
        }
        case 5:
        {
            Node *newRoot = loadTree(target);
            if (newRoot != nullptr)
            {
                freeTree(root); // Free old tree from memory before replacing.
                root = newRoot;
                target = fs::canonical(target);
            }
            break;
        }
        case 6:
        {
            string kind;
            if (!prompt("Create file or folder? (file/folder): ", kind) || kind.empty())
                break;

            string name;
            if (!prompt("Name (relative to current folder): ", name) || name.empty())
                break;

            fs::path newPath = target / name;
            error_code ec;

            if (kind == "file")
            {
                if (!newPath.parent_path().empty())
                    fs::create_directories(newPath.parent_path(), ec);

                ofstream out(newPath);
                if (!out)
                {
                    cout << "Could not create file: " << newPath << endl;
                    break;
                }
                out.close();
                cout << "Created file: " << newPath << endl;
            }
            else if (kind == "folder")
            {
                if (!fs::create_directories(newPath, ec) && ec)
                {
                    cout << "Could not create folder: " << newPath << endl;
                    break;
                }
                cout << "Created folder: " << newPath << endl;
            }
            else
            {
                cout << "Invalid type. Enter 'file' for file or 'folder' for folder.\n";
                break;
            }

            Node *newRoot = loadTree(target);
            if (newRoot != nullptr)
            {
                freeTree(root);
                root = newRoot;
            }
            break;
        }
        case 7:
            cout << "Thanks for checking out my program! - Hunter Roberson (Charmanita)\n";
            break;

        default:
            cout << "Invalid input for menu. Please choose 1-7.\n";
            break;
        }
    } while (choice != 7);

    freeTree(root);
    return 0;
}