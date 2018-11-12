#include "tree.h"
#include <iostream>

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

void Tree::loadTree()
{
    FILE *infile;
    nodeSave node;

    // Open person.dat for reading
    infile = fopen("arbol.dat", "r");
    if (infile == NULL)
    {
        printf("\nThere is no tree saved or error reading!\n");
        return;
    }

    fread(&this->numNodes, sizeof(int), 1, infile);
    fread(&this->lastID, sizeof(int), 1, infile);
    //root node
    fread(&node, sizeof(nodeSave), 1, infile);
    this->root->setLastModification(node.lastModification);

    Node *lastNode = this->root;
    // read file contents till end of file
    while (fread(&node, sizeof(nodeSave), 1, infile))
    {
       lastNode = loadNode(lastNode, &node);
    }

    // close file
    fclose(infile);
}

Node* Tree::loadNode(Node *lastNode, nodeSave *newNode)
{
    Node* parentNode = lastNode;
    Node* childNode;

    //Getting parent node by level
    while(parentNode->getLevel() >= newNode->level){
        parentNode = parentNode->getParent();
    }

    childNode = new Node(newNode->name, newNode->id, newNode->isDir, parentNode, this);
    childNode->setLastModification(newNode->lastModification);
    childNode->setSize(newNode->size);

    parentNode->getChilds()->push_back(childNode);
    
    return childNode;
}

void Tree::saveTree()
{
    FILE *outfile;

    // open file for writing
    outfile = fopen("arbol.dat", "w");
    if (outfile == NULL)
    {
        printf("\nError opend file\n");
        fclose(outfile);
        return;
    }
    fwrite(&this->numNodes, sizeof(int), 1, outfile);
    fwrite(&this->lastID, sizeof(int), 1, outfile);
    
    // write struct to file
    saveNodesRecursive(this->root, outfile);

    if (fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose(outfile);
}

void Tree::saveNodesRecursive(Node *node, FILE *outfile)
{
    nodeSave *saveNode = node->getNodeSave();
    fwrite(saveNode, sizeof(nodeSave), 1, outfile);
    for (auto i : (*node->getChilds()))
    {
        saveNodesRecursive(i, outfile);
    }
    delete saveNode;
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