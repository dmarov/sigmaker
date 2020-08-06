#include <sqlite3.h>
#include "modules/sigmaker.h"
#include <iostream>

int main(int argc, char **argv)
{
    SigMaker::appendRecord("../config.yml");

    std::cout << SigMaker::getSignature("../config.yml") << std::endl;

    return 0;
}
