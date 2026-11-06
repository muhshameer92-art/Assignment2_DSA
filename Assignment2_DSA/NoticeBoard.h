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
	void showHelper(PlayerNode* h) {
		if (h == tail) {
			cout << "\n(TAIL )\n";
			return;
		}
		cout << h->player <<endl<<" || \n";
		showHelper(h->next);
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
	void move_front(PlayerNode* p) {
		if (head->next == tail)
			return;
		if (head->next == p)
			return;
		PlayerNode* curr = head->next;
		while (curr != tail) {
			if (curr->next == p) {
				PlayerNode* temp = curr->next;
				curr->next = p->next;
				p->next->prev = curr;
				temp->next = head->next;
				head->next = temp;
				temp->prev = head;
				return;
			}
			curr = curr->next;
		}
	}
	void show() {
		cout << "(HEAD)\n\n || \n";
		showHelper(head->next);
	}
};