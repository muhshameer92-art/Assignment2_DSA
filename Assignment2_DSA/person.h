#pragma once
#include <iostream>
#include <string>
using namespace std;
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
        level = max(1, int((wins + 0.5 * draws) / 5 + 1));
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
        level = max(1, int((wins + 0.5 * draws) / 5 + 1));
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
        updateLvl();
    }
    void update_score(int newScore) {
        score = newScore;//score can rise or fall (even below zero)
    }
    bool operator == (const person& p) const {
        if (username == p.username && playerID == p.playerID && level == p.level
            && score == p.score && matchesPlayed == p.matchesPlayed && wins == p.wins
            && losses == p.losses && draws == p.draws)
            return true;
        return false;
    }
    person& operator = (const person& p) {
        username = p.username;
        playerID = p.playerID;
        level = p.level;
        matchesPlayed = p.matchesPlayed;
        score = p.score;
        wins = p.wins;
        losses = p.losses;
        draws = p.draws;
        return *this;
    }
    friend ostream& operator << (ostream& out, const person& p) {
        out << "+______________+\n";
        out << " Player: " << p.getUsername() << endl;
        out << " PlayerID: " << p.getPlayerID() << endl;
        out << " Level: " << p.getLvl() << endl;
        out << " Score: " << p.getScore() << endl;
        out << " Matches Played: " << p.getMatchesplayed() << endl;
        out << " Wins: " << p.getWins() << endl;
        out << " Losses: " << p.getLosses() << endl;
        out << " Draws: " << p.getDraws() << endl;
        out << "+______________+\n";
        return out;
    }
};