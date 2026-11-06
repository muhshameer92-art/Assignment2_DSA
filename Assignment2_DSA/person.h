#pragma once
class person {
private:
    int playerID;
    string username;
    int score;
    int wins;
    int losses;
    int draws;
    int matchesPlayed;
    int level;
    //Additional helper
    int max(int a, int b) {
        if (a >= b)
            return a;
        else
            return b;
    }
public:
    person(int pID = 0, string user = "", int s = 0, int w = 0, int l = 0, int d = 0)
    {
        playerID = pID;
        username = user;
        score = s;
        wins = w;
        losses = l;
        draws = d;
        matchesPlayed = wins + losses + draws;
        level = max(1, (wins + 0.5 * draws) / 5 + 1);
    }
    int getWins() const {
        return wins;
    }
    int getDraws() const {
        return draws;
    }
    int getLosses() const {
        return losses;
    }
    int getLvl() const {
        return level;
    }
    int getMatchesplayed() const {
        return matchesPlayed;
    }
    int getPlayerID() const {
        return playerID;
    }
    int getScore() const {
        return score;
    }
    string getUsername() const {
        return username;
    }
    void updateLvl() {
        level = max(1, (wins + 0.5 * draws) / 5 + 1);
    }
    void update_wins() {
        wins++;
        matchesPlayed++;
        updateLvl();
    }
    void update_draws() {
        draws++;
        matchesPlayed++;
        updateLvl();
    }
    void update_lost() {
        losses++;
        matchesPlayed++;
    }
    void update_score(int newScore) {
        if (newScore > score)
            score = newScore;
    }
};
