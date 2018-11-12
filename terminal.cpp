#include "terminal.h"

Terminal::Terminal()
{
    this->tree = new Tree();
    this->tree->loadTree();
    this->cmd = new Command(tree);
}

void Terminal::run()
{
    bool exit = false;
    command_t command;
    command.args = new vector<char *>();
    while (!exit)
    {
        //print actual path
        this->cmd->printPath();
        read_command(&command);
        exec_command(&command);
    }
}

void Terminal::read_command(command_t *command)
{
    char *line = new char[1024];
    const char s[2] = " ";
    char *token;
    (*command->args).clear();

    //Get user input
    fgets(line, 1023, stdin);
    //Assign command type and args
    token = strtok(line, s);
    command->type = get_command_type(token);

    while (token != NULL)
    {
        token = strtok(NULL, s);
        if (token != NULL)
        {
            int len = strlen(token);
            if (len > 0 && token[len - 1] == '\n')
                token[len - 1] = '\0';
            command->args->push_back(token);
        }
    }
}

int Terminal::get_command_type(char *command)
{
    if (command != NULL)
    {
        int len = strlen(command);
            if (len > 0 && command[len - 1] == '\n')
                command[len - 1] = '\0';

        if (!strncmp("ls", command, strlen("ls")) && strlen(command) == strlen("ls"))
        {
            return CMD_LS;
        }
        else if (!strncmp("pwd", command, strlen("pwd")) && strlen(command) == strlen("pwd"))
        {
            return CMD_PWD;
        }
        else if (!strncmp("cd", command, strlen("cd")) && strlen(command) == strlen("cd"))
        {
            return CMD_CD;
        }
        else if (!strncmp("mv", command, strlen("mv")) && strlen(command) == strlen("mv"))
        {
            return CMD_MV;
        }
        else if (!strncmp("cp", command, strlen("cp")) && strlen(command) == strlen("cp"))
        {
            return CMD_CP;
        }
        else if (!strncmp("mkdir", command, strlen("mkdir")) && strlen(command) == strlen("mkdir"))
        {
            return CMD_MKDIR;
        }
        else if (!strncmp("rmdir", command, strlen("rmdir")) && strlen(command) == strlen("rmdir"))
        {
            return CMD_RMDIR;
        }
        else if (!strncmp("rm", command, strlen("rm")) && strlen(command) == strlen("rm"))
        {
            return CMD_RM;
        }
        else if (!strncmp("lls", command, strlen("lls")) && strlen(command) == strlen("lls"))
        {
            return CMD_LLS;
        }
        else if (!strncmp("lcd", command, strlen("lcd")) && strlen(command) == strlen("lcd"))
        {
            return CMD_LCD;
        }
        else if (!strncmp("lpwd", command, strlen("lpwd")) && strlen(command) == strlen("lpwd"))
        {
            return CMD_LPWD;
        }
        else if (!strncmp("upload", command, strlen("upload")) && strlen(command) == strlen("upload"))
        {
            return CMD_UPLOAD;
        }
        else if (!strncmp("touch", command, strlen("touch")) && strlen(command) == strlen("touch"))
        {
            return CMD_TOUCH;
        }
        else if (!strncmp("exit", command, strlen("exit")) && strlen(command) == strlen("exit"))
        {
            return EXIT;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

void Terminal::exec_command(command_t *command)
{
    switch (command->type)
    {
    case CMD_LS:
        this->cmd->ls(command);
        break;
    case CMD_PWD:
        this->cmd->pwd(command);
        break;
    case CMD_CD:
        this->cmd->cd(command);
        break;
    case CMD_MV:
        this->cmd->mv(command);
        break;
    case CMD_CP:
        this->cmd->cp(command);
        break;
    case CMD_MKDIR:
        this->cmd->mkdir(command, true);
        break;
    case CMD_RMDIR:
        this->cmd->rmdir(command, true);
        break;
    case CMD_RM:
        this->cmd->rm(command);
        break;
    case CMD_LLS:
        this->cmd->lls(command);
        break;
    case CMD_LCD:
        this->cmd->lcd(command);
        break;
    case CMD_LPWD:
        this->cmd->lpwd(command);
        break;
    case CMD_UPLOAD:
        this->cmd->upload(command);
        break;
    case CMD_TOUCH:
        this->cmd->touch(command);
        break;
    case EXIT:
        this->tree->saveTree();
        printf("Close file system\n");
        exit(0);
        break;
    default:
        printf("Command not found\n");
        break;
    }
    printf("\n");
}