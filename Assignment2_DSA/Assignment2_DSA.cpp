#include <iostream>
#include "person.h"
#include "NoticeBoard.h"
using namespace std;
//Test file
int main()
{
    person p1(832,"Shameer",1000,8,1,1);
    person p2(845, "Mahad", 1100, 9, 1, 0);
    person p3(822, "Izan", 1200, 10, 0, 0);
    person p4(845, "Nofil", 1000, 7, 1, 2);
    NoticeBoard<person>n;
    n.push_front(p1);
    n.push_front(p2);
    n.push_front(p3);
    n.push_front(p4);
    n.show();
    return 0;
}
