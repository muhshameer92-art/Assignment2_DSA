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
	int nextPlayerID;
public:
	classManager() {
		nextPlayerID = 0;
	}
	void registerPlayer(string user,int s ,int w, int l, int d) {
		nextPlayerID++;
		person* p = new person(nextPlayerID,user,s, w, l, d);
		players.push_back(p);
		list.push_back(p);
		
	}
	void removePlayer(string user) {
		for (int i = 0; i < players.size(); i++) {
			if (players[i]->getUsername() == user) {
				list.remove(i+1);
				players.erase(players.begin() + i);
			}
		}
	}
	void revealNoticeBoard() {
		list.displayForward();
	}
	void revealRegisteredPlayers() {
		for (int i = 0; i < players.size(); i++) {
			cout << *players.at(i) << endl;
		}
	}

	
};
