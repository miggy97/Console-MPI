#ifndef TREE_H
#define TREE_H
#include <node.h>
class Node;

using namespace std;

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

    //Copy the node and all the dependencies recursively
    Node* copyNodeRecursive(Node *copyNode, Node *parent, char *name);
    ~Tree();
};

#endif