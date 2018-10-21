#ifndef COMMAND_H
#define COMMAND_H
#include "tree.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef struct command_t
{
    int type;
    vector<char *> *args;
} command_t;

class Command
{
  private:
  Tree* tree;
  public:
    Command(Tree* tree);

    //Commands
    void ls(command_t *command);
    void pwd(command_t *command);
    void cd(command_t *command);
    void mv(command_t *command);
    void cp(command_t *command);
    void mkdir(command_t *command, bool isDir);
    void rmdir(command_t *command, bool isDir);
    void rm(command_t *command);
    void lls(command_t *command);
    void lcd(command_t *command);
    void lpwd(command_t *command);
    void upload(command_t *command);
    void touch(command_t *command);

    //Returns a vector with the path
    vector<char*>* getPath(char *path);

    //Prints full path
    void printPath();
};
#endif