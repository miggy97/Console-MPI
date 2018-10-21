#include <stdio.h>
#include <terminal.h>
using namespace std;

main(int argc, char const *argv[])
{
    Terminal *term = new Terminal();
    term->run();
    return 0;
}


