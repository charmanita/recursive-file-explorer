#ifndef FILENODE_H
#define FILENODE_H

#include <string>
#include <filesystem>
using namespace std;

struct Node
{
    string name;
    bool isDir;
    int size;          // The sizes of files, not folders.
    Node *firstChild;  // head of folder's child list.
    Node *nextSibling; // next item in same folder.

    Node(const string &n, bool dir, int s = 0) : name(n), isDir(dir), size(s), firstChild(nullptr), nextSibling(nullptr) {}
};

Node *makeDir(const string &name);
Node *makeFile(const string &name, int size);
void addChild(Node *parent, Node *child);
int totalSize(const Node *node);
void printTree(const Node *node, int depth);
void freeTree(Node *node);
Node *buildFromPath(const filesystem::path &p);

#endif // FILENODE_H