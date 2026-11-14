#pragma once
#include <iostream>
#include <algorithm>
#include <cstdlib>//rand(), srand(), RAND_MAX (needed for the random match outcome)
#include <ctime>//time() to seed the random generator
#include "vector.h"//my own vector implementation
#include "person.h"
#include "NoticeBoard.h"
#include "ChessPlayerDirectory.h"
#include "LeaderBoard.h"
using namespace std;

class clubManager {
private:
	vector<person*> players;
	NoticeBoard list;
	chessPlayerDirectory indexBST;
	leaderBoard rankingAVL;
	int nextPlayerID;
public:
	clubManager() {
		nextPlayerID = 0;
		srand(time(0));
	}
	~clubManager() {
		for (int i = 0; i < players.size(); i++)
			delete players.at(i);
	}
	void registerPlayer(string user, int scr, int win, int loss, int draw) {
		if (user == "")
		{
			cout << "No player is mentioned!" << endl;
			return;
		}
		if (win < 0 || loss < 0 || draw < 0)//score may be negative, match counts may not
			return;
		transform(user.begin(), user.end(), user.begin(), ::toupper); //took idea from https://www.digitalocean.com/community/tutorials/string-uppercase-lowercase-c-plus-plus
		if (indexBST.search(user)) {//checked AFTER capitalizing so "ali" and "ALI" are the same user
			cout << "Username taken\n";
			return;
		}
		nextPlayerID++;
		person* p = new person(nextPlayerID, user, scr, win, loss, draw);
		players.push_back(p);
		list.push_front(p);//newest registration sits at the head
		indexBST.insert(p);
		rankingAVL.insert(p);
		cout << "Player registered successfully!" << endl;
	}
	void removePlayer(string user) {
		if (user == "")
		{
			cout << "No player is mentioned!" << endl;
			return;
		}
		transform(user.begin(), user.end(), user.begin(), ::toupper);
		person* target = indexBST.search(user);
		if (!target) {
			cout << "Player not found!" << endl;
			return;
		}
		//unlink from every structure BEFORE deleting the record
		rankingAVL.remove(target);
		indexBST.remove(target);
		list.remove(target->getPlayerID());
		vector<person*> temp;
		for (int i = 0; i < players.size(); i++) {
			if (players.at(i) != target)
				temp.push_back(players.at(i));
		}
		players = temp;
		delete target;
		cout << "Player removed successfully!" << endl;
	}
	void conductMatch(string user1, string user2) {
		if (user1 == "" || user2 == "") {
			cout << "No player is mentioned!" << endl;
			return;
		}
		transform(user1.begin(), user1.end(), user1.begin(), ::toupper);
		transform(user2.begin(), user2.end(), user2.begin(), ::toupper);
		if (user1 == user2) {
			cout << "A player can't play against themselves!" << endl;
			return;
		}
		person* p1 = indexBST.search(user1);
		person* p2 = indexBST.search(user2);
		if (!p1 || !p2) {
			if (!p1)
				cout << user1 << " is not registered!" << endl;
			if (!p2)
				cout << user2 << " is not registered!" << endl;
			return;
		}
		double P = rand();
		P = P / RAND_MAX;
		int points = 10 + rand() % 21;//random score between 10 and 30
		//old keys out of the AVL (keys depend on score & level)
		rankingAVL.remove(p1);
		rankingAVL.remove(p2);
		if (P < 0.3) {
			p1->update_wins();
			p2->update_lost();
			p1->update_score(p1->getScore() + points);
			p2->update_score(p2->getScore() - points);
			cout << user1 << " wins! (+" << points << " / -" << points << ")" << endl;
		}
		else if (P < 0.6) {
			p1->update_draws();
			p2->update_draws();
			cout << "Match drawn between " << user1 << " and " << user2 << "!" << endl;
		}
		else {
			p2->update_wins();
			p1->update_lost();
			p2->update_score(p2->getScore() + points);
			p1->update_score(p1->getScore() - points);
			cout << user2 << " wins! (+" << points << " / -" << points << ")" << endl;
		}
		list.moveForward(p1->getPlayerID());
		list.moveForward(p2->getPlayerID());
		//new keys back into the AVL
		rankingAVL.insert(p1);
		rankingAVL.insert(p2);
		cout << *p1 << endl;
		cout << *p2 << endl;
	}
	void revealNoticeBoard() {
		list.displayForward();
	}
	void revealNoticeBoardBackward() {
		list.displayBackward();
	}
	void revealRegisteredPlayers() {
		for (int i = 0; i < players.size(); i++) {
			cout << *players.at(i) << endl;
		}
	}
	void revealLeaderBoard() {
		rankingAVL.displayAscending();

	}
	void revealLeaderBoardDescending() {
		rankingAVL.displayDescending();
	}
	void revealDirectory() {
		if (players.size() == 0) {
			cout << "No players registered yet!" << endl;
			return;
		}
		indexBST.display();
	}
	void revealDirectoryRange(string low, string high) {
		transform(low.begin(), low.end(), low.begin(), ::toupper);
		transform(high.begin(), high.end(), high.begin(), ::toupper);
		indexBST.displayRange(low, high);
	}
	void revealTopPlayer() {
		rankingAVL.displayHighest();
	}
	void revealBottomPlayer() {
		rankingAVL.displayLowest();
	}
	void revealPlayer(string name) {
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		person* found = indexBST.search(name);
		if (!found) {
			cout << "Player not found!" << endl;
			return;
		}
		cout << *found << endl;
	}
	void revealNearbyPlayers(string name, int k) {
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		person* target = indexBST.search(name);
		if (!target) {
			cout << "Player not found!" << endl;
			return;
		}
		if (k <= 0) {
			cout << "k must be greater than 0!" << endl;
			return;
		}
		if (k > players.size() - 1) {
			cout << "Only " << players.size() - 1 << " other player(s) exist, showing all of them." << endl;
		}
		vector<person*> nearby = rankingAVL.Nearby_K_Opponents(target->getPlayerID(), k);
		if (nearby.size() == 0) {
			cout << "No opponents available!" << endl;
			return;
		}
		cout << "<==(NEAREST OPPONENTS FOR " << target->getUsername() << ")==>" << endl;
		for (int i = 0; i < nearby.size(); i++) {
			cout << *nearby.at(i) << endl;
		}
	}
	void bringForward(string name) {
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		if (name == "") {
			cout << "No player mentioned!" << endl;
			return;
		}
		person* found = indexBST.search(name);
		if (!found) {
			cout << "Player not found!" << endl;
			return;
		}
		list.moveForward(found->getPlayerID());
	}
};