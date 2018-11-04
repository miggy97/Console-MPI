#include "node.h"
#include <string.h>

Node::Node(char *name, int id, bool isDir, Node *parent, Tree *myTree)
{
    this->setName(name);
    this->id = id;
    this->isDir = isDir;
    this->parent = parent;
    this->childs = new vector<Node *>;
    this->myTree = myTree;
    this->isDir ? this->setSize(4096) : this->setSize(0);
    this->parent ? this->level = this->parent->getLevel() + 1 : this->level = 0;
}

Tree *Node::getMyTree()
{
    return this->myTree;
}
void Node::setMyTree(Tree *myTree)
{
    this->myTree = myTree;
}
Node *Node::getParent()
{
    return this->parent;
}
vector<Node *> *Node::getChilds()
{
    return this->childs;
}
char *Node::getName()
{
    return this->name;
}
void Node::setName(char *name)
{
    int len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';
    this->lastModification = time(0);
    strcpy(this->name, name);
}
int Node::getId()
{
    return this->id;
}
void Node::setId(int id)
{
    this->id = id;
}
int Node::getLevel()
{
    return this->level;
}
void Node::setLevel(int level)
{
    this->level = level;
}
bool Node::getIsDir()
{
    return this->isDir;
}
void Node::setIsDir(bool isDir)
{
    this->isDir = isDir;
}
off_t Node::getSize()
{
    off_t childsSize = 0;
    for (auto i : (*this->childs))
    {
        childsSize += i->getSize();
    }
    return this->size + childsSize;
}
void Node::setSize(off_t size)
{
    this->size = size;
}
time_t Node::getLastModification()
{
    return this->lastModification;
}
void Node::setLastModification(time_t lastModification)
{
    this->lastModification = lastModification;
}

nodeSave *Node::getNodeSave()
{
    nodeSave *node = new nodeSave();
    strcpy(node->name, this->name);
    node->id = this->id;
    node->level = this->level;
    node->isDir = this->isDir;
    node->size = this->size;
    node->lastModification = this->lastModification;

    return node;
}