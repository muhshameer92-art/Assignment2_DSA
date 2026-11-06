#include <iostream>
using namespace std;
class person {
public:
    int playerID;
    string username;
    int score;
    int wins;
    int loses;
    int draws;
    int matchesPlayed;
    int level;
    person(int pID = 0, string user = "", int s = 0, int w = 0, int l = 0, int d = 0, int lvl = 0)
    {
        playerID = pID;
        username = user;
        score = s;
        wins = w;
        loses = l;
        draws = d;
        matchesPlayed = wins + loses + draws;
        level = lvl;
    }
    int max(int a, int b) {
        if (a >= b)
            return a;
        else
            return b;
    }
    void updateLvl() {
        level = max(1, (wins + 0.5 * draws) / 5 + 1);
    }
};
int main()
{

    return 0;
}
