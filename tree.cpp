#include "tree.h"
#include <string.h>

Tree::Tree()
{
    //Node(char* name, int id, bool isDir, Node* parent, Tree *myTree);
    this->root = new Node((char *)"root", 0, true, NULL, this);
    this->root->setLevel(0);

    this->currentDir = this->root;
    this->numNodes = 0;
    this->lastID = 0;
}

Node *Tree::addChild(Node *parent, char *name, bool isDir)
{
    if (parent != NULL && parent->getIsDir() == true)
    {
        //Initialize new Node
        Node *newNode = new Node(name, lastID + 1, isDir, parent, this);
        newNode->setLevel(parent->getLevel() + 1);

        //Set as child of parent
        parent->getChilds()->push_back(newNode);
        this->lastID++;
        this->numNodes++;

        return newNode;
    }
    return NULL;
}
Node *Tree::findChild(Node *parent, char *name)
{
    if (parent != NULL && parent->getIsDir() == true)
    {
        //Iterate through childs
        for (auto node = parent->getChilds()->begin(); node != parent->getChilds()->end(); ++node)
        {
            if (strncmp(name, (*node)->getName(), strlen((*node)->getName())) == 0 && strncmp(name, (*node)->getName(), strlen(name)) == 0)
            {
                return (*node);
            }
        }
        return NULL;
    }
    return NULL;
}
void Tree::removeChild(Node *node)
{
    if (node->getParent() != NULL)
    {
        int pos = 0;
        vector<Node *> *parentVector = node->getParent()->getChilds();
        for (auto i : (*parentVector))
        {
            if (*&i == *&node)
            {
                (*parentVector).erase((*parentVector).begin() + pos);
                break;
            }
            pos++;
        }
    }
    delete node;
    this->numNodes--;
}

Node *Tree::getRoot()
{
    return this->root;
}

Node *Tree::getCurrentDir()
{
    return this->currentDir;
}

void Tree::setCurrentDir(Node *node)
{
    this->currentDir = node;
}

void Tree::removeTree(Node *node)
{
    if ((*node->getChilds()).size() == 0)
        delete node;
    else
    {
        for (auto i : (*node->getChilds()))
            removeTree(i);
    }
}

Node *Tree::copyNodeRecursive(Node *copyNode, Node *parent, char *name)
{
    this->lastID++;
    Node *newNode = new Node(name, lastID, copyNode->getIsDir(), parent, this);
    if ((*copyNode->getChilds()).size() > 0)
    {
        for (auto i : (*copyNode->getChilds()))
        {
            (*newNode->getChilds()).push_back(copyNodeRecursive(i, copyNode, i->getName()));
        }
    }
    return newNode;
}

Tree::~Tree()
{
}