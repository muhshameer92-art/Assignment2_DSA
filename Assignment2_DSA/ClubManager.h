#pragma once
#include <iostream>
#include <vector>
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
			removePlayer(players.at(i));
	}
	void registerPlayer(string user,int scr ,int win, int loss, int draw) {
		nextPlayerID++;
		if(!user.empty())
			user[0] = toupper(user[0]);//capitalize first letter of word
		person* p = new person(nextPlayerID,user,scr, win, loss, draw);
		players.push_back(p);
		list.push_back(p);
		indexBST.insert(p);
	}
	void removePlayer(person* user) {
		vector<person*> temp;
		for (int i = 0; i < players.size(); i++) {
			if (players[i]->getPlayerID() == user->getPlayerID() ) {
				indexBST.remove(players[i]);
				list.remove(players[i]->getPlayerID());
				delete players[i];
			}
			else {
				temp.push_back(players[i]);
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
	void revealDirectory() {
		indexBST.display();
	}
	void bringForward(string name) {
		for (int i = 0; i < players.size(); ++i) {
			if (players.at(i)->getUsername() == name)
				list.moveForward(players.at(i)->getPlayerID());
		}
	}
};
