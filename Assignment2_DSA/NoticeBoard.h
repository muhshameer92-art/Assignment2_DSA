#pragma once
#include <iostream>
#include "person.h"
using namespace std;
template<class T>
class NoticeBoard {
	struct PlayerNode {
		T player;
		PlayerNode* next;
		PlayerNode* prev;
		PlayerNode(T pl = person(), PlayerNode* n = NULL, PlayerNode* p = NULL) {
			player = pl;
			next = n;
			prev = p;
		}
	};
	PlayerNode* head;
	PlayerNode* tail;
	void displayForwardsHelper(PlayerNode* h) {
		if (h == tail) {
			cout << "\n(TAIL)\n";
			return;
		}
		cout << h->player <<endl<<" || \n";
		displayForwardsHelper(h->next);
	}
	void displayBackwardsHelper(PlayerNode* h = tail -> prev) {
		if (h == head) {
			cout << "\n(HEAD)\n";
			return;
		}
		cout << h->player << endl << " || \n";
		displayBackwardsHelper(h->prev);
	}
	PlayerNode* search_Player(PlayerNode* curr,  T& p) {
		if (curr == tail)
			return NULL;
		if (curr->player.getPlayerID() == p.getPlayerID())
			return curr;
		return search_Player(curr->next, p);
	}
	void move_front(T& p) {
		if (head->next == tail)
			return;
		if (head->next->player.getPlayerID() == p.getPlayerID())
			return;
		PlayerNode* curr = head->next;
		curr = search_Player(curr, p);
		if (!curr)
			return;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;

		curr->next = head->next;
		head->next->prev = curr;
		head->next = curr;
		curr->prev = head;
	}
public:
	NoticeBoard() {
		head = new PlayerNode();
		tail = new PlayerNode();
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
	}
	NoticeBoard(const PlayerNode*p) {
		head = tail = new PlayerNode();
		PlayerNode* curr = p.head->next;
		PlayerNode* temp = head->next;
		PlayerNode* pr = head;
		while (!curr) {
			temp->prev = pr;
			temp->player = curr->player;
			pr = temp;
			temp = temp->next;
			curr = curr->next;
		}
	}
	~NoticeBoard() {
		PlayerNode* temp = head->next;
		while (!temp) {
			temp = temp->next;
			delete temp->prev;
		}
		delete head;
		delete tail;
	}
	void push_front(T val) {
		PlayerNode* temp = new PlayerNode(val, head->next, head);
		head->next->prev = temp;
		head->next = temp;
	}
	void push_back(T val) {
		PlayerNode* temp = new PlayerNode(val, tail, tail->prev);
		tail->prev->next = temp;
		tail->prev = temp;
	}
	void pop_front() {
		if (head->next == tail)
			return;
		PlayerNode* temp = head -> next;
		head->next = head->next->next;
		delete temp;
		head -> next ->prev = head;
	}
	void pop_back() {
		if (head->next == tail)
			return;
		PlayerNode* temp = tail->prev;
		tail->prev = tail->prev->prev;
		delete temp;
		tail->prev->next = tail;
	}
	void remove(T&d) {
		PlayerNode* temp = head->next;
		if (temp == tail)
			return;
		while (temp != tail) {
			if (temp->player == d) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				return;
			}
			temp = temp->next;
		}
	}
	void moveForward(T& p) {
		move_front(p);
	}
	void displayForward() {
		cout << "=====\n(HEAD)\n\n || \n";
		displayForwardsHelper(head->next);
		cout << "\n\n";
	}
	void displayBackward() {
		cout << "(TAIL)\n\n || \n";
		displayBackwardsHelper(tail->prev);
		
	}
};