#include <sqlite3.h>
#include "modules/sigmaker.h"

int main(int argc, char **argv)
{
    SigMaker::append("../config.yml");

    std::cout << SigMaker::getSignature("../config.yml") << std::endl;

    return 0;
}
