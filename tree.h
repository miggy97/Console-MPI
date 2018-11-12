#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "node.h"

using namespace std;

class Node;

class Tree
{
  private:
    Node *root;
    Node *currentDir;
    int numNodes;
    int lastID;

  public:
    Tree();
    Node *addChild(Node *parent, char *name, bool isDir);
    Node *findChild(Node *parent, char *name);
    void removeChild(Node *node);

    Node *getRoot();
    Node *getCurrentDir();
    void setCurrentDir(Node *node);
    void removeTree(Node *node);

    void loadTree();
    Node* loadNode(Node *lastNode, nodeSave *newNode);
    void saveTree();
    void saveNodesRecursive(Node *node, FILE *outfile);

    //Copy the node and all the dependencies recursively
    Node* copyNodeRecursive(Node *copyNode, Node *parent, char *name);
    ~Tree();
};
