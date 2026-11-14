#pragma once
#include<iostream>
#include<string>
#include "person.h"
using namespace std;
class chessPlayerDirectory {
	struct playerRecord {
		person* player;
		playerRecord* left;
		playerRecord* right;
		playerRecord(person* p = NULL, playerRecord* l = NULL, playerRecord* r = NULL) {
			player = p;
			left = l;
			right = r;
		}
	};
	playerRecord* root;
	playerRecord* insertHelper(playerRecord* node, person* p) {
		if (!p)
		{
			cout << "No Player Found!" << endl;
			return node;
		}
		if (!node) {
			return new playerRecord(p);
		}
		if (node->player->getUsername() > p->getUsername())
			node->left = insertHelper(node->left, p);
		else if (node->player->getUsername() < p->getUsername())
			node->right = insertHelper(node->right, p);
		else
			cout << "Username already exists!" << endl;
		return node;
	}
	playerRecord* searchHelper(playerRecord* node, string username) {
		if (!node)
			return nullptr;

		if (node->player->getUsername() == username)
			return node;

		if (username < node->player->getUsername())
			return searchHelper(node->left, username);

		return searchHelper(node->right, username);
	}
	playerRecord* findMax(playerRecord* node) {
		if (!node)
			return NULL;
		if (!node->right)
			return node;
		return findMax(node->right);
	}
	playerRecord* removeHelper(playerRecord* node, person* p) {
		if (!node)
			return node;
		if (!p)
		{
			cout << "No Player Found!" << endl;
			return node;
		}
		if (node->player->getUsername() == p->getUsername() ) {
			if (!node->left && !node->right) {
				delete node;
				node = NULL;
			}
			else if (node->left && !node->right) {
				playerRecord* temp = node;
				node = node->left;
				delete temp;
			}
			else if (!node->left && node->right) {
				playerRecord* temp = node;
				node = node->right;
				delete temp;
			}
			else {
				playerRecord* temp = findMax(node->left);
				node->player = temp->player;
				node->left = removeHelper(node->left, temp->player);
			}
			return node;
		}
		if (node->player->getUsername() > p->getUsername())
			node->left = removeHelper(node->left, p);
		else if (node->player->getUsername() < p->getUsername())
			node->right = removeHelper(node->right, p);

		return node;
	}
	void printInOrder(playerRecord* node) {
		if (!node)
			return;
		printInOrder(node->left);
		cout << node->player->getUsername() << endl;
		printInOrder(node->right);
	}
	void reverseOrderHelper(playerRecord* node) {
		if (!node)
			return;
		reverseOrderHelper(node->right);
		cout << node->player->getUsername() << endl;
		reverseOrderHelper(node->left);
	}
	void rangeHelper(playerRecord* node, string low, string high) {
		if (!node)
			return;

		string username = node->player->getUsername();

		if (username > low)
			rangeHelper(node->left, low, high);

		if (username >= low && username <= high)
			cout << username << endl;

		if (username < high)
			rangeHelper(node->right, low, high);
	}
	void destroy(playerRecord* node) {
		if (!node)
			return;

		destroy(node->left);
		destroy(node->right);
		delete node;
	}
public:
	chessPlayerDirectory() {
		root = NULL;
	}
	~chessPlayerDirectory() {
		destroy(root);
	}
	void insert(person* p) {
		if (!p)
			return;
		root = insertHelper(root, p);
	}
	void remove(person* p) {
		if (!p)
			return;
		root = removeHelper(root, p);
	}
	void display() {
		printInOrder(root);
	}
	void display_Reverse() {
		reverseOrderHelper(root);
	}
	void displayRange(string low, string high) {
		if (low > high) {
			cout << "Invalid range!" << endl;
			return;
		}

		rangeHelper(root, low, high);
	}
	person* search(string username) {
		playerRecord* result = searchHelper(root, username);

		if (!result)
			return nullptr;

		return result->player;
	}
	
};