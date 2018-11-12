#include "command.h"

Command::Command(Tree *tree)
{
    this->tree = tree;
}
void Command::ls(command_t *command)
{
    if ((*command->args).size() != 0)
    {
        printf("Error! The command ls doesn't accept params!");
        return;
    }

    vector<Node *> *childs = this->tree->getCurrentDir()->getChilds();
    int totalSize = 0;

    for (auto i : (*childs))
    {
        time_t date = i->getLastModification();
        char *lastMod = ctime(&date);
        cout << i->getName() << " " << (i->getIsDir() ? "DIR" : "FILE") << " " << i->getSize() << " " << lastMod;
        totalSize += (int)i->getSize();
    }

    cout << (*childs).size() << " elements with a total size of " << totalSize << " bytes";
}
void Command::pwd(command_t *command)
{
    if ((*command->args).size() != 0)
    {
        printf("Error! The command pwd doesn't accept params!");
        return;
    }

    Node *position = this->tree->getCurrentDir();
    vector<char *> path;
    while (position != NULL)
    {
        path.insert(path.begin(), position->getName());
        position = position->getParent();
    }

    for (auto &i : path)
    {
        cout << "/";
        cout << i;
    }
}
void Command::cd(command_t *command)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command cd only accepts 1 argument");
        return;
    }

    Node *parent;
    vector<char *> *path = getPath((*command->args)[0]);

    if (strncmp((*command->args)[0], "/", 1) == 0)
    {
        parent = this->tree->getRoot();

        for (auto i : (*path))
        {
            //Check that the first char is root
            if (*&i == *&(path->front()))
            {
                if (i != NULL && strncmp(i, "root", strlen("root")) != 0)
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
            else
            {
                //If the child exists point child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    parent = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
        }
    }
    else if (strncmp((*command->args)[0], "..", 2) == 0 && (*path).size() == 1)
    {
        if (this->tree->getCurrentDir() != this->tree->getRoot())
            parent = this->tree->getCurrentDir()->getParent();
        else
            return;
    }
    else
    {
        parent = this->tree->getCurrentDir();
        for (auto i : (*path))
        {
            //If the child exists point child | else error
            if (this->tree->findChild(parent, i) != NULL)
            {
                parent = this->tree->findChild(parent, i);
            }
            else
            {
                printf("Error! The path doesn't exist!");
                return;
            }
        }
    }
    this->tree->setCurrentDir(parent);
}
void Command::mv(command_t *command)
{
    if ((*command->args).size() != 2)
    {
        printf("Error! The command mv only accepts 2 arguments");
        return;
    }
    Node *parent;
    vector<char *> *path = getPath((*command->args)[0]);

    if (strncmp((*command->args)[0], "/", 1) == 0)
    {
        parent = this->tree->getRoot();

        for (auto i : (*path))
        {
            if (*&i == *&(path->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    Node *node = this->tree->findChild(parent, i);
                    node->setName((*command->args)[1]);
                }
                else
                {
                    printf("Error! The DIR or FILE doesn't exist!");
                }
            }
            else
            {
                //Check that the first char is root
                if (*&i == *&(path->front()))
                {
                    if (strncmp(i, "root", strlen("root")) != 0)
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
                else
                {
                    //If the child exists point child | else error
                    if (this->tree->findChild(parent, i) != NULL)
                    {
                        parent = this->tree->findChild(parent, i);
                    }
                    else
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
            }
        }
    }
    else
    {
        parent = this->tree->getCurrentDir();
        for (auto i : (*path))
        {
            //If it's the last char
            if (*&i == *&(path->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    Node *node = this->tree->findChild(parent, i);
                    node->setName((*command->args)[1]);
                }
                else
                {
                    printf("Error! The DIR or FILE doesn't exist!");
                }
            }
            else
            {
                //If the child exists point child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    parent = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
        }
    }
}
void Command::cp(command_t *command)
{
    if ((*command->args).size() != 2)
    {
        printf("Error! The command mv only accepts 2 arguments");
        return;
    }
    Node *parent;                                         // Iterator
    vector<char *> *path1 = getPath((*command->args)[0]); //First arg path
    vector<char *> *path2 = getPath((*command->args)[1]); //Second arg path
    Node *copyNode;                                       //The node that is going to be copy

    //Get copyNode from the first arg
    if (strncmp((*command->args)[0], "/", 1) == 0)
    {
        parent = this->tree->getRoot();

        for (auto i : (*path1))
        {
            if (*&i == *&(path1->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    copyNode = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The DIR or FILE doesn't exist!");
                }
            }
            else
            {
                //Check that the first char is root
                if (*&i == *&(path1->front()))
                {
                    if (strncmp(i, "root", strlen("root")) != 0)
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
                else
                {
                    //If the child exists point child | else error
                    if (this->tree->findChild(parent, i) != NULL)
                    {
                        parent = this->tree->findChild(parent, i);
                    }
                    else
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
            }
        }
    }
    else
    {
        parent = this->tree->getCurrentDir();
        for (auto i : (*path1))
        {
            //If it's the last char
            if (*&i == *&(path1->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    copyNode = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The DIR or FILE doesn't exist!");
                }
            }
            else
            {
                //If the child exists point child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    parent = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
        }
    }

    //Find the path and copy the node(s) second arg
    if (strncmp((*command->args)[0], "/", 1) == 0)
    {
        parent = this->tree->getRoot();

        for (auto i : (*path2))
        {
            if (*&i == *&(path2->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) == NULL)
                {
                    Node *newNode = this->tree->copyNodeRecursive(copyNode, parent, i);
                    (*parent->getChilds()).push_back(newNode);
                }
                else
                {
                    printf("Error! The DIR or FILE already exist!");
                }
            }
            else
            {
                //Check that the first char is root
                if (*&i == *&(path2->front()))
                {
                    if (strncmp(i, "root", strlen("root")) != 0)
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
                else
                {
                    //If the child exists point child | else error
                    if (this->tree->findChild(parent, i) != NULL)
                    {
                        parent = this->tree->findChild(parent, i);
                    }
                    else
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
            }
        }
    }
    else
    {
        parent = this->tree->getCurrentDir();
        for (auto i : (*path2))
        {
            //If it's the last char
            if (*&i == *&(path2->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) == NULL)
                {
                    Node *newNode = this->tree->copyNodeRecursive(copyNode, parent, i);
                    (*parent->getChilds()).push_back(newNode);
                }
                else
                {
                    printf("Error! The DIR or FILE already exist!");
                }
            }
            else
            {
                //If the child exists point child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    parent = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
        }
    }
}
void Command::mkdir(command_t *command, bool isDir)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command mkdir only accepts 1 argument");
        return;
    }

    Node *parent;
    vector<char *> *path = getPath((*command->args)[0]);

    if (strncmp((*command->args)[0], "/", 1) == 0)
    {
        parent = this->tree->getRoot();

        for (auto i : (*path))
        {
            if (*&i == *&(path->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) == NULL)
                {
                    Node *node = this->tree->addChild(parent, i, isDir);
                    if (node == NULL)
                        printf("Error! This is a file!");
                }
                else
                {
                    printf("Error! It already exist a dir/file with this name!");
                }
            }
            else
            {
                //Check that the first char is root
                if (*&i == *&(path->front()))
                {
                    if (strncmp(i, "root", strlen("root")) != 0)
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
                else
                {
                    //If the child exists point child | else error
                    if (this->tree->findChild(parent, i) != NULL)
                    {
                        parent = this->tree->findChild(parent, i);
                    }
                    else
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
            }
        }
    }
    else
    {
        parent = this->tree->getCurrentDir();
        for (auto i : (*path))
        {
            //If it's the last char
            if (*&i == *&(path->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) == NULL)
                {
                    Node *node = this->tree->addChild(parent, i, isDir);
                    if (node == NULL)
                        printf("Error! This is a file!");
                }
                else
                {
                    printf("Error! It already exist a dir/file with this name!");
                }
            }
            else
            {
                //If the child exists point child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    parent = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
        }
    }
}
void Command::touch(command_t *command)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command touch only accepts 1 argument");
        return;
    }
    this->mkdir(command, false);
}
void Command::lls(command_t *command)
{
    if ((*command->args).size() != 0)
    {
        printf("Error! The command lls doesn't accept arguments!");
        return;
    }

    struct dirent **namelist; //files and dir list
    struct stat sb;           //Get info of dir and file
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
        return;
    }

    int numberofElem = n;
    int totalSize = 0;
    while (n--)
    {
        if (stat(namelist[n]->d_name, &sb) == 1)
        {
            perror("stat");
            return;
        }
        cout << namelist[n]->d_name << " " << (S_ISDIR(sb.st_mode) ? "DIR" : "FILE") << " " << sb.st_size << " " << ctime(&sb.st_mtime) << endl;
        totalSize += sb.st_size;
        free(namelist[n]);
    }
    cout << numberofElem << " elements with a total size of " << totalSize << " bytes";
    free(namelist);
}
void Command::lcd(command_t *command)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command lcd only accepts 1 argument!");
        return;
    }
    if (chdir((*command->args)[0]) != 0)
        perror("chdir() error()");
}
void Command::lpwd(command_t *command)
{
    if ((*command->args).size() != 0)
    {
        printf("Error! The command lpwd doesn't accept arguments!");
        return;
    }
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
    else
        printf("%s", cwd);
}
void Command::rmdir(command_t *command, bool isDir)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command rmdir only accepts 1 argument");
        return;
    }

    Node *parent;
    vector<char *> *path = getPath((*command->args)[0]);

    if (strncmp((*command->args)[0], "/", 1) == 0)
    {
        parent = this->tree->getRoot();

        for (auto i : (*path))
        {
            if (*&i == *&(path->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    Node *node = this->tree->findChild(parent, i);
                    if (node->getIsDir() == isDir)
                    {
                        if ((*node->getChilds()).size() == 0 && node != this->tree->getCurrentDir())
                        {
                            this->tree->removeChild(node);
                        }
                        else
                            printf("Error! This dir is not empy or is being use!");
                    }
                    else
                        printf("Error! use rmdir for DIR and rm for FILES!");
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                }
            }
            else
            {
                //Check that the first char is root
                if (*&i == *&(path->front()))
                {
                    if (strncmp(i, "root", strlen("root")) != 0)
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
                else
                {
                    //If the child exists point child | else error
                    if (this->tree->findChild(parent, i) != NULL)
                    {
                        parent = this->tree->findChild(parent, i);
                    }
                    else
                    {
                        printf("Error! The path doesn't exist!");
                        return;
                    }
                }
            }
        }
    }
    else
    {
        parent = this->tree->getCurrentDir();
        for (auto i : (*path))
        {
            //If it's the last char
            if (*&i == *&(path->back()))
            {
                //If there is no child with this name create child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    Node *node = this->tree->findChild(parent, i);
                    if (node->getIsDir() == isDir)
                    {
                        if ((*node->getChilds()).size() == 0 && node != this->tree->getCurrentDir())
                        {
                            this->tree->removeChild(node);
                        }
                        else
                            printf("Error! This dir is not empy or is being use!");
                    }
                    else
                        printf("Error! use rmdir for DIR and rm for FILES!");
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                }
            }
            else
            {
                //If the child exists point child | else error
                if (this->tree->findChild(parent, i) != NULL)
                {
                    parent = this->tree->findChild(parent, i);
                }
                else
                {
                    printf("Error! The path doesn't exist!");
                    return;
                }
            }
        }
    }
}
void Command::rm(command_t *command)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command rm only accepts 1 argument");
        return;
    }
    this->rmdir(command, false);
}
void Command::upload(command_t *command)
{
    if ((*command->args).size() != 1)
    {
        printf("Error! The command upload only accepts 1 argument!");
        return;
    }

    struct dirent **namelist; //files and dir list
    struct stat sb;           //Get info of dir and file
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
        return;
    }

    int numberofElem = n;
    int totalSize = 0;
    bool exist = false;
    while (n--)
    {
        if (strncmp(namelist[n]->d_name, (*command->args)[0], strlen(namelist[n]->d_name)) == 0)
        {
            exist = true;

            if (stat(namelist[n]->d_name, &sb) == 1)
            {
                perror("stat");
                break;
            }

            if (S_ISDIR(sb.st_mode))
            {
                printf("This is not a file!");
                break;
            }

            if(this->tree->findChild(this->tree->getCurrentDir(), namelist[n]->d_name) != NULL){
                printf("Error! It already exist a dir/file with this name!");
            }

            Node *uploadNode = this->tree->addChild(this->tree->getCurrentDir(), namelist[n]->d_name, false);
            uploadNode->setSize(sb.st_mtime);
            uploadNode->setSize(sb.st_size);
            break;
        }
    }

    if(!exist)
        printf("Error! The file doesn't exist!");

    //Free memory 
    while (numberofElem--)
        free(namelist[numberofElem]);
    free(namelist);
}

vector<char *> *Command::getPath(char *path)
{
    vector<char *> *vPath = new vector<char *>();
    const char s[2] = "/";
    char *token;

    token = strtok(path, s);
    vPath->push_back(token);

    while (token != NULL)
    {
        token = strtok(NULL, s);
        if (token != NULL)
            vPath->push_back(token);
    }

    return vPath;
}

void Command::printPath()
{
    Node *position = this->tree->getCurrentDir();
    vector<char *> path;
    while (position != NULL)
    {
        path.insert(path.begin(), position->getName());
        position = position->getParent();
    }

    for (auto &i : path)
    {
        cout << i;
        if (&i == &path.back())
            cout << "> ";
        else
            cout << "/";
    }
}
