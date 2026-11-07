#include <iostream>
#include "ClubManager.h"
using namespace std;
//Test file
int main()
{
    classManager cm;
    cm.registerPlayer("Shameer", 1000, 8, 1, 1);
    cm.registerPlayer("Izan", 1200, 9, 0, 1);
    cm.registerPlayer("Nofil", 1100, 8, 0, 2);
    cm.registerPlayer("Musa", 1200, 10, 0, 0);
    
    cm.revealNoticeBoard();
    cm.revealRegisteredPlayers();
    return 0;
}
