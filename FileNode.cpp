#include "FileNode.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
using namespace std;
namespace fs = filesystem; // Using fs as a shortcut for filesystem header.

// Function for making a directory.
Node *makeDir(const string &name) { return new Node(name, true); }

// Function for making a file.
Node *makeFile(const string &name, int size) { return new Node(name, false, size); }

// Add Child function adds a file.
void addChild(Node *parent, Node *child)
{
    if (parent->firstChild == nullptr)
    {
        parent->firstChild = child;
    }
    else
    {
        Node *p = parent->firstChild;
        while (p->nextSibling != nullptr)
            p = p->nextSibling;
        p->nextSibling = child;
    }
}

// buildFromPath builds filesystem using filesystem header.
Node *buildFromPath(const fs::path &p)
{
    error_code ec;
    // Don't follow symlinks (a link to a parent folder would recurse forever).
    if (fs::is_symlink(p, ec))
        return makeFile(p.filename().string(), 0);

    // Base case: a regular file.
    if (!fs::is_directory(p, ec))
    {
        auto size = fs::file_size(p, ec);
        return makeFile(p.filename().string(), ec ? 0 : static_cast<int>(size));
    }

    // Recursive case: a directory.
    Node *dir = makeDir(p.filename().string());
    vector<fs::path> entries;
    for (fs::directory_iterator it(p, ec), end; !ec && it != end; it.increment(ec))
        entries.push_back(it->path());
    sort(entries.begin(), entries.end());

    for (const auto &e : entries)
        addChild(dir, buildFromPath(e));

    return dir;
}

// printTree function prints the tree of files.
void printTree(const Node *node, int depth)
{
    cout << string(depth * 2, ' ') << node->name;
    if (node->isDir)
        cout << "/ (" << totalSize(node) << ")";
    else
        cout << " (" << node->size << ")";
    cout << endl;

    for (const Node *c = node->firstChild; c != nullptr; c = c->nextSibling)
        printTree(c, depth + 1);
}
// Return total size of directory.
int totalSize(const Node *node)
{
    if (!node->isDir)
        return node->size;

    int sum = 0; // local, fresh per call.
    for (const Node *c = node->firstChild; c != nullptr; c = c->nextSibling)
        sum += totalSize(c);
    return sum;
}

// freeTree frees memory.
void freeTree(Node *node)
{
    Node *c = node->firstChild;
    while (c != nullptr)
    {
        Node *next = c->nextSibling; // Save nextsibling before deleting.
        freeTree(c);
        c = next;
    }
    delete node;
}

// Prints the path of every item whose name contains term.
// Returns the match count.
int search(const Node *node, const string &term, const string &path)
{
    int matches = 0;
    for (const Node *c = node->firstChild; c != nullptr; c = c->nextSibling)
    {
        string childPath = path + "/" + c->name;
        if (c->name.find(term) != string::npos)
        {
            cout << childPath << (c->isDir ? "/" : "") << endl;
            matches++;
        }
        matches += search(c, term, childPath);
    }
    return matches;
}