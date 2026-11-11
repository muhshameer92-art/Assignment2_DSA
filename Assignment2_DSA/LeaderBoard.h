#pragma once
#include<iostream>
using namespace std;
class leaderBoard {
	struct scoreCard {
		person* player;
		scoreCard* left;
		scoreCard* right;
		int height;
		scoreCard(person* p = NULL, scoreCard* l = NULL, scoreCard* r = NULL) {
			player = p;
			left = l;
			right = r;
			height = 0;
		}
	};
	scoreCard* root;
	int getH(scoreCard* node) {
		return node->height;
	}
	void updateH(scoreCard* node) {
		node->height = 1 + max(getH(node->left), getH(node->right));
	}
	int BF(scoreCard* node) {
		if (!node) {
			return 0;
		}
		return getH(node->left) - getH(node->right);
	}
	bool isBalanced(scoreCard* node) {
		if (abs(BF(node)) > 1)
			return false;
		return true;
	}
	scoreCard* rotateRight(scoreCard* x) {
		if (x == nullptr || x->left == nullptr)
			return x;

		scoreCard* y = x->left;
		scoreCard* T2 = y->right;

		// Perform rotation
		y->right = x;
		x->left = T2;

		// Update heights
		updateH(x);
		updateH(y);
		return y;
	}
	scoreCard* rotateLeft(scoreCard* x) {
		if (x == nullptr || x->right == nullptr)
			return x;

		scoreCard* y = x->right;
		scoreCard* T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		// Update heights
		updateH(x);
		updateH(y);

		return y;
	}
	scoreCard* doubleRotateRight(scoreCard* x) {
		if (x == nullptr)
			return x;

		x->left = rotateLeft(x->left);
		return rotateRight(x);
	}
	scoreCard* doubleRotateLeft(scoreCard* x) {
		if (x == nullptr)
			return x;

		x->right = rotateRight(x->right);
		return rotateLeft(x);
	}
	scoreCard* insertHelper(scoreCard* node, person* p) {
		//edge case
		if (!p) {
			cout << "No Player Found!" << endl;
			return node;
		}
		// base case
		if (!node) {
			return new scoreCard(p);
		}
		//first priority is score
		if (node->player->getScore() > p->getScore() )
			node->left = insertHelper(node->left, p);
		else if (node->player->getScore() < p->getScore())
			node->right = insertHelper(node->right, p);
		// tie in score! judge level of players
		else if (node->player->getScore() == p->getScore()) {
			if(node->player->getLvl() > p->getLvl())
				node->left = insertHelper(node->left, p);
			else if(node->player->getLvl() < p->getLvl())
				node->right = insertHelper(node->right, p);
			//level also tied,tsk tsk tsk, lets compare playerID
			else if (node->player->getLvl() == p->getLvl()) {
				if(node->player->getPlayerID() > p->getPlayerID())
					node->left = insertHelper(node->left, p);
				else if(node->player->getPlayerID() > p->getPlayerID())
					node->right = insertHelper(node->right, p);
			}
		}
		//update Height
		updateH(node);
		//balance check - during backtracking - leaf node towards root
		if (!isBalanced(node)) {
			if (BF(node) > 1 && BF(node->left) >= 0)
				node = rotateRight(node);
			if (BF(node) < -1 && BF(node->right) <= 0)
				node = rotateLeft(node);
			if (BF(node) > 1 && BF(node->left) < 0)
				node = doubleRotateRight(node);
			if (BF(node) < -1 && BF(node->right) > 0)
				node = doubleRotateLeft(node);
		}
		return node;
	}
public:
	leaderBoard() {
		root = NULL;
	}
	void insert(person* p) {
		root = insertHelper(root, p);
	}

};