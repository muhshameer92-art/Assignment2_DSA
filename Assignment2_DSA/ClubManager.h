#pragma once
#include <iostream>
#include "vector.h"//my own vector implementation
#include "person.h"
#include "NoticeBoard.h"
#include "ChessPlayerDirectory.h"
#include "LeaderBoard.h"
using namespace std;

class classManager {
private:
	vector<person*> players;
	NoticeBoard list;
	chessPlayerDirectory indexBST;
	leaderBoard rankingAVL;
	int nextPlayerID;
public:
	classManager() {
		nextPlayerID = 0;
	}
	~classManager() {
		for (int i = 0; i < players.size(); i++)
			removePlayer(players.at(i)->getUsername() );
	}
	void registerPlayer(string user,int scr ,int win, int loss, int draw) {
		if (user == "")
		{
			cout << "No player is mentioned!" << endl;
			return;
		}
		if (scr < 0 || win < 0 || loss < 0 || draw < 0)
			return;
		nextPlayerID++;
		if(!user.empty())
			user[0] = toupper(user[0]);//capitalize first letter of word
		person* p = new person(nextPlayerID,user,scr, win, loss, draw);
		players.push_back(p);
		list.push_back(p);
		indexBST.insert(p);
		rankingAVL.insert(p);
	}
	void removePlayer(string user) {
		if (user == "")
		{
			cout << "No player is mentioned!" << endl;
			return;
		}
		vector<person*> temp;
		bool isFirst = true; // to ensure that only one player is removed in case of dups
		for (int i = players.size() - 1; i >= 0; --i) {// better to remove low scorer
			if (players.at(i)->getUsername() == user && isFirst) {
				isFirst = false;
				rankingAVL.remove(players.at(i));
				indexBST.remove(players.at(i));
				list.remove(players.at(i)->getPlayerID());
				delete players.at(i);
			}
			else {
				temp.push_back(players.at(i));
			}
		}
		players = temp;
	}
	void revealNoticeBoard() {
		list.displayForward();
	}
	void revealRegisteredPlayers() {
		for (int i = 0; i < players.size(); i++) {
			cout << *players.at(i) << endl;
		}
	}
	void revealLeaderBoard() {
		rankingAVL.displayAscending();
		
	}
	void revealDirectory() {
		indexBST.display();
	}
	void revealTopPlayer() {
		rankingAVL.displayHighest();
	}
	void revealBottomPlayer() {
		rankingAVL.displayLowest();
	}
	void bringForward(string name) {
		if (name == "") {
			cout << "No player mentioned!" << endl;
			return;
		}

		for (int i = 0; i < players.size(); ++i) {
			if (players.at(i)->getUsername() == name)
				list.moveForward(players.at(i)->getPlayerID());
		}
	}
};
