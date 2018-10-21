#ifndef TERMINAL_H
#define TERMINAL_H
#include "command.h"
using namespace std;

#define EXIT 0
#define CMD_LS 1
#define CMD_PWD 2
#define CMD_CD 3
#define CMD_MV 4
#define CMD_CP 5
#define CMD_MKDIR 6
#define CMD_RMDIR 7
#define CMD_RM 8
#define CMD_LLS 9
#define CMD_LCD 10
#define CMD_LPWD 11
#define CMD_UPLOAD 12
#define CMD_TOUCH 13

class Terminal
{
  private:
    Tree *tree;
    Command *cmd;

  public:
    Terminal();
    void run();
    void read_command(command_t *command);
    int get_command_type(char *command);
    void exec_command(command_t *command);
};
#endif