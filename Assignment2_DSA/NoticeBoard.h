#pragma once
#include <iostream>
#include "person.h"
using namespace std;
class NoticeBoard {
	struct PlayerNode {
		person* player;
		PlayerNode* next;
		PlayerNode* prev;
		PlayerNode(person* pl = NULL, PlayerNode* n = NULL, PlayerNode* p = NULL) {
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
		cout << *(h->player) <<endl<<" || \n";
		displayForwardsHelper(h->next);
	}
	void displayBackwardsHelper(PlayerNode* h) {
		if (h == head) {
			cout << "\n(HEAD)\n";
			return;
		}
		cout << *(h->player) << endl << " || \n";
		displayBackwardsHelper(h->prev);
	}
	PlayerNode* search_Player(PlayerNode* curr,  int &id) {
		if (curr == tail)
			return NULL;
		if (curr->player->getPlayerID() == id)
			return curr;
		return search_Player(curr->next, id);
	}
	void clear() {
		PlayerNode* temp = head->next;
		while (head->next != tail) {
			temp = head->next;
			head -> next = temp->next;
			delete temp;
		}
		head->next = tail;
		tail->prev = head;
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
	NoticeBoard(const NoticeBoard& p) {
		head = new PlayerNode();
		tail = new PlayerNode();
		head->next = tail;
		tail->prev = head;
		head->prev = tail->next = NULL;

		PlayerNode* curr = p.head->next;
		while (curr != p.tail) {
			push_back(curr->player);
			curr = curr->next;
		}
	}
	bool operator == (const NoticeBoard& other) {
		PlayerNode* curr = other.head->next;
		PlayerNode* temp = head->next;
		while (curr != other.tail && temp != tail) {
			if (curr->player != temp->player)
				return false;
			curr = curr->next;
			temp = temp->next;
		}
		return true;
	}
	NoticeBoard& operator = (const NoticeBoard& other) {
		if (&other == this)
			return *this;
		clear();
		head->next = tail;
		tail->prev = head;
		head->prev = tail->next = NULL;

		PlayerNode* curr = other.head->next;
		while (curr != other.tail) {
			push_back(curr->player);
			curr = curr->next;
		}
		return *this;
	}
	
	~NoticeBoard() {
		clear();
		delete head;
		delete tail;
	}
	void push_front(person* p) {
		if (!p)
			return;
		PlayerNode* temp = new PlayerNode(p, head->next, head);
		head->next->prev = temp;
		head->next = temp;
	}
	void push_back(person* p) {
		if (!p)
			return;
		PlayerNode* temp = new PlayerNode(p, tail, tail->prev);
		tail->prev->next = temp;
		tail->prev = temp;
	}
	void remove(int id) {
		PlayerNode* temp = head->next;
		if (temp == tail)
			return;
		while (temp != tail) {
			if (temp->player->getPlayerID() == id) {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				return;
			}
			temp = temp->next;
		}
	}
	void moveForward(int id) {
		if (head->next == tail)
			return;
		
		PlayerNode* curr = head->next;
		curr = search_Player(curr, id);
		if (!curr)
			return;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;

		curr->next = head->next;
		head->next->prev = curr;
		head->next = curr;
		curr->prev = head;
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