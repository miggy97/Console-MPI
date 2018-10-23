#ifndef NODE_H
#define NODE_H
#include "tree.h"
#include<vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

using namespace std;

class Tree;

class Node
{
  private:
    Tree *myTree;
    Node *parent;
    vector<Node *> *childs;
    char name[25];
    int id;
    int level;
    bool isDir;
    off_t size;
    time_t lastModification;

  public:
    Node(char* name, int id, bool isDir, Node* parent, Tree *myTree);
    Tree *getMyTree();
    void setMyTree(Tree *myTree);
    Node *getParent();
    vector<Node *> *getChilds();
    char* getName();
    void setName(char *name);
    int getId();
    void setId(int id);
    int getLevel();
    void setLevel(int level);
    bool getIsDir();
    void setIsDir(bool isDir);
    off_t getSize();
    void setSize(off_t size);
    time_t getLastModification();
    void setLastModification(time_t lastModification);
};

#endif