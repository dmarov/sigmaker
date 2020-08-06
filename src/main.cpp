#include <sqlite3.h>
#include "modules/eventloop.h"

int main(int argc, char **argv)
{
    EventLoop::start(argc, argv);

    return 0;
}
